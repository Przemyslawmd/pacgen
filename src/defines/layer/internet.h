
#pragma once

#include <array>
#include <map>
#include <cstdint>


constexpr unsigned int IP_HDR_LEN_IN_WORDS_DEFAULT = 5;
constexpr unsigned int VER_IP_V4 = 4;
constexpr unsigned int VER_IP_V6 = 6;
constexpr unsigned int MAX_TTL = 255;

constexpr std::string KEY_IP_SRC = "IP_SRC";
constexpr std::string KEY_IP_DST = "IP_DST";
constexpr std::string KEY_TTL = "TTL";


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

    std::uint8_t ver;
    std::byte protocol;
    std::uint8_t ttl;

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

