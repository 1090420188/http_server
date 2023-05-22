#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[])
{
    char *addr;

    int fd;

    if(argc<2)
    {
        printf("%s file",argv[0]);
        return -1;
    }

    fd=open(argv[1],O_RDWR);

    addr= mmap(NULL,10,PROT_WRITE,MAP_SHARED,fd,0);

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
    printf("%p\n",addr);
    if(argc>2)
    {
        if(strlen(argv[2])>10)
        {
            printf("new-value to large\n");
            return -1;   
        }

        memset(addr,0,10);

        strncpy(addr,argv[2],strlen(argv[2]));
        if(msync(addr,10,MS_SYNC)==-1)
        {
            perror("msync error");
            return -1;
        }
        printf("Copied %s to shared memory\n",argv[2]);
    }

    return 0;
}