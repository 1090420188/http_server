#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BD_CHDIR             0x1
#define BD_CLOSE_FILES       0x2
#define BD_REOPEN_STD_FDS    0x4
#define BD_UMASK0            0x8

int becomeDaemon(int flags)
{
    int maxfd,fd;

    switch (fork())
    {
    case -1:
        return -1;
    case 0:
        break;
    default:
        exit(0);
    }

    if(flags& BD_UMASK0)
        umask(0);
    
    if(flags & BD_CHDIR)
        chdir("/");

    if(flags & BD_REOPEN_STD_FDS){
        close(STDIN_FILENO);

        fd=open("/dev/null",O_RDWR);

        if(fd!=STDIN_FILENO)
            return -1;
        if(dup2(STDIN_FILENO,STDOUT_FILENO)!=STDOUT_FILENO)
            return -1;
        if(dup2(STDIN_FILENO,STDERR_FILENO)!=STDERR_FILENO)
            return -1;
    }
    
    return 0;
}