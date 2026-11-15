
#pragma once

#include <cstdint>
#include <array>
#include <map>


const std::map<unsigned char, uint8_t> xxx
{
    { '0', 0 }, { '1', 1 }, { '2', 2 },  { '3', 3 },   { '4', 4 },  { '5', 5 },  { '6', 6 },  { '7', 7 },
    { '8', 8 }, { '9', 9 }, { 'A', 10 }, { 'B', 11 },  { 'C', 12 }, { 'D', 13 }, { 'E', 14 }, { 'F', 15 },
};


constexpr std::byte hexToByte(const unsigned char hex_1, const unsigned char hex_2)
{
    uint8_t val = xxx.at(hex_1);
    val <<= 4;
    val += xxx.at(hex_2);
    return static_cast<std::byte>(val);
}


constexpr void macStrToBytes (const std::string& macStr, std::array<std::byte, MAC_BYTES>& arr) {
    for (unsigned int i = 0, j = 0; i < MAC_BYTES; i++, j += 3) {
        arr[i] = hexToByte(macStr[j], macStr[j + 1]);
    }
};

