#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#define SV_SOCK_PATH "/tmp/us_xfr"
#define BUF_SIZE 100
#define BACKLOG 5

int main(){
    // remove previous created socket
    remove(SV_SOCK_PATH);

    // create sockaddr_un 
    struct sockaddr_un *svaddr = malloc(sizeof(struct sockaddr_un));
    svaddr->sun_family = AF_UNIX;
    strncpy(svaddr->sun_path, SV_SOCK_PATH, sizeof(svaddr->sun_path) - 1);

    // create socket
    int sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
 
    // bind
    bind(sfd, (struct sockaddr *)svaddr, sizeof(struct sockaddr_un));

    // receive messages, convert to uppercase, and return to client
    for(;;){
        int len;
        char buf[BUF_SIZE];
        struct sockaddr_un claddr;
        ssize_t numBytes = recvfrom(sfd, buf, BUF_SIZE, 0, (struct sockaddr *)&claddr, &len);

        printf("Server received %ld bytes from %s\n", (long) numBytes, claddr.sun_path);

        for(int j = 0; j < numBytes; j++){
            buf[j] = toupper(buf[j]);
        }

        sendto(sfd, buf, numBytes, 0, (struct sockaddr *) &claddr, len);
    }

    return 0;
}