#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define BUFLEN 512
#define PORT 8888

struct temperature
{
    int id;
    int seq;
    int value;
};

int main()
{
    SOCKET s;
    struct sockaddr_in server, si_other;
    int slen, recv_len;
    char buf[BUFLEN];
    WSADATA wsa;

    slen = sizeof(si_other);

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    printf("Initialised.\n");

    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d", WSAGetLastError());
    }
    printf("Socket created.\n");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    puts("Bind done");

    while (1)
    {
        printf("Waiting for data...");
        fflush(stdout);

        struct temperature temp;

        if ((recv_len = recvfrom(s, (char *)&temp, sizeof(temp), 0, (struct sockaddr *)&si_other, &slen)) == SOCKET_ERROR)
        {
            printf("recvfrom() failed with error code : %d", WSAGetLastError());
            exit(EXIT_FAILURE);
        }

        printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        printf("id : %d, seq : %d, value : %d \n", temp.id, temp.seq, temp.value);
    }

    closesocket(s);
    WSACleanup();

    return 0;
}
