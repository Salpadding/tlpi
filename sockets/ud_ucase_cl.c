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

int main(int argc, char *argv[]){
    // create client socket; bind to unique pathname
    struct sockaddr_un *claddr = malloc(sizeof(struct sockaddr_un));
    claddr->sun_family = AF_UNIX;
    snprintf(claddr->sun_path, sizeof(claddr->sun_path), "/tmp/ud_ucase_cl.%ld", (long) getpid());
    int sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    bind(sfd, (struct sockaddr *)claddr, sizeof(struct sockaddr_un));

    struct sockaddr_un *svaddr = malloc(sizeof(struct sockaddr_un));
    svaddr->sun_family = AF_UNIX;
    strncpy(svaddr->sun_path, SV_SOCK_PATH, sizeof(svaddr->sun_path) - 1);


    for(int j = 1; j < argc; j++){
        char resp[BUF_SIZE];
        size_t msgLen = strlen(argv[j]);
        sendto(sfd, argv[j], msgLen, 0, (struct sockaddr *) svaddr, sizeof(struct sockaddr_un));
        ssize_t numBytes = recvfrom(sfd, resp, BUF_SIZE, 0, NULL, NULL);
        printf("Response: %d: %.*s\n", j, (int) numBytes, resp);
    }

    remove(claddr->sun_path);
    return 0;
}