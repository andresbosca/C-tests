#include <stdio.h>
#include <winsock2.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER "127.0.0.1"
#define BUFLEN 512
#define PORT 8888

struct temperature
{
    int id;
    int seq;
    int value;
};

void *sendToServer(SOCKET s, struct sockaddr_in si_other, int slen, struct temperature temp)
{
    if (sendto(s, &temp, sizeof(temp), 0, (struct sockaddr *)&si_other, slen) == SOCKET_ERROR)
    {
        printf("sendto() failed with error code : %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    printf("Data Sent. Id : %d. \n", temp.id);
}

int main(void)
{
    struct sockaddr_in si_other;
    int s, slen = sizeof(si_other);
    char buf[BUFLEN];
    char message[5][BUFLEN];
    int sequence = 0;
    WSADATA wsa;

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    printf("Initialised.\n");

    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
    {
        printf("socket() failed with error code : %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    memset((char *)&si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
    si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

    // start random data
    srand(time(NULL));

    while (1)
    {
        pthread_t thread[10];
        for (int i = 0; i < 10; i++)
        {
            sequence++;
            struct temperature temp;

            temp.id = i + 1;
            temp.seq = sequence;
            temp.value = rand() % 50 - 20;

            pthread_create(&thread[i], NULL, sendToServer(s, si_other, slen, temp), NULL);

            // if (sendto(s, &temp, sizeof(temp), 0, (struct sockaddr *)&si_other, slen) == SOCKET_ERROR)
            // {
            //     printf("sendto() failed with error code : %d", WSAGetLastError());
            //     exit(EXIT_FAILURE);
            // }
        }
        for (int i = 0; i < 10; i++)
        {
            pthread_join(thread[i], NULL);
        }
        pthread_exit(NULL);
        sleep(5);
    }

    closesocket(s);
    WSACleanup();

    return 0;
}
