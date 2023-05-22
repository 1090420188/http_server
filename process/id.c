#define _POSIX_C_SOURCE 202010
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

void main()
{
    pid_t pgid=getpgrp();
    pid_t pid=getpid();

    pid_t sid=getsid(pid);

    printf("pid: %d\tpgid: %d\tsid: %d\n",pid,pgid,sid);
}