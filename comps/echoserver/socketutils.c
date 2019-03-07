#include "echoserver.h"

 /**********************
 * ****Create Socket****
 * ********************/
int SocketDemoUtils_createTcpSocket() {
    int sockFd = 0;
   
    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd == -1) {
        perror("socket");
        exit(1);
    }
    int enable = 1;
    setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
   
    return sockFd;
}
 
 /***********************
 * ***Update ADDR INFO***
 * *********************/
int SocketDemoUtils_populateAddrInfo(char *port, char *ipAddr, struct sockaddr_in *addr) {
    short shortPort = atoi(port);
    addr->sin_family = AF_INET;
    inet_pton(AF_INET, ipAddr, &(addr->sin_addr));
    addr->sin_port = htons(shortPort);
    return 0;
}
 
 /************************
 * ********BIND***********
 * **********************/
int SocketDemoUtils_bind(int *sockFd, struct sockaddr_in *addr) {
    if (bind(*sockFd, (struct sockaddr *) addr, sizeof(struct sockaddr)) < 0) {
        printf("wrong");
        exit(EXIT_FAILURE);
    }
}
 
 /************************
 * ********LISTEN*********
 * **********************/
int SocketDemoUtils_listen(int sockFd) {
    if (listen(sockFd, 5) == 0) {
        printf("listenin\n");
    }
    return 0;
}

 /************************
 * ********ACCEPT*********
 * **********************/
int SocketDemoUtils_accept(int sockFd, struct sockaddr_in *addr) {
    if (accept(sockFd, (struct sockaddr*) addr, sizeof(struct sockaddr)) > 0) {
        printf("conencted");
    }
}
