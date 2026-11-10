
#pragma once

#include <memory>

#include "internetLayer.h"
#include "linkLayer.h"


struct PacketData
{
    std::unique_ptr<LinkLayer> linkLayer;
    std::unique_ptr<InternetLayer> internetLayer;
};

