
#pragma once

#include <arpa/inet.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>

#include "utils/hexToByte.h"


unsigned short calculateCRC(unsigned short *ptr, int nbytes) {
    long sum = 0;
    unsigned short oddByte;
    short crc;

    while (nbytes > 1) {
        sum += *ptr++;
        nbytes -= 2;
    }
    if (nbytes == 1) {
        oddByte = 0;
        *((unsigned char* )&oddByte) = *(unsigned char *)ptr;
        sum += oddByte;
    }

    sum = (sum >> 16) + (sum & 0xffff);
    sum = sum + (sum >> 16);
    crc = (short)~sum;
    return crc;
}


ErrorCode sendPacket(const void* buffer, size_t bufferSize)
{
    int sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sockfd < 0) {
        return SEN_SOCK_FAIL;
    }

    char buff[4096];
    memset(buff, 0, sizeof(buff));
    ethhdr* eth = (ethhdr *)buff;
    iphdr* iph = (iphdr*)(buff + sizeof(ethhdr));
    udphdr* udph = (udphdr*)(buff + sizeof(ethhdr) + sizeof(iphdr));
    char* data = buff + sizeof(ethhdr) + sizeof(iphdr) + sizeof(udphdr);

    char src[6];
    char dst[6];
    src[0] = (char) hexToByte('5', '8');
    src[1] = (char) hexToByte('1', '1');
    src[2] = (char) hexToByte('2', '2');
    src[3] = (char) hexToByte('B', 'E');
    src[4] = (char) hexToByte('9', 'C');
    src[5] = (char) hexToByte('7', 'C');

    dst[0] = (char) hexToByte('F', 'F');
    dst[1] = (char) hexToByte('F', 'F');
    dst[2] = (char) hexToByte('F', 'F');
    dst[3] = (char) hexToByte('F', 'F');
    dst[4] = (char) hexToByte('F', 'F');
    dst[5] = (char) hexToByte('F', 'F');

    memcpy(eth->h_source, src, 6);
    memcpy(eth->h_dest, dst, 6);
    eth->h_proto = htons(ETH_P_IP);

    const char* payload = "Test raw UDP packet";
    strcpy(data, payload);
    int payloadLen = strlen(payload);

    const char *src_ip = "127.0.0.1";
    const char *dst_ip = "127.0.0.1";

    iph->ihl = 5;
    iph->version = 4;
    iph->tos = 0;
    iph->tot_len = htons(sizeof(struct iphdr) + sizeof(struct udphdr) + payloadLen);
    iph->id = htons(54321);
    iph->frag_off = 0;
    iph->ttl = 64;
    iph->protocol = IPPROTO_UDP;
    // Zero before CRC calculation
    iph->check = 0;
    iph->saddr = inet_addr(src_ip);
    iph->daddr = inet_addr(dst_ip);

    iph->check = calculateCRC((unsigned short *)iph, sizeof(struct iphdr));

    udph->source = htons(12345);
    udph->dest = htons(8888);
    udph->len = htons(sizeof(struct udphdr) + payloadLen);
    udph->check = 0;

    const sockaddr_ll addr = {
        .sll_family = AF_PACKET,
        .sll_protocol = htons(ETH_P_ALL),
        .sll_ifindex = 2,
        .sll_halen = ETH_ALEN,
    };

    int totalSize = sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct udphdr) + payloadLen;
    if (sendto(sockfd, buff, totalSize, 0, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        close(sockfd);
        return SEN_SEND_ERROR;
    }
    close(sockfd);
    return OK;
}


