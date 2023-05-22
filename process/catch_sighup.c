#define _POSIX_C_SOURCE 202010
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

static void 
handler(int sig)
{
    int fd=open("log",O_WRONLY|O_APPEND);

    write(fd,"22",2);
    close(fd);
}
void main(int argc,char *argv[])
{
    setbuf(stdout,NULL);
    pid_t childpid;

    struct sigaction ac;

    ac.sa_flags=0;
    ac.sa_handler=handler;
    sigemptyset(&ac.sa_mask);

    if(sigaction(SIGHUP,&ac,NULL)==-1)
    {
        perror("sigaction");
        return ;
    }

    
    pid_t pgid=getpgrp();
    pid_t pid=getpid();

    pid_t sid=getsid(pid);

    printf("pid: %d\tpgid: %d\tsid: %d\n",pid,pgid,sid);

    alarm(60);
    for(;;)
    {
        pause();
        printf("%d caught SIGHUP\n",getpid());
    }
}