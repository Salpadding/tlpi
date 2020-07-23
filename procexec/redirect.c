#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    if(fork() == 0){
        int fd = open("txt.o", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        dup2(fd, 1);
        close(fd);
        printf("hello world\n");
    }
    return 0;
}