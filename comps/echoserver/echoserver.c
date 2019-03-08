#include "echoserver.h"
 
int main(int argc, char *argv[]) {
    int sockFd = 0, clientFd = 0, bytesReceived = 0, bytesSent = 0;
 
    struct sockaddr_in addr = {0};
    char *buf = NULL;
    char *hello = "Hello from client";
    char buffer[100] = {0};
    if (argc != 3) {
        printf("***USAGE***\n./echoserver.h <ipaddr> <port>\nYou Must Specify The Port\n");    
        exit(EXIT_FAILURE);
    }
   
    //create a socket that can connect with TCP/IP
    if ((sockFd = SocketDemoUtils_createTcpSocket()) == -1) {
        exit(EXIT_FAILURE);
    }
 
    //populate the addr variable with the port and ip address
    if (SocketDemoUtils_populateAddrInfo(argv[2], argv[1], &addr) != 0) {
        printf("ADDR INFO NOT UPDATED\n");
        exit(EXIT_FAILURE);
    }
 
    //bind the socket to the id address and port
    if (SocketDemoUtils_bind(&sockFd, &addr) != 0) {
        printf("BIND FAILUED\n");
        exit(EXIT_FAILURE);
    }
 
    //set upthe socket to be listening
    if (SocketDemoUtils_listen(sockFd) != 0) {
        printf("LISTEN FAILED");
        exit(EXIT_FAILURE);
    }
   
 
    while(1) {
        //TODO: accept connection
        clientFd = SocketDemoUtils_accept(sockFd, &addr);
 
        //TODO: once connection is accepted, receive entire message
        // from the client and then send it back
        //SocketDemoUtils_recv();
   
        //while(1) {
            //TODO: allocate memory for receiveing
           
            //TODO: receive the message until it has been completly recieved
 
            //TODO: send the message to the client
 
            //TODO: clena up buffer memory to aavoid memory leak
 
        //}
        //TODO: shutdown connection with client gracefully
        //close();
    }
    close(clientFd);
}