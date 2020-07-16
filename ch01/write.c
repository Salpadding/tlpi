#include <sys/stat.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

#define MAX_WRITE 20

void print(char *c);
int str_len(char *c);

int main(){

    char *f_name = "/home/sal/Documents/apue/ch01/write.o";
    int fd = open(f_name, O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(fd == -1)
        errExit("open");
    char *content = "hello world";
    int padding = 0;
    lseek(fd, padding, SEEK_SET);

    write(fd, content, str_len(content));
    if(close(fd) == -1)
        errExit("close");
    return 0;
}

int str_len(char *c){
    int len = 0;
    while (*(c++) != '\0')
    {
        len++;
    }
    return len;
}

void print(char *c){
    while (*c != '\0')
    {
        putchar(*c);
        c++;
    }
    
}