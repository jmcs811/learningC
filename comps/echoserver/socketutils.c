#include "echoserver.h"
 
 /**********************
 * ****Create Socket****
 * ********************/
int SocketDemoUtils_createTcpSocket() {
    int sockFd = 0;
   
    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd == -1) {
        perror("socket");
        return -1;
    }
    int enable = 1;
    if (setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) != 0) {
        printf("Error setting sockopt\n");
        return -1;
    }
    //printf("%d sockfd In function\n", sockFd);
    return sockFd;
}
 
 /***********************
 * ***Update ADDR INFO***
 * *********************/
int SocketDemoUtils_populateAddrInfo(char *port, char *ipAddr, struct sockaddr_in *addr) {
    // convert char* to int and chack range
    int intPort = atoi(port);
    if (isValidPort(intPort) != 1) {
        printf("INVALID PORT\n");
        return 1;
    }
 
    addr->sin_family = AF_INET;
 
    // convert char* to ip and check validity
    if (isValidIp(ipAddr, addr) != 0) {
        printf("Invalid IP\n");
        return 1;
    }
    addr->sin_port = htons(intPort);
    return 0;
}
 
 /************************
 * ********BIND***********
 * **********************/
int SocketDemoUtils_bind(int sockFd, struct sockaddr_in *addr) {
    if (bind(sockFd, (struct sockaddr *) addr, sizeof(struct sockaddr)) != 0) {
        printf("Error Binding\n");
        return -1;
    }
    return 0;
}
 
 /************************
 * ********LISTEN*********
 * **********************/
int SocketDemoUtils_listen(int sockFd) {
    if (listen(sockFd, 5) != 0) {
        printf("Error listening\n");
        return 1;
    }
    return 0;
}
 
 /************************
 * ********ACCEPT*********
 * **********************/
int SocketDemoUtils_accept(int sockFd, struct sockaddr_in *addr) {
    socklen_t addrLen = sizeof(struct sockaddr_in);
    int clientFd = accept(sockFd, (struct sockaddr*) &addr, &addrLen);
    if (clientFd > 0) {
        printf("conencted\n");
        return clientFd;
    } else {
        printf("ERROR ACCEPTING\n");
        return -1;
    }
}
 
 /************************
 * *********RECV**********
 * **********************/
int SocketDemoUtils_recv(int sockFd, char **buf) {
    return 0;
}
 
 /************************
 * *********SEND**********
 * **********************/
int SocketDemoUtils_send(int sockFd, char *buf, int numBytes){
    return 0;
}
 
 /************************
 * ******VALIDPORT********
 * **********************/
int isValidPort(int portNumber) {
    // check if in range (0-65535)
    if (portNumber > 0 && portNumber <= 65535) {
        return 1;
    }
    return 0;
}
 
 /************************
 * *******VALIDIP*********
 * **********************/
int isValidIp(char *ip, struct sockaddr_in *addr) {
    int result = inet_pton(AF_INET, ip, &(addr->sin_addr));
    // success
    if (result == 1) {
        return 0;
    }
    // src does not contain a character string
    if (result == 0) {
        printf("input is not a string\n");
        return 1;
    }
    //af does not contain a valid address
    if (result == -1) {
        printf("Incorrect addr family\n");
        return 1;
    }
    return 0;
}
