
#pragma once

#include <cstdint>


struct TransportLayer
{
    virtual ~TransportLayer() = default;

    uint16_t portSrc;
    uint16_t portDst;
    uint16_t checkSum;
};


struct TransportLayerUDP : TransportLayer
{
    uint16_t dataLen;
};


struct TransportLayerTCP : TransportLayer
{
    uint32_t seqNum;
    uint32_t ackNum;
    uint16_t window;
};

