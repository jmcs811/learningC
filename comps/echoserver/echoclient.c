#include "echoserver.h"

int main(int argc, char *argv[])
{
    struct sockaddr_in client_addr, serv_addr;
    int sockFd;
    char *hello = "Hello from client";
    char buffer[100] = {0};

    if (argc != 3) {
        printf("***USAGE***\n./echoclient <ipaddr> <port>\n");
        exit(EXIT_FAILURE);
    }

    if ((sockFd = SocketDemoUtils_createTcpSocket()) == -1) {
        exit(EXIT_FAILURE);
    }

    SocketDemoUtils_populateAddrInfo(argv[2], argv[1], &serv_addr);

    if (connect(sockFd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection failed\n");
        return -1;
    }

    send(sockFd, hello, strlen(hello), 0);
    printf("sent message");
    read(sockFd, buffer, 100);
    printf("%s", buffer);

    return 0;
}
