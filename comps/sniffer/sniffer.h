#ifndef __SNIFFER_H
#define __SNIFFER_H
 
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <signal.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/ip.h>
#include <linux/icmp.h>
#include <net/ethernet.h>
#include <linux/if_ether.h>
#include <string.h>
 
#define BUFF_SIZE 1024
 
//protos
void processPacket(unsigned char *);
void initIpPacket(unsigned char *);
void printTcpUdpPacket(unsigned char *, char *);
void printUdpPacket(unsigned char *);
void printIcmpPacket(unsigned char *);
void handle_sigint();
#endif