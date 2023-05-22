#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc,char *argv[])
{
    int *addr;

#ifdef USE_MAP_ANON
    addr=mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANON,-1,0);

    if(addr==MAP_FAILED)
    {
        perror("mmap");
        return -1;
    }
#else
    int  fd=open("/dev/zero",O_RDWR);
    
    addr=mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

    if(addr==MAP_FAILED)
    {
        perror("mmap");
        return -1;
    }

    if(close(fd)==-1)
    {
        perror("close");
        return -1;
    }
#endif
    *addr=1;

    switch(fork())
    {
        case 0:
        printf("Child started ,value=%d\n",*addr);
        (*addr)++;
        if(munmap(addr,sizeof(int))==-1)
        {
            perror("munmap");
            return -1;
        }
        return 0;
        default:
        if(wait(NULL)==-1)
        {
            perror("wait");
            return -1;
        }
        printf("Parent end ,value=%d\n",*addr);
        if(munmap(addr,sizeof(int))==-1)
        {
            perror("munmap");
            return -1;
        }
        return 0;
    }

    return 0;
}