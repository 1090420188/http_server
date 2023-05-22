
#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
extern char *optarg;

extern int optind;

int main(int argc,char *argv[])
{
    int flags,opt;
    mode_t perms;
    mqd_t mqd;

    struct mq_attr attr,*attrp=NULL;

    flags=O_RDWR;

    while ((opt=getopt(argc,argv,"cm:s:x"))!=-1){
        switch (opt)
        {
        case 'c':
            flags|=O_CREAT;
            break;
        case 'm':
            attr.mq_maxmsg=atoi(optarg);
            attrp=&attr;
            break;
        case 's':
            attr.mq_msgsize=atoi(optarg);
            attrp=&attr;
            break;
        case 'x':
            flags|=O_EXCL;
            break;
        default:
            printf("error\n");
            return -1;
        }
    }
    
    perms = S_IRUSR |S_IWUSR;

    printf("argv[optind]:%s\n",argv[optind]);
    mqd=mq_open(argv[optind],flags,perms,attrp);

    if(mqd==-1)
    {
        perror("mq_open");
        return -1;
    }

    return 0;
}