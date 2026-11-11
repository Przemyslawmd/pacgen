
#pragma once

#include "defines/errors.h"


class Sender
{
public:
    Sender() = default;

    ErrorCode sendPacket(const void* buffer, size_t bufferSize);
};

