
#pragma once

#include "tabLink.h"
#include "tabInternet.h"
#include "tabTransport.h"
#include "defines/packetData.h"


class PacketPanel
{
public:
    PacketPanel() = default;

    QTabWidget* init();

    PacketData getPacketData();

    std::unique_ptr<std::map<std::string, std::string>> getWidgetValues();
    ErrorCode fillWidgetValues(const std::map<std::string, std::string>&);

private:
    std::unique_ptr<TabLink> tabLink;
    std::unique_ptr<TabInternet> tabInternet;
    std::unique_ptr<TabTransport> tabTransport;
};

