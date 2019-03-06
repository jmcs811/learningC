#include "echoserver.h"
 
int main(int argc, char *argv[]) {
    int sockFd = 0, clientFd = 0, bytesReceived = 0, bytesSent = 0;
 
    struct sockaddr_in addr = {0};
    char *buf = NULL;
    if (argc != 3) {
        printf("***USAGE***\n./echoserver.h <ipaddr> <port>\nYou Must Specify The Port\n");    
        exit(EXIT_FAILURE);
    }
   
    //create a socket that can connect with TCP/IP
    if ((sockFd = SocketDemoUtils_createTcpSocket()) == -1) {
        exit(EXIT_FAILURE);
    }
 
    //populate the addr variable with the port and ip address
    SocketDemoUtils_populateAddrInfo(argv[2], argv[1], &addr);
 
    //bind the socket to the id address and port
    SocketDemoUtils_bind(&sockFd, &addr);
 
    //set upthe socket to be listening
    SocketDemoUtils_listen(sockFd);
   
 
    while(1) {
        //TODO: accept connection
        clientFd = SocketDemoUtils_accept(sockFd, &addr);
 
        //TODO: once connection is accepted, receive entire message
        // from the client and then send it back
        //SocketDemoUtils_recv();
   
        while(1) {
            //TODO: allocate memory for receiveing
           
            //TODO: receive the message until it has been completly recieved
 
            //TODO: send the message to the client
 
            //TODO: clena up buffer memory to aavoid memory leak
 
        }
        //TODO: shutdown connection with client gracefully
        //close();
    }
}