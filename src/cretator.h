
#pragma once

#include <array>
#include <memory>
#include "utils/hexToByte.h"

#include <arpa/inet.h>
#include <linux/if_ether.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <sys/socket.h>
#include <cstring>
#include <tuple>


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


inline std::tuple<std::unique_ptr<char[]>, int> createPacket()
{
    auto buffer = std::make_unique<char[]>(1522);

    ethhdr* eth = (ethhdr *) buffer.get();
    iphdr* iph = (iphdr*)(buffer.get() + sizeof(ethhdr));
    udphdr* udph = (udphdr*)(buffer.get() + sizeof(ethhdr) + sizeof(iphdr));
    char* data = buffer.get() + sizeof(ethhdr) + sizeof(iphdr) + sizeof(udphdr);

    std::array<std::byte, 6> src;
    std::array<std::byte, 6> dst;;
    macStrToBytes("58:11:22:BE:9C:7C", src);
    macStrToBytes("FF:FF:FF:FF:FF:FF", dst);
    memcpy(eth->h_source, src.data(), 6);
    memcpy(eth->h_dest, dst.data(), 6);
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

    int totalSize = sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct udphdr) + payloadLen;
    return { std::move(buffer), totalSize };
}

