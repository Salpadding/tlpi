#include "../lib/tlpi_hdr.h"
#include <sys/stat.h> 
#include <fcntl.h>
#include <string.h>
#define DELTA	1000

int main(int argc, char** argv){
    int openFlags = O_TRUNC | O_WRONLY | O_CREAT;
    int f = open(argv[1], openFlags);
    char* c = "write into hole";
    write(f, c, strlen(c));    
    lseek(f, 10 * DELTA, SEEK_SET);
    write(f, c, strlen(c));    
    close(f);
    return 0;
}