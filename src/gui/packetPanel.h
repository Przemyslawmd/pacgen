
#pragma once

#include <QTabWidget>

#include "tabLink.h"
#include "tabInternet.h"
#include "defines/packetData.h"
#include "defines/linkLayer.h"


class PacketPanel
{
public:
    PacketPanel() = default;

    QTabWidget* init();

    PacketData getPacketData();

private:
    std::unique_ptr<TabLink> tabLink;
    std::unique_ptr<TabInternet> tabInternet;
};

