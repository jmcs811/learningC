#include "socketutils.h"
 
int main(int argc, char *argv[])
{
    int serverFd = 0;
    int valread = 0;
    char buffer[BUFF_SIZE] = {0};
    struct sockaddr_in serv_addr = {0};
 
    /*
    * Make sure enough args are passed to the program
    */
    if (argc != 3) {
        printf("***USAGE***\n./echoclient <ipaddr> <port>\nYou Must Specify The Port\n");
        return 1;    
    }
 
    /*
    * Creates socket and populates addr information. Returns FD.
    * Ready for connect call
    */
    serverFd = SocketDemoUtils_networkInit(argv[1], argv[2], &serv_addr);
    if (serverFd < 0) {
        return 1;
    }
 
    int connStatus = connect(serverFd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr));
    if (connStatus < 0) {
        SocketDemoUtils_cleanUp(serverFd);
        return 1;
    }
 
    while(1) {
        printf("Enter Message: ");
        fgets(buffer, sizeof(buffer), stdin);
 
        int sent = SocketDemoUtils_send(serverFd, (char *)&buffer, strlen(buffer));
        if (sent < 0) {
            break;
        }
        memset(buffer, 0, BUFF_SIZE);
        valread = SocketDemoUtils_recv(serverFd, (char *)&buffer);
        if (valread < 0) {
            break;
        }
        printf("Server said: %s", buffer);
    }
    SocketDemoUtils_cleanUp(serverFd);
    return 0;
}