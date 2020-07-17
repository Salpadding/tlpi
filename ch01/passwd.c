#include <stdio.h>
#include <pwd.h>


int main(){
    struct passwd *p = getpwnam("sal");
    printf("login name = %s\n", (*p).pw_name);
    printf("password = %s\n", (*p).pw_passwd);
    printf("uid = %d\n", (*p).pw_uid);
    printf("gid = %d\n", (*p).pw_gid);
    printf("home directory = %s\n", (*p).pw_dir);
    printf("login shell = %s\n", (*p).pw_shell);
    return 0;
}