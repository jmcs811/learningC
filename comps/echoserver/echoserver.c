#include "socketutils.h"
 
int main(int argc, char *argv[]) {
    int sockFd = 0, clientFd = 0, bytesReceived = 0, bytesSent = 0;
    int bytesRecieved = 0;
    char buffer[BUFF_SIZE] = {0};
    struct sockaddr_in addr = {0};
    struct sockaddr_in clientAddr;
 
    /*
    * Make sure enough args are passed to the program
    */
    if (argc != 3) {
        printf("***USAGE***\n./echoserver <ipaddr> <port>\nYou Must Specify The Port\n");
        return 1;
    }
 
    /*
    * Set up Server: creates socket, populates addr,
    * binds, and listens. Ready for accept  
    */
    sockFd = SocketDemoUtils_serverInit(argv[1], argv[2], &addr);
    if (sockFd < 0) {
        return 1;
    }
 
    // acceptloop.
    while(1) {
        clientFd = SocketDemoUtils_accept(sockFd, &clientAddr);
        if (clientFd < 0) {
            break;
        }
 
        // recieve bytes and send back to client
        while(1) {
            bytesReceived = SocketDemoUtils_recv(clientFd, (char *)&buffer);
 
            if (!bytesReceived) break;
 
            if (bytesRecieved < 0) {
                break;
            }
 
            printf("Client said: %s", buffer);
 
            bytesSent = SocketDemoUtils_send(clientFd, (char *)&buffer, bytesReceived);
            if (bytesSent < 0) {
                break;
            }
            memset(buffer, 0, BUFF_SIZE);
        }
        memset(buffer, 0, BUFF_SIZE);
        SocketDemoUtils_cleanUp(clientFd);
   }
   SocketDemoUtils_cleanUp(sockFd);
   return 0;
}