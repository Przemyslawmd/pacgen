
#pragma once

#include <array>
#include <map>
#include <cstdint>


enum class Protocol
{
    ICMP,
    IGMP,
    TCP,
    UDP,
    IPv6,
    GRE,
    ESP,
    AH,
    ICMPv6,
    OSPF,
    SCTP,
};


const std::map<Protocol, uint8_t> ProtocolVal
{
    { Protocol::ICMP,   1 },
    { Protocol::IGMP,   2 },
    { Protocol::TCP,    6 },
    { Protocol::UDP,    17 },
    { Protocol::IPv6,   41 },
    { Protocol::GRE,    47 },
    { Protocol::ESP,    50 },
    { Protocol::AH,     51 },
    { Protocol::ICMPv6, 58, },
    { Protocol::OSPF,   89 },
    { Protocol::SCTP,   132 },
};


struct InternetLayer
{
    virtual ~InternetLayer() = default;
    std::byte protocol;
    std::byte ttl;

    std::optional<uint8_t> headerLen;
    std::optional<uint16_t> id;

    bool dontFragment;
    bool moreFragments;
};


struct InternetV4Layer : InternetLayer
{
    uint32_t ipSrc;
    uint32_t ipDst;
};


struct InternetV6Layer : InternetLayer
{
    std::array<std::byte, 16> ipSrc;
    std::array<std::byte, 16> ipDst;
};

