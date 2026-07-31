#ifndef PROCESS_LIST
#define PROCESS_LIST

#include <sys/proc.h>

typedef struct {
    pid_t pid;
    char name[32];
    char status[16];
} ProcessInfo;

ProcessInfo* get_process_lst(int *out_count);

#endif