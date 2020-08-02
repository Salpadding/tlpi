#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SV_SOCK_PATH "/tmp/us_xfr"
#define BUF_SIZE 100
#define BACKLOG 5

int main(){
    // remove previous created socket
    remove(SV_SOCK_PATH);

    // create sockaddr_un 
    struct sockaddr_un *addr = malloc(sizeof(struct sockaddr_un));
    addr->sun_family = AF_UNIX;
    strncpy(addr->sun_path, SV_SOCK_PATH, sizeof(addr->sun_path) - 1);



    // create socket
    int sfd = socket(AF_UNIX, SOCK_STREAM, 0);
 
    // bind
    bind(sfd, (struct sockaddr *)addr, sizeof(struct sockaddr_un));
    listen(sfd, BACKLOG);

    // handle connections
    for(;;){
        int cfd = accept(sfd, NULL, NULL);
        char buf[BUF_SIZE];
        ssize_t numRead = 0;
        while ((numRead = read(cfd, buf, BUF_SIZE)) > 0)
        {
            fprintf(stdout, "%s", buf);
        }
    }

    return 0;
}