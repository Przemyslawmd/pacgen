
#include "sender.h"

#include <arpa/inet.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <sys/socket.h>


ErrorCode Sender::sendPacket(const void* buffer, size_t bufferSize)
{
    int sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sockfd < 0) {
        return SEN_SOCK_FAIL;
    }

    const sockaddr_ll addr = {
        .sll_family = AF_PACKET,
        .sll_protocol = htons(ETH_P_ALL),
        .sll_ifindex = 0,
    };
    if (bind(sockfd, (sockaddr*) &addr, sizeof(addr)) < 0) {
         return SEN_BIND_ERROR;
    }

    sendto(sockfd, buffer, bufferSize, 0, (sockaddr*) &addr, sizeof(addr));
    return OK;
}


