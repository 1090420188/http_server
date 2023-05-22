#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
    char *addr;
    int fd;

    struct stat sb;

    if(argc!=2)
    {
        printf("%s file",argv[0]);
        return -1;
    }

    fd=open(argv[1],O_RDONLY);
    if(fd==-1)
    {
        perror("open");
        return -1;
    }

    if(fstat(fd,&sb)==-1)
    {
        perror("fstat");
        return -1;
    }

    addr=mmap(NULL,sb.st_size,PROT_READ,MAP_PRIVATE,fd,0);

    printf("%p\n",addr);

    if(addr==MAP_FAILED)
    {
        perror("mmap");
        return -1;
    }

    if(write(STDOUT_FILENO,addr,sb.st_size)!=sb.st_size)
    {
        perror("write");
        return -1;
    }

    exit(0);
}


