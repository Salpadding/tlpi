#include <stdio.h>
#include <unistd.h>


int main(){
    printf("pid = %d\n", getpid());
    printf("parent pid = %d\n", getppid());
    return 0;
}
