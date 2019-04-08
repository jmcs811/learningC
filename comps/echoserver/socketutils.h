#ifndef __SOCKETUTILS_H
#define __SOCKETUTILS_H
 
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
 
#define BUFF_SIZE 1024
 
//protos
int SocketDemoUtils_serverInit(char *ip, char *port, struct sockaddr_in *addr);
int SocketDemoUtils_networkInit(char *ip, char *port, struct sockaddr_in *addr);
int SocketDemoUtils_populateAddrInfo(char *port, char *ipAddr, struct sockaddr_in *addr);
int SocketDemoUtils_accept(int sockFd, struct sockaddr_in *addr);
int SocketDemoUtils_recv(int sockFd, char *buf);
int SocketDemoUtils_send(int sockFd, char *buf, int numBytes);
int SocketDemoUtils_cleanUp(int sockFd);
int isValidPort(int portNumber);
int isValidIp(char *ip, struct sockaddr_in *addr);
int getIntInput(char*, int*);
 
#endif
