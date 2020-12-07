#include <sys/stat.h> 
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

void fd_print(int f){
    #define BUF_SIZE 1024
    char buf[BUF_SIZE + 1];
    int n;
    while ((n = read(f, buf, BUF_SIZE)) > 0)
    {
        buf[n] = '\0';
        printf("%s", buf);
    }
}

int main(int argc, char** argv){    
    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s filename\n", argv[0]);  
    int openFlags = O_RDONLY;
    int f = open(argv[1], openFlags);
    fd_print(f);
    lseek(f, 0, SEEK_SET);
    fd_print(f);
    close(f);
    return 0;
}

