
#pragma once

#include <QTabWidget>

#include "packetPanelLink.h"
#include "defines/linkLayer.h"


class PacketPanel
{
public:
    PacketPanel() = default;

    QTabWidget* init();

    std::unique_ptr<LinkLayer> getLinkLayerData();

private:
    std::unique_ptr<PacketPanelLink> tabLink;

};

