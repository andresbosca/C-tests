#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *firstThreadFun()
{
    printf("It's me a Mario \n");
}

void *secondThreadFun()
{
    printf("It's not me a Mario \n");
}

int main()
{
    pthread_t tid;

    pthread_create(&tid, NULL, firstThreadFun, (void *)&tid);

    pthread_create(&tid, NULL, secondThreadFun, (void *)&tid);

    pthread_exit(NULL);
    return 0;
}