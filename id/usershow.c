#define _BAD_SOURCE
#define _XOPEN_SOURCE
#include <pwd.h>
#include <shadow.h>
#include <stdio.h>
#include <crypt.h>


void main()
{
    struct passwd *pwd;


    pwd=getpwnam("root");


    printf("name: %s\npasswd: %s\ngecos: %s\ndir: %s\nshell: %s\n",pwd->pw_name,pwd->pw_passwd,pwd->pw_gecos,pwd->pw_dir,pwd->pw_shell);


//    getpwent 逐条获取

    struct spwd *shadow_pwd= getspnam("root");

    printf("name: %s\npwdp: %s\nsp_last_change: %ld\nsp_min: %ld\nsp_max: %ld\n",shadow_pwd->sp_namp,shadow_pwd->sp_pwdp,shadow_pwd->sp_lstchg,shadow_pwd->sp_min,shadow_pwd->sp_max);


 char *p=   crypt("Houguohao123","$6$QBWOkTUH$CNdxL2RV1Y6B5sS28NhT");
    printf("%s\n",p);
}