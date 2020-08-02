#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SV_SOCK_PATH "/tmp/us_xfr"
#define BUF_SIZE 100
#define BACKLOG 5

int main()
{

    // connect to server
    struct sockaddr_un *addr = malloc(sizeof(struct sockaddr_un));
    addr->sun_family = AF_UNIX;
    strncpy(addr->sun_path, SV_SOCK_PATH, sizeof(addr->sun_path) - 1);
    int sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    connect(sfd, (struct sockaddr *)addr, sizeof(struct sockaddr_un));

    ssize_t numRead;
    char buf[BUF_SIZE];

    // copy stdin to sfd
    while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
    {
        write(sfd, buf, numRead);
    }

    return 0;
}