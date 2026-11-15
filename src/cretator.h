
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


inline std::tuple<std::unique_ptr<char[]>, int> createPacket(const LinkLayer& linkLayer)
{
    auto buffer = std::make_unique<char[]>(1522);

    auto* const eth = reinterpret_cast<ethhdr*>(buffer.get());
    memcpy(eth->h_source, linkLayer.macSrc.data(), MAC_BYTES);
    memcpy(eth->h_dest, linkLayer.macDst.data(), MAC_BYTES);
    eth->h_proto = htons(linkLayer.ethType);

    auto* const iph = reinterpret_cast<iphdr*>(buffer.get() + sizeof(ethhdr));
    auto* const udph = reinterpret_cast<udphdr*>(buffer.get() + sizeof(ethhdr) + sizeof(iphdr));
    char* const data = buffer.get() + sizeof(ethhdr) + sizeof(iphdr) + sizeof(udphdr);

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

