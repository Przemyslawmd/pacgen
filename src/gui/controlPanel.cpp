
#include "controlPanel.h"

#include <iostream>

#include <QPushButton>
#include <QHBoxLayout>


QHBoxLayout* ControlPanel::init()
{
    auto* layout = new QHBoxLayout();

    auto* pushSendPacket = new QPushButton("Send Packet");
    connect(pushSendPacket, &QPushButton::clicked, this, &ControlPanel::slotSendPacket);
    layout->addWidget(pushSendPacket);

    auto* pushLoadPacket = new QPushButton("Load Packet");
    connect(pushLoadPacket, &QPushButton::clicked, this, &ControlPanel::slotLoadPacket);
    layout->addWidget(pushLoadPacket);

    auto* pushSavePacket = new QPushButton("Save Packet");
    connect(pushSavePacket, &QPushButton::clicked, this, &ControlPanel::slotSavePacket);
    layout->addWidget(pushSavePacket);

    auto* pushSettings = new QPushButton("Settings");
    connect(pushSettings, &QPushButton::clicked, this, &ControlPanel::slotSettings);
    layout->addWidget(pushSettings);

   return layout;
}


void ControlPanel::slotSendPacket()
{
    controller.preparePacket();
}


void ControlPanel::slotSavePacket()
{
    std::cout << "slotSavePacket" << std::endl;
}


void ControlPanel::slotLoadPacket()
{
    std::cout << "slotLoadPacket" << std::endl;
}


void ControlPanel::slotSettings()
{
    std::cout << "slotSettings" << std::endl;
}

