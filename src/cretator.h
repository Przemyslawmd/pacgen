
#pragma once

#include <array>
#include <arpa/inet.h>
#include <cstring>
#include <linux/if_ether.h>
#include <memory>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <sys/socket.h>
#include <tuple>

#include "defines/internetLayer.h"


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
    return static_cast<short>(~sum);
}


inline std::tuple<std::unique_ptr<char[]>, int> createPacket(const LinkLayer& link,
                                                             const InternetV4Layer& internet)
{
    auto buffer = std::make_unique<char[]>(1522);

    auto* const eth = reinterpret_cast<ethhdr*>(buffer.get());
    memcpy(eth->h_source, link.macSrc.data(), MAC_BYTES);
    memcpy(eth->h_dest, link.macDst.data(), MAC_BYTES);
    eth->h_proto = htons(link.ethType);

    auto* const iph = reinterpret_cast<iphdr*>(buffer.get() + sizeof(ethhdr));
    iph->ihl = IP_HDR_LEN_IN_WORDS_DEFAULT;
    iph->version = internet.ver;
    iph->ttl = internet.ttl;
    iph->saddr = htonl(internet.ipSrc);
    iph->daddr = htonl(internet.ipDst);

    auto* const udph = reinterpret_cast<udphdr*>(buffer.get() + sizeof(ethhdr) + sizeof(iphdr));
    char* const data = buffer.get() + sizeof(ethhdr) + sizeof(iphdr) + sizeof(udphdr);

    const char* payload = "Test raw UDP packet";
    strcpy(data, payload);
    int payloadLen = strlen(payload);

    iph->tos = 0;
    iph->tot_len = htons(sizeof(iphdr) + sizeof(udphdr) + payloadLen);
    iph->id = htons(54321);
    iph->frag_off = 0;

    iph->protocol = IPPROTO_UDP;
    // Zero before CRC calculation
    iph->check = 0;
    iph->check = calculateCRC((unsigned short *)iph, sizeof(iphdr));

    udph->source = htons(12345);
    udph->dest = htons(8888);
    udph->len = htons(sizeof(udphdr) + payloadLen);
    udph->check = 0;

    int totalSize = sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct udphdr) + payloadLen;
    return { std::move(buffer), totalSize };
}

