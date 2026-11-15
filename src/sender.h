
#pragma once

#include <arpa/inet.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <sys/socket.h>
#include <unistd.h>


constexpr ErrorCode sendPacket(const void* buffer, size_t totalSize)
{
    const int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sock < 0) {
        return SEN_SOCK_FAIL;
    }

    const sockaddr_ll addr = {
        .sll_family = AF_PACKET,
        .sll_protocol = htons(ETH_P_ALL),
        .sll_ifindex = 2,
        .sll_halen = ETH_ALEN,
    };

    const ssize_t res = sendto(sock, buffer, totalSize, 0, (sockaddr*)&addr, sizeof(addr));
    close(sock);
    return res < 0 ? SEN_SEND_ERROR : OK;
}

