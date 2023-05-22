#include <mqueue.h>
#include <string.h>
#include <stdio.h>

int main(int argc,char *argv[])
{
    mqd_t mqd;
    struct mq_attr attr;

    if(argc<3)
    {
        printf("%s filename send_message",argv[0]);
        return -1;
    }

    mqd=mq_open(argv[1],O_RDWR);
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

    if(mq_send(mqd,argv[2],strlen(argv[2]),0)==-1)
    {
        perror("mq_send");
        return -1;
    }

    return 0;
}
