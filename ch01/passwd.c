#include <stdio.h>
#include <pwd.h>
#include <grp.h>

void print_strs(char **arr);

int main()
{
    struct passwd *p = getpwnam("mac");
    printf("login name = %s\n", p->pw_name);
    printf("password = %s\n", p->pw_passwd);
    printf("uid = %d\n", p->pw_uid);
    printf("gid = %d\n", p->pw_gid);
    printf("home directory = %s\n", p->pw_dir);
    printf("login shell = %s\n", p->pw_shell);

    struct group *g = getgrnam("staff");
    printf("group name = %s\n", g->gr_name);
    printf("password = %s\n", g->gr_passwd);
    printf("gid = %d\n", g->gr_gid);
    printf("members:\n");
    print_strs(g->gr_mem);
    return 0;
}

void print_strs(char **arr)
{
    char **p = arr;
    while (*p != NULL)
    {
        printf("%s\n", *p);
        p++;
    }
}