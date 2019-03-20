#include "echoserver.h"
 
int main(int argc, char *argv[])
{
    int serverFd = 0;
    int valread = 0;
    char *hello = "Hello, world!\n";
    char buffer[BUFF_SIZE] = {0};
    struct sockaddr_in serv_addr = {0};
 
    if (argc != 3) {
        printf("***USAGE***\n./echoclient <ipaddr> <port>\n");
    }
 
    if ((serverFd = SocketDemoUtils_createTcpSocket()) == -1) {
        printf("error in creating client socket\n");
        exit(EXIT_FAILURE);
    }
 
    if (SocketDemoUtils_populateAddrInfo(argv[2], argv[1], &serv_addr) != 0) {
        printf("Error Updating addr info\n");
        exit(EXIT_FAILURE);
    }
 
    int connStatus = connect(serverFd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr));
    if (connStatus < 0) {
        printf("Error Connecting");
        exit(EXIT_FAILURE);
    }
 
    while(1) {
        fgets(buffer, sizeof(buffer), stdin);
 
        int sent = send(serverFd, buffer, strlen(buffer), 0);
        printf("message sent\n%d bytes sent\n", sent);
        valread = read(serverFd, buffer, BUFF_SIZE);
        printf("Server said: %s\n", buffer);
    }
   
    return 0;
}