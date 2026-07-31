#include <stdio.h>
#include <stdlib.h>
#include <libproc.h>
#include "process.h"
#include <sys/proc.h>
#include <mach/thread_info.h>

// does everything: gets bsdinfo, checks zombie/stopped, falls back to threads
static const char *get_run_state(pid_t pid)
{
    struct proc_bsdinfo bsdinfo = {0}; // 0 to clean garbage
    int bsd_bytes = proc_pidinfo(pid, PROC_PIDTBSDINFO, 0, &bsdinfo, PROC_PIDTBSDINFO_SIZE);

    if (bsd_bytes != PROC_PIDTBSDINFO_SIZE) { // PROC_PIDTBSDINFO_SIZE is 136
        return "unknown";
    }

    // zombies have no threads left to inspect, so this is the only way to catch them
    if (bsdinfo.pbi_status == SZOMB) {
        return "zombie";
    }

    // everything else, we can get straight from thread state
    uint64_t thread_ids[64];
    int bytes = proc_pidinfo(pid, PROC_PIDLISTTHREADS, 0, thread_ids, sizeof(thread_ids));
    if (bytes <= 0) { // length varies
        return "unknown";
    }

    int num_threads = bytes / sizeof(uint64_t);

    int saw_waiting = 0;
    int saw_stopped = 0;

    for (int t = 0; t < num_threads; t++) {
        struct proc_threadinfo tinfo = {0}; // 0 to clean garbage in mem
        int tb = proc_pidinfo(pid, PROC_PIDTHREADINFO, thread_ids[t], &tinfo, sizeof(tinfo));
        if (tb != sizeof(tinfo)) {
            continue;
        }

        switch (tinfo.pth_run_state) {
        case TH_STATE_RUNNING:
            return "running";
        case TH_STATE_WAITING:
        case TH_STATE_UNINTERRUPTIBLE:
            saw_waiting = 1;
            break;
        case TH_STATE_STOPPED:
            saw_stopped = 1;
            break;
        case TH_STATE_HALTED:
        default:
            break;
        }
    }

    if (saw_waiting) return "sleeping";
    if (saw_stopped) return "stopped";
    return "unknown";
}

ProcessInfo* get_process_lst(int *out_count)
{
    int space_needed = proc_listpids(PROC_ALL_PIDS, 0, NULL, 0);
    pid_t *pid_list = malloc(space_needed);
    space_needed = proc_listpids(PROC_ALL_PIDS, 0, pid_list, space_needed);
    int num_of_proc = space_needed / sizeof(pid_t);
    ProcessInfo *final_list = malloc(num_of_proc * sizeof(ProcessInfo));

    for (int i = 0; i < num_of_proc; i++) {
        (final_list + i)->pid = *(pid_list + i);
        proc_name((final_list + i)->pid, (final_list + i)->name, 32);

        const char *state = get_run_state((final_list + i)->pid);
        snprintf((final_list + i)->status, 16, "%s", state);
    }

    free(pid_list);
    *out_count = num_of_proc;
    return final_list;
}