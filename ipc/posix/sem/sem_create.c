#include <semaphore.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

extern int optind;

int main(int argc,char *argv[])
{
    int flags,opt;
    mode_t perms;

    unsigned int value;
    sem_t *sem;

    flags=0;

    while((opt=getopt(argc,argv,"cx"))==-1)
    {
        switch (opt)
        {
        case 'c':
            flags|=O_CREAT;
            break;
        case 'x':
            flags|=O_EXCL;
            break;
        default:
            printf("error");
            return -1;
        }
    }    

    sem=sem_open(argv[optind],flags,S_IRUSR|S_IWUSR,1);
    if(sem==SEM_FAILED)
    {
        perror("sem_open");
        return -1;
    }

    return 0;
}