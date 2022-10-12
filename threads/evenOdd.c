#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#ifndef NUM_THREADS
#define NUM_THREADS 20
#endif

void *oddFunction(void *threadid)
{
    long tid;
    tid = (long)threadid;
    printf("Eu sou um processo PAR” - %lu --- número %lu \n", pthread_self(), tid + 1);
    pthread_exit(NULL);
}

void *evenFunction(void *threadid)
{
    long tid;
    tid = (long)threadid;
    printf("Eu sou um processo ÍMPAR. - %lu --- número %lu \n", pthread_self(), tid + 1);
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    for (t = 0; t < NUM_THREADS; t++)
    {
        if (t % 2 == 0)
        {
            rc = pthread_create(&threads[t], NULL, evenFunction, (void *)t);
        }
        else
        {
            rc = pthread_create(&threads[t], NULL, oddFunction, (void *)t);
        }
        if (rc)
        {
            printf("ERORR; return code from pthread_create() is %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }
    pthread_exit(NULL);
}