#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER "127.0.0.1"
#define BUFLEN 512
#define PORT 8888

int main(void)
{
    struct sockaddr_in si_other;
    int s, slen = sizeof(si_other);
    char buf[BUFLEN];
    char message[BUFLEN];
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
        for (int i = 0; i < 5; i++)
        {
            sequence++;
            message[i] = "id: " + id + ", sequence: " + sequence + ", value: " + rand() * 50 - 20;

            if (sendto(s, message[i], strlen(message[i]), 0, (struct sockaddr *)&si_other, slen) == SOCKET_ERROR)
            {
                printf("sendto() failed with error code : %d", WSAGetLastError());
                exit(EXIT_FAILURE);
            }

            memset(buf, '\0', BUFLEN);
            // try to receive some data, this is a blocking call
            if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *)&si_other, &slen) == SOCKET_ERROR)
            {
                printf("recvfrom() failed with error code : %d", WSAGetLastError());
                exit(EXIT_FAILURE);
            }

            puts(buf);
        }
    }

    closesocket(s);
    WSACleanup();

    return 0;
}
