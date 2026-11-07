
#include "controlPanel.h"

#include <iostream>

#include <QPushButton>
#include <QHBoxLayout>


QHBoxLayout* ControlPanel::init()
{
    auto* layout = new QHBoxLayout();

    auto* pushSendPacket = new QPushButton("Send packet");
    connect(pushSendPacket, &QPushButton::clicked, this, &ControlPanel::slotSendPacket);
    layout->addWidget(pushSendPacket);

    auto* pushLoadPacket = new QPushButton("Load packet");
    connect(pushLoadPacket, &QPushButton::clicked, this, &ControlPanel::slotLoadPacket);
    layout->addWidget(pushLoadPacket);

    auto* pushSavePacket = new QPushButton("Save packet");
    connect(pushSavePacket, &QPushButton::clicked, this, &ControlPanel::slotSavePacket);
    layout->addWidget(pushSavePacket);

   return layout;
}


void ControlPanel::slotSendPacket()
{
    std::cout << "slotSendPacket" << std::endl;
}


void ControlPanel::slotSavePacket()
{
    std::cout << "slotSavePacket" << std::endl;
}


void ControlPanel::slotLoadPacket()
{
    std::cout << "slotLoadPacket" << std::endl;
}