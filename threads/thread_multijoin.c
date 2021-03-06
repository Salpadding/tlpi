/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2020.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* thread_multijoin.c

   This program creates one thread for each of its command-line arguments.
   Each thread sleeps for the number of seconds specified in the corresponding
   command-line argument, and then terminates. This sleep interval simulates
   "work" done by the thread.

   The program maintains a global array (pointed to by 'thread') recording
   information about all threads that have been created. The items of this
   array record the thread ID ('tid') and current state ('state', of type
   'enum tstate') of each thread.

   As each thread terminates, it sets its 'state' to TS_TERMINATED and
   signals the 'threadDied' condition variable. The main thread continuously
   waits on this condition variable, and is thus informed when any of the
   threads that it created has terminated. When 'numLive', which records
   the number of live threads, falls to 0, the main thread terminates.
*/
#include <pthread.h>
#include "../lib/tlpi_hdr.h"

static pthread_cond_t threadDied = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t threadMutex = PTHREAD_MUTEX_INITIALIZER;
/* Protects all of the following global variables */

static int totThreads = 0;  /* Total number of threads created */
static int numLive = 0;     /* Total number of threads still alive or
                                   terminated but not yet joined */
static int numUnjoined = 0; /* Number of terminated threads that
                                   have not yet been joined */
enum tstate
{                /* Thread states */
  TS_ALIVE,      /* Thread is alive */
  TS_TERMINATED, /* Thread terminated, not yet joined */
  TS_JOINED      /* Thread terminated, and joined */
};

static struct
{                      /* Info about each thread */
    pthread_t tid;     /* ID of this thread */
    enum tstate state; /* Thread state (TS_* constants above) */
    int sleepTime;     /* Number seconds to live before terminating */
} * thread;

static void * /* Start function for thread */
threadFunc(void *arg)
{
    int idx = (int)arg;

    sleep(thread[idx].sleepTime); /* Simulate doing some work */
    printf("Thread %d terminating\n", idx);

    thread_mutex_lock(&threadMutex);

    numUnjoined++;
    thread[idx].state = TS_TERMINATED;

    pthread_mutex_unlock(&threadMutex);
    pthread_cond_signal(&threadDied);

    return NULL;
}

int main(int argc, char *argv[])
{

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s num-secs...\n", argv[0]);

    thread = calloc(argc - 1, sizeof(*thread));
    if (thread == NULL)
        errExit("calloc");

    /* Create all threads */

    for (int idx = 0; idx < argc - 1; idx++)
    {
        thread[idx].sleepTime = getInt(argv[idx + 1], GN_NONNEG, NULL);
        thread[idx].state = TS_ALIVE;
        pthread_create(&thread[idx].tid, NULL, threadFunc, (void *)idx);
    }

    totThreads = argc - 1;
    numLive = totThreads;

    /* Join with terminated threads */

    while (numLive > 0)
    {
        pthread_mutex_lock(&threadMutex);

        while (numUnjoined == 0)
        {
            pthread_cond_wait(&threadDied, &threadMutex);
        }

        for (int idx = 0; idx < totThreads; idx++)
        {
            if (thread[idx].state == TS_TERMINATED)
            {
                pthread_join(thread[idx].tid, NULL);

                thread[idx].state = TS_JOINED;
                numLive--;
                numUnjoined--;

                printf("Reaped thread %d (numLive=%d)\n", idx, numLive);
            }
        }

        pthread_mutex_unlock(&threadMutex);
    }

    exit(EXIT_SUCCESS);
}
