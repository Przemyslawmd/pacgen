
#pragma once

#include "gui/messagePanel.h"
#include "gui/packetPanel.h"

class Controller
{
public:
    Controller(MessagePanel& mes, PacketPanel& pac) : messagePanel(mes), packetPanel(pac) {};

    void preparePacket() const;

private:
    MessagePanel& messagePanel;
    PacketPanel& packetPanel;
};