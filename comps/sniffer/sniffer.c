#include "sniffer.h"
 
// globals are already zeroized
int total;
int udp;
int tcp;
int icmp;
int others;
struct sockaddr_in source, dest;
char srcBuf[INET_ADDRSTRLEN];
char dstBuf[INET_ADDRSTRLEN];
 
int main() {
 
    int sock_raw;
   
    signal(SIGINT, handle_sigint);
 
    /*
    * Create RAW socket using SOCK_DGRAM to ignore
    * ethernet headers, and ETH_P_ALL to get all
    * packets reguardless of protocol
    */
    sock_raw = socket(AF_PACKET, SOCK_DGRAM, htons(ETH_P_ALL));
    if (sock_raw == -1) {
        printf("Error createing socket\nMust be root (or sudo)\n");
        exit(1);
    }
 
    /*
    * malloc packet size
    */
    unsigned char *packet = malloc(1024 * 4);
 
    // Recieve loop
    while(1) {
        int data_size;
        data_size = recvfrom(sock_raw, packet, 4096, 0, NULL, NULL);
        if (data_size == -1) {
            printf("Error recv'ing\n");
            exit(1);
        }
        processPacket(packet);
    }
    close(sock_raw);
    free(packet);
    return 0;
}
 
/*
* Read packet and get the protocol in
* the ip header. Call the corresponding
* function based on protocol. Add to the
* running totals.
*/
void processPacket(unsigned char *packet) {
    struct iphdr *iph = (struct iphdr*)packet;
    total++;
 
    switch(iph->protocol) {
        // ICMP
        case IPPROTO_ICMP:
            icmp++;
            printIcmpPacket(packet);
            break;
        // TCP
        case IPPROTO_TCP:
            tcp++;
            printTcpUdpPacket(packet, "TCP");
            break;
        // UDP
        case IPPROTO_UDP:
            udp++;
            printTcpUdpPacket(packet, "UDP");
            break;
        // Others
        default :
            others++;
            break;
    }
}
 
/*
* Set the source and dest ip addrs for
* each packet
*/
void initIpPacket(unsigned char* buffer) {
    struct iphdr *iph = (struct iphdr*) buffer;
 
    /*
    * clear out struct and set the ip addr
    */
    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = iph->saddr;
 
    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = iph->daddr;
 
    const char *srcIp = inet_ntop(AF_INET, &source.sin_addr, srcBuf, INET_ADDRSTRLEN);
    if (srcIp  == NULL) {
        printf("Error getting src port\n");
    }
 
    const char *dstIp = inet_ntop(AF_INET, &source.sin_addr, srcBuf, INET_ADDRSTRLEN);
    if (dstIp == NULL) {
        printf("Error getting dst port\n");
    }
 
 
    printf("%s -> %s", srcIp, dstIp);
}
 
/*
* Call initIpPacket to get src and dst ip
* addr. Get src and dest port from tcp header
* print out tcp packet
*/
void printTcpUdpPacket(unsigned char *buffer, char *protocol) {
    unsigned short iphdrlen;
 
    struct iphdr *iph = (struct iphdr *)buffer;
    iphdrlen = iph->ihl*4;
 
    struct tcphdr *tcph = (struct tcphdr*)(buffer + iphdrlen);
 
    int srcPort = ntohs(tcph->source);
    int dstPort = ntohs(tcph->dest);
    initIpPacket(buffer);
 
    printf("%d:%d [%s]\n", srcPort, dstPort, protocol);
 
}
 
/*
* ICMP does not have ports. Just show srcs and
* dst ip addr. Could show type and code but not
* sure if its necessary
*/
void printIcmpPacket(unsigned char *buffer) {
    initIpPacket(buffer);
    printf("[ICMP]\n");
}
 
/*
* Print totals and exit the program after
* pressing CTRL+C
*/
void handle_sigint() {
    printf("\nTCP: %d\nUDP: %d\nICMP: %d\n", tcp, udp, icmp);
    exit(0);
}