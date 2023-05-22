#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc,char *argv[])
{
    mqd_t mqd;
    struct mq_attr attr;

    if(argc<2)
    {
        printf("%s filename send_message",argv[0]);
        return -1;
    }

    mqd=mq_open(argv[1],O_RDONLY);
    if(mqd==-1)
    {
        perror("mq_open");
        return -1;
    }
    if(mq_getattr(mqd,&attr)==-1)
    {
        perror("mq_getattr");
        return -1;
    }

    char *buffer=malloc(attr.mq_msgsize);

    unsigned int prio;

    int numRead=mq_receive(mqd,buffer,attr.mq_msgsize,&prio);

    printf("Read %d bytes,priority=%u\n",numRead,prio);

    printf("%s\n",buffer);

    return 0;
}