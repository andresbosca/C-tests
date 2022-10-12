#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#ifndef TOTAL_LINES
#define TOTAL_LINES 100
#endif
#ifndef TOTAL_COLUMNS
#define TOTAL_COLUMNS 100
#endif

void fillMatrix(int matrixA[TOTAL_LINES][TOTAL_COLUMNS], int matrixB[TOTAL_LINES][TOTAL_COLUMNS])
{
    srand(time(NULL));
    for (int i = 0; i < TOTAL_LINES; i++)
    {
        for (int j = 0; j < TOTAL_COLUMNS; j++)
        {
            matrixA[i][j] = rand() % 100;
            matrixB[i][j] = rand() % 100;
        }
    }
}

int matrixA[TOTAL_LINES][TOTAL_COLUMNS];
int matrixB[TOTAL_LINES][TOTAL_COLUMNS];
int matrixC[TOTAL_LINES][TOTAL_COLUMNS];
int step_i = 0;

void *multi(void *threadNumber)
{
    long threadNumberInt = (long)threadNumber;
    printf("Sou o Processo - %lu \n", pthread_self());
    int i, j, k;
    int core = step_i++;
    for (i = core * TOTAL_LINES / threadNumberInt; i < (core + 1) * TOTAL_LINES / threadNumberInt; i++)
    {
        for (j = 0; j < TOTAL_COLUMNS; j++)
        {
            for (k = 0; k < TOTAL_COLUMNS; k++)
            {
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

void printMatrix(int matrix[TOTAL_LINES][TOTAL_COLUMNS])
{
    for (int i = 0; i < TOTAL_LINES; i++)
    {
        for (int j = 0; j < TOTAL_COLUMNS; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void calculateMatrix(long threadNumber)
{
    pthread_t threads[threadNumber];

    fillMatrix(matrixA, matrixB);

    printMatrix(matrixA);
    printf("\n");
    printMatrix(matrixB);
    printf("\n");

    for (int i = 0; i < threadNumber; i++)
    {
        int *p;
        pthread_create(&threads[i], NULL, multi, (void *)(threadNumber));
    }

    for (int i = 0; i < threadNumber; i++)
        pthread_join(threads[i], NULL);

    printMatrix(matrixC);

    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    int threadNumber = 1;
    calculateMatrix(threadNumber);
}
