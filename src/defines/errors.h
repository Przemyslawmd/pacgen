
#pragma once


enum class ErrorCode
{
    OK,

    PAN_MAC_SRC,
    PAN_MAC_DST,
};


using enum ErrorCode;
const std::map<ErrorCode, std::string> ErrorDesc
{
    { PAN_MAC_SRC, "Improper source MAC address" },
    { PAN_MAC_DST, "Improper destination MAC address" },
};

