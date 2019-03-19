#include "echoserver.h"
 
int main(int argc, char *argv[]) {
    int sockFd = 0, clientFd = 0, bytesReceived = 0, bytesSent = 0;
    int valread = 0;
    char buffer[BUFF_SIZE] = {0};
    struct sockaddr_in addr = {0};
    struct sockaddr_in clientAddr;
    char *buf = NULL;
  
    if (argc != 3) {
        printf("***USAGE***\n./echoserver <ipaddr> <port>\nYou Must Specify The Port\n");    
        exit(EXIT_FAILURE);
    }
   
    //create a socket that can connect with TCP/IP
    if ((sockFd = SocketDemoUtils_createTcpSocket()) == -1) {
        exit(EXIT_FAILURE);
    }
 
    //populate the addr variable with the port and ip address
    if (SocketDemoUtils_populateAddrInfo(argv[2], argv[1], &addr) != 0) {
        printf("Error Updating addr info\n");
        exit(EXIT_FAILURE);
    }
 
    //bind the socket to the ip address and port
    if (SocketDemoUtils_bind(sockFd, &addr) != 0) {
        printf("Error Binding\n");
        exit(EXIT_FAILURE);
    }
 
    //set upthe socket to be listening
    if (SocketDemoUtils_listen(sockFd) != 0) {
        printf("Error Listening");
        exit(EXIT_FAILURE);
    }
 
 
    while(1) {
        //TODO: accept connection
        clientFd = SocketDemoUtils_accept(sockFd, &clientAddr);
        if (clientFd < 0) {
            printf("Error Accecpting\n");
            exit(EXIT_FAILURE);
        }
       
        //TODO: once connection is accepted, receive entire message
        // from the client and then send it back
        //SocketDemoUtils_recv();
 
        while(1) {
            //TODO: allocate memory for receiveing
           
            //TODO: receive the message until it has been completly recieved
 
            //TODO: send the message to the client
 
            //TODO: clean up buffer memory to avoid memory leak
 
            int valRead = recv(clientFd, buffer, BUFF_SIZE, 0);
 
            if (!valRead) break;
 
            if (valRead < 0) {
                printf("Error reading\n");
                exit(EXIT_FAILURE);
            }
 
            printf("Client said: %s", buffer);
 
            int sent = send(clientFd, buffer, valRead, 0);
        }
        memset(buffer, 0, BUFF_SIZE);
        //TODO: shutdown connection with client gracefully
        close(clientFd);
   }
   return 0;
}