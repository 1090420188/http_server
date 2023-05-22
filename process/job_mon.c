#define _POSIX_C_SOURCE 202010
#define _GNU_SOURCE
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

static int cmdNum;

static void
handler(int sig)
{
    if(getpid()==getpgrp())
    {
        fprintf(stderr,"Terminal FG process group:%d\n",tcgetpgrp(STDERR_FILENO));
    }
    fprintf(stderr,"Process %d (%d)received signal %d (%s)\n",getpid(),cmdNum,sig,strsignal(sig));
    if(sig==SIGTSTP)
        raise(SIGSTOP);
}

void main()
{
    struct sigaction ac;
    sigemptyset(&ac.sa_mask);
    ac.sa_flags=SA_RESTART;
    ac.sa_handler=handler;
    if(sigaction(SIGINT,&ac,NULL)==-1)
    {
        perror("sigactoin");
        return ;
    }
    if(sigaction(SIGTSTP,&ac,NULL)==-1)
    {
        perror("sigactoin");
        return ;
    }
    if(sigaction(SIGCONT,&ac,NULL)==-1)
    {
        perror("sigactoin");
        return ;
    }

    if(isatty(STDIN_FILENO)){
        fprintf(stderr,"Terminal FG process group:%d\n",tcgetpgrp(STDIN_FILENO));
        fprintf(stderr,"Command PID PPID PGRP SID\n");
    }
    else{
        if(read(STDIN_FILENO,&cmdNum,sizeof(cmdNum))<=0)
        {
            perror("read");
        }
    }
    cmdNum++;

     pid_t pgid=getpgrp();
    pid_t pid=getpid();

    pid_t sid=getsid(pid);

    fprintf(stderr,"%d\tpid: %d\tpgid: %d\tsid: %d\n",cmdNum,pid,pgid,sid);

    if(!isatty(STDOUT_FILENO))
        write(STDOUT_FILENO,&cmdNum,sizeof(cmdNum));
    for(;;)
        pause();
}