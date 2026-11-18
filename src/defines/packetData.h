
#pragma once

#include <memory>

#include "layer/internet.h"
#include "layer/link.h"


struct PacketData
{
    std::unique_ptr<LinkLayer> linkLayer;
    std::unique_ptr<InternetLayer> internetLayer;
};

