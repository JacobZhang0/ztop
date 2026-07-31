#include <libproc.h>
#include <stdio.h>
#include <stdlib.h>
#include "process.h"

int main(void)
{
    int total_proc = 0;

    ProcessInfo *my_list = get_process_lst(&total_proc);
    printf("PID\tNAME\tSTATUS\n");
    for (int i = 0; i < total_proc; i++) {
        printf("%-4d\t%-32s\t%-8s\n", (my_list + i)->pid, (my_list+ i)->name, (my_list + i)->status);
    }

    free(my_list);
    return 0;
}
