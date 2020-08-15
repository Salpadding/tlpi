#include "../lib/i6d_ucase.h"

/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2020.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

int main(int argc, char *argv[])
{
    int sfd = socket(AF_INET6, SOCK_DGRAM, 0);

    struct sockaddr_in6 *svaddr = malloc(sizeof(struct sockaddr_in6));
    svaddr->sin6_family = AF_INET6;
    svaddr->sin6_addr = in6addr_any; /* Wildcard address */
    svaddr->sin6_port = htons(PORT_NUM);

    bind(sfd, (struct sockaddr *)svaddr,
         sizeof(struct sockaddr_in6));

    /* Receive messages, convert to uppercase, and return to client */

    for (;;)
    {
        struct sockaddr_in6 claddr;
        char buf[BUF_SIZE];
        char claddrStr[INET6_ADDRSTRLEN];
        socklen_t len = sizeof(struct sockaddr_in6);
        ssize_t numBytes = recvfrom(sfd, buf, BUF_SIZE, 0,
                            (struct sockaddr *)&claddr, &len);

        if (inet_ntop(AF_INET6, &claddr.sin6_addr, claddrStr,
                      INET6_ADDRSTRLEN) == NULL)
            printf("Couldn't convert client address to string\n");
        else
            printf("Server received %ld bytes from (%s, %u)\n",
                   (long)numBytes, claddrStr, ntohs(claddr.sin6_port));

        for (int j = 0; j < numBytes; j++)
            buf[j] = toupper((unsigned char)buf[j]);

        if (sendto(sfd, buf, numBytes, 0, (struct sockaddr *)&claddr, len) !=
            numBytes)
            fatal("sendto");
    }
}