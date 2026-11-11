
#pragma once

#include <map>
#include <string>

enum class ErrorCode
{
    OK,
    PAN_MAC_SRC,
    PAN_MAC_DST,
    PAN_IP4_SRC,
    PAN_IP4_DST,
    PAN_IP6_SRC,
    PAN_IP6_DST,
    SEN_SOCK_FAIL,
    SEN_BIND_ERROR,
};


using enum ErrorCode;
const std::map<ErrorCode, std::string> ErrorDesc
{
    { PAN_MAC_SRC, "Improper source MAC address, a proper pattern is XX:XX:XX:XX:XX:XX" },
    { PAN_MAC_DST, "Improper destination MAC address, a proper pattern is XX:XX:XX:XX:XX:XX" },
    { PAN_IP4_SRC, "Improper source IPv4 address" },
    { PAN_IP4_DST, "Improper destination IPv4 address" },
    { PAN_IP6_SRC, "Improper source IPv6 address" },
    { PAN_IP6_DST, "Improper destination IPv6 address" },
};

