#define _GNU_SOURCE
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>


void main()
{

    uid_t real_id,effective_id;
    gid_t real_gid,effective_gid;


    real_id=getuid();
    real_gid=getgid();

    effective_id=geteuid();
    effective_gid=getegid();



    if(setuid(real_id)<-1) 
    {
        if(errno==EPERM)
        {
            //非特权用户 修改id 不是  real saved
        }   
    }
    //特权  将real effective saved 都修改为 1000
    //非特权 将effective 修改为real 或saved 

    //real effective
    setreuid(-1,1000);
    //非特权 将 effective 修改为 real saved



}