#include "echoserver.h"

int main(int argc, char const *argv[]) {
    int sockFd = 0, clientFd = 0, bytesReceived = 0, bytesSent = 0;
    struct sockaddr_in adddr = {0};
    char *buf = NULL;

    if(argc != 3) {
        printf("***Correct Usage***\n./echoserver <ip_addr> <port>\n");
        exit(EXIT_FAILURE);
    }

    //create a socket that can connect with TCP/IP
    if ((sockFd = SocketDemoUtils_createTcpSocket()) == -1) {
        exit(EXIT_FAILURE);
    }

    //TODO: populate addr variable with the port and ip addr
    struct sockaddr_in my_addr;
    SocketDemoUtils_populateAddrInfo(argv[2], argv[1], &my_addr);

    //TODO: bind the socket to the ip addr and port
    printf("start bind");
    SocketDemoUtils_bind(sockFd, &my_addr);
    printf("end bind");

    //TODO: set up the socket to be listening
    SocketDemoUtils_listen(sockFd);

    while(1) {
        //TODO: accept connection

        //TODO: once conn is accepted recieve entire message
        // from the client then send it back
        while (1) {
            //TODO: allocate memory for recieving message

            //TODO: recieve the message until it has been completely recieved

            //TODO: send the message to the client

            //TODO: clean up the buffer to avoid mem leak
        }
        //TODO: shutdown the conn with client (gracefully)
    }
    return 0;
}
