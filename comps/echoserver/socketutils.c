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
    // convert char[] to int
    char *ptr;
    int shortPort = strtol(port, &ptr, 10);

    // set addr properties
    addr->sin_family = AF_INET;

    // convert char ip to net. byte order & 
    // test to make sure IP is valid
    if (inet_pton(AF_INET, ipAddr, &(addr->sin_addr)) != 1) {
        printf("%s IS NOT A VALID IP\n", ipAddr);
        exit(EXIT_FAILURE);
    }

    // test if port number is in valid range
    if(shortPort < 0 || shortPort > 65535) {
        printf("%s IS NOT A VALID PORT NUMBER\n", port);
        exit(EXIT_FAILURE);
    }
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
    return 0;
}
 
 /************************
 * ********LISTEN*********
 * **********************/
int SocketDemoUtils_listen(int sockFd) {
    if (listen(sockFd, 5) == 0) {
        printf("listenin\n");
        return 0;
    }
    return 1;
}

 /************************
 * ********ACCEPT*********
 * **********************/
int SocketDemoUtils_accept(int sockFd, struct sockaddr_in *addr) {
    if (accept(sockFd, (struct sockaddr*) addr, sizeof(struct sockaddr)) > 0) {
        printf("conencted");
        return 0;
    }
    return 1;
}

 /************************
 * *********SEND**********
 * **********************/
int SocketDemoUtils_send(int sockFd, char *buf, int numBytes) {
    return 0;
}

 /************************
 * *********RECV**********
 * **********************/
int SocketDemoUtils_recv(int sockFd, char **buf) {
    return 0;
}