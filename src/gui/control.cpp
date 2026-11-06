
#include "control.h"

#include <iostream>

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>


QHBoxLayout* Control::init()
{
    auto* layout = new QHBoxLayout();

    auto* pushSendPacket = new QPushButton("Send packet");
    connect(pushSendPacket, &QPushButton::clicked, this, &Control::slotSendPacket);
    layout->addWidget(pushSendPacket);

    auto* pushLoadPacket = new QPushButton("Load packet");
    connect(pushLoadPacket, &QPushButton::clicked, this, &Control::slotLoadPacket);
    layout->addWidget(pushLoadPacket);

    auto* pushSavePacket = new QPushButton("Save packet");
    connect(pushSavePacket, &QPushButton::clicked, this, &Control::slotSavePacket);
    layout->addWidget(pushSavePacket);

   return layout;
}


void Control::slotSendPacket()
{
    std::cout << "slotSendPacket" << std::endl;
}


void Control::slotSavePacket()
{
    std::cout << "slotSavePacket" << std::endl;
}


void Control::slotLoadPacket()
{
    std::cout << "slotLoadPacket" << std::endl;
}