#include <syslog.h>
#include <unistd.h>


void main(int agrc,char *argv[])
{
    openlog(argv[0],LOG_NDELAY,LOG_SYSLOG);

    syslog(LOG_ERR,"error %s",argv[0]);

    pause();   
}