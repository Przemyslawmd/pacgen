
#pragma once

#include <arpa/inet.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <sys/socket.h>
#include <unistd.h>


ErrorCode sendPacket(const void* buffer, size_t totalSize)
{
    int sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sockfd < 0) {
        return SEN_SOCK_FAIL;
    }

    const sockaddr_ll addr = {
        .sll_family = AF_PACKET,
        .sll_protocol = htons(ETH_P_ALL),
        .sll_ifindex = 2,
        .sll_halen = ETH_ALEN,
    };

    int res = sendto(sockfd, buffer, totalSize, 0, (sockaddr *)&addr, sizeof(addr));
    close(sockfd);
    return res < 0 ? SEN_SEND_ERROR : OK;
}

