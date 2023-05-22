#define _POSIX_C_SCOURCE 202305
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

extern int optind;

int main(int argc,char *argv[])
{
    int flags,opt,fd;
    mode_t perms;
    size_t size;

    void *addr;

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
    perms=S_IRUSR|S_IWUSR;
    fd=shm_open(argv[optind],flags,perms);

    if(fd==-1)
    {
        perror("shm_open");
        return -1;
    }   
    size=atoi(argv[optind+1]);

    if(ftruncate(fd,size)==-1)
    {
        perror("ftruncate");
        return -1;
    }

    addr=mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

    return 0;
}