#include "socketutils.h"
 
 /***********************
 * ***Update ADDR INFO***
 * *********************/
int SocketDemoUtils_populateAddrInfo(char *port, char *ipAddr, struct sockaddr_in *addr) {
    // convert char* to int and chack range
    int intPort;
    if (getIntInput(port, &intPort) != 0) {
        printf("Error getting input\n");
        return 1;
    }
 
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
 * *****NETWORK INIT******
 * **********************
 * Basic socket craeted
 * and addr info updated
 */
 
int SocketDemoUtils_networkInit(char *ip, char *port, struct sockaddr_in *addr) {
     // create socket
    int sock = 0;
 
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket");
        return -1;
    }
 
    // set seockopt reuseable
    int enable = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) != 0) {
        printf("Error setting sockopt\n");
        return -1;
    }
 
    // update addr information
    if (SocketDemoUtils_populateAddrInfo(port, ip, addr) != 0) {
        return -1;
    }
    return sock;
}
 
 /************************
 * ******SERVER INIT******
 * **********************
 * Calls networkInit to
 * create socket and update
 * addr info. Then calls
 * bind and listen
 */
int SocketDemoUtils_serverInit(char *ip, char *port, struct sockaddr_in *addr) {
    // create socket
    int sock = 0;
 
    sock = SocketDemoUtils_networkInit(ip, port, addr);
    if (sock < 0) {
        return -1;
    }
 
    // bind socket
    if (bind(sock, (struct sockaddr *)addr, sizeof(struct sockaddr)) != 0) {
        printf("error binding\n");
        return -1;
    }
 
    // listen
    if (listen(sock, 5) != 0) {
        printf("error listening\n");
        return -1;
    }
    return sock;
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
int SocketDemoUtils_recv(int sockFd, char *buf) {
    int numBytes = recv(sockFd, buf, BUFF_SIZE, 0);
    if (numBytes < 0) {
        printf("Error recv'ing\n");
        return -1;
    }
    return numBytes;
}
 
 /************************
 * *********SEND**********
 * **********************/
int SocketDemoUtils_send(int sockFd, char *buf, int numBytes){
    int sent = send(sockFd, buf, numBytes, 0);
 
    if (sent < 0) {
        printf("Error Sending\n");
        return -1;
    }
    return sent;
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
 
 /************************
 * *******CLEANUP*********
 * **********************/
int SocketDemoUtils_cleanUp(int sockFd) {
    if (shutdown(sockFd, SHUT_RDWR) != 0) {
        return 1;
    }
    return 0;
}
 
int getIntInput(char *finalString, int *result) {
    long tmp;
    char *endptr;
 
    // Convert String to long int
    tmp = strtol(finalString, &endptr, 10);
 
    // check for various possible errors
    if (((tmp == LONG_MAX || tmp == LONG_MIN))) {
        perror("strotol");
        return 1;
    }
 
    if (endptr == finalString) {
        //fprintf(stderr, "No digits were found\n");
        return 1;
    }
 
    if (!(*endptr == '\0' || *endptr == '\n')) {
        fprintf(stderr, "Invalid characters\n");
        return 1;
    }
 
    if (tmp >= INT_MIN && tmp <= INT_MAX) {
        *result = tmp;
        return 0;
    } else {
        fprintf(stderr, "Number out of range\n");
        return 1;
    }
}