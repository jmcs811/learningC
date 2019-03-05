#include "echoserver.h"

int SocketDemoUtils_createTcpSocket() {
    int sockFd = 0;

    sockFd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockFd == -1)
        perror("SOCKET");

    //TODO: make socket reusable 
    int enable = 1;
    setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(sockFd));
    
    return sockFd;
}

int SocketDemoUtils_populateAddrInfo(char *port, char *ipAddr, struct sockaddr_in *addr) {
    addr->sin_family = AF_INET;
    inet_pton(AF_INET, ipAddr, &addr->sin_addr.s_addr);
    addr->sin_port = htons(8876);

    return 0;
}

int SocketDemoUtils_bind(int sockFd, struct sockaddr_in *addr) {
    if ((bind(sockFd, (struct sockaddr*)&addr, sizeof(*addr))) == 0) {
        printf("Its working");
        return 0;
    } else {
        printf("bind no good");
        return 1;
    }
}

int SocketDemoUtils_listen(int sockFd) {
    if(listen(sockFd, 5) < 0) {
        return 1;
    } else { 
        return 0;
    }
}
