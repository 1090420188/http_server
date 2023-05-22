#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>


int main(int argc,char *argv[])
{
    uid_t real_id,effective_id,saved_id;
    gid_t real_gid,effective_gid,save_gid;


    real_id=getuid();
    real_gid=getgid();

    effective_id=geteuid();
    effective_gid=getegid();


    getresuid(NULL,NULL,&saved_id);
    getresgid(NULL,NULL,&save_gid);

    printf("real id:%d\t gid:%d\n",real_id,real_gid);

    printf("effective id:%d\t gid:%d\n",effective_id,effective_gid);

    printf("saved id:%d\t gid:%d\n",saved_id,save_gid);

    return 0;
}
