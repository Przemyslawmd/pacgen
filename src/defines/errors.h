
#pragma once

#include <map>
#include <string>


enum class ErrorCode
{
    OK,

    CON_FILE,
    CON_STREAM,

    FILE_NO_MAC_STR,
    FILE_NO_MAC_DST,
    FILE_NO_ETH_TYPE,

    PAN_MAC_SRC,
    PAN_MAC_DST,
    PAN_IP4_SRC,
    PAN_IP4_DST,
    PAN_IP6_SRC,
    PAN_IP6_DST,
    PAN_TTL,

    SEN_SOCK_FAIL,
    SEN_SEND_ERROR,
};


using enum ErrorCode;
const std::map<ErrorCode, std::string> ErrorDesc
{
    { CON_STREAM, "Controller: File stream error" },
    { CON_FILE, "Controller: File read error" },

    { FILE_NO_MAC_STR, "File: No source MAC address in the file" },
    { FILE_NO_MAC_DST, "File: No destination MAC address in the file" },
    { FILE_NO_ETH_TYPE, "File: No Eth Type in the file" },

    { PAN_MAC_SRC, "Panel: Improper source MAC address, a proper pattern is XX:XX:XX:XX:XX:XX" },
    { PAN_MAC_DST, "Panel: Improper destination MAC address, a proper pattern is XX:XX:XX:XX:XX:XX" },
    { PAN_IP4_SRC, "Panel: Improper source IPv4 address" },
    { PAN_IP4_DST, "Panel: Improper destination IPv4 address" },
    { PAN_IP6_SRC, "Panel: Improper source IPv6 address" },
    { PAN_IP6_DST, "Panel: Improper destination IPv6 address" },
    { PAN_TTL, "Panel: Improper TTL value, it must be integer in range { 0 - 255 }" },

    { SEN_SOCK_FAIL, "Sender: Socker error" },
    { SEN_SEND_ERROR, "Sender: Sending packet error" },
};

