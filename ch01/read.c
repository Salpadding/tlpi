#include <sys/stat.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

#define MAX_READ 20

void print(char *c);

int main(){
    char buf[MAX_READ];
    char *f_name = "/home/sal/Documents/apue/ch01/copy.c";
    int fd = open(f_name, O_RDONLY);
    if(fd == -1)
        errExit("open");

    while (read(fd, buf, MAX_READ) > 0)
    {
        printf("%s", buf);
    }
    
    printf("\n");
    printf("current offset = %d\n", lseek(fd, 0, SEEK_CUR));

    if(close(fd) == -1)
        errExit("close");
    return 0;
}

void print(char *c){
    while (*c != '\0')
    {
        putchar(*c);
        c++;
    }
    
}