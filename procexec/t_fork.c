/* t_fork.c

   Demonstrate the use of fork(), showing that parent and child
   get separate copies of stack and data segments.
*/
#include "../lib/tlpi_hdr.h"

static int idata = 111;             /* Allocated in data segment */
int
main(int argc, char *argv[])
{
    int istack = 222;               /* Allocated in stack segment */
    pid_t childPid;

    switch (childPid = fork()) {
    case -1:
        errExit("fork");

    case 0:
        printf("childPid = %ld\n", (long) childPid);
        idata *= 3;
        istack *= 3;
        break;

    default:
        printf("childPid = %ld\n", (long) childPid);
        sleep(3);                   /* Give child a chance to execute */
        break;
    }

    /* Both parent and child come here */

    printf("PID=%ld %s idata=%d istack=%d\n", (long) getpid(),
            (childPid == 0) ? "(child) " : "(parent)", idata, istack);

    exit(EXIT_SUCCESS);
}