#include <stdio.h>
#include <mqueue.h>
#include <sys/stat.h>

int main(int argc,char *argv[])
{
    mqd_t mqd;

    struct mq_attr attr;

    if(argc<2)
    {
        printf("%s filename",argv[0]);
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

    printf("Maxinum #of messages on queue %ld\n",attr.mq_maxmsg);
    printf("Maxinum message size: %ld\n",attr.mq_msgsize);
    printf("# of message currently on queue: %ld\n",attr.mq_curmsgs);

    return 0;
}
