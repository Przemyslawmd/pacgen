
#pragma once

#include "gui/messagePanel.h"
#include "gui/packetPanel.h"

class Controller
{
public:
    Controller(MessagePanel& mes, PacketPanel& pac) : messagePanel(mes), packetPanel(pac) {};

    void preparePacket() const;

    void writePacket(const std::string&);
    void readPacket(const std::string&);

private:
    MessagePanel& messagePanel;
    PacketPanel& packetPanel;
};

