
#pragma once

#include <array>
#include <map>
#include <cstdint>


constexpr unsigned int MAC_BYTES = 6;


enum class EthType
{
    IPV4,
    IPV6,
    ARP,
    IEEE_802_1AD,
};


const std::map<EthType, uint16_t> EthTypeVal
{
    { EthType::IPV4,         0x0800 },
    { EthType::IPV6,         0x86DD },
    { EthType::ARP,          0x0806 },
    { EthType::IEEE_802_1AD, 0x8100 }
};


struct LinkLayer
{
    std::array<std::byte, MAC_BYTES> macSrc;
    std::array<std::byte, MAC_BYTES> macDst;
    uint16_t ethType;
};

