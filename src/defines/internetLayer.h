
#pragma once

#include <array>
#include <map>
#include <cstdint>


struct InternetLayer
{
    std::byte protocol;
    std::byte ttl;
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

