
#include "packetPanelLink.h"

#include <QGridLayout>
#include <QLabel>
#include <QVBoxLayout>

#include "defines/linkLayer.h"


void PacketPanelLink::init()
{
    auto* grid = new QGridLayout();
    grid->setContentsMargins(20, 0, 0, 0);
    grid->setAlignment(Qt::AlignLeft);
    grid->setVerticalSpacing(20);

    auto* srcLabel = new QLabel("Source MAC");
    srcLabel->setFixedWidth(120);
    grid->addWidget(srcLabel, 0, 0);
    macSrc = new QLineEdit();
    macSrc->setMaxLength(17);
    macSrc->setFixedWidth(140);
    macSrc->setAlignment(Qt::AlignCenter);
    grid->addWidget(macSrc, 0, 1);

    grid->addWidget(new QLabel("Destination MAC"), 1, 0);
    macDst = new QLineEdit();
    macDst->setMaxLength(17);
    macDst->setFixedWidth(140);
    macDst->setAlignment(Qt::AlignCenter);
    grid->addWidget(macDst, 1, 1);

    grid->addWidget(new QLabel("Ether Type"), 2, 0);
    ethType = new QComboBox();
    ethType->addItem("IPv4", EthTypeVal.at(EthType::IPV4));
    ethType->addItem("IPv6", EthTypeVal.at(EthType::IPV6));
    ethType->addItem("ARP", EthTypeVal.at(EthType::ARP));
    ethType->addItem("IEEE 802.1Q", EthTypeVal.at(EthType::IEEE_802_1AD));
    grid->addWidget(ethType, 2, 1);

    auto* layout = new QVBoxLayout(this);
    layout->addSpacing(20);
    layout->addLayout(grid);
    layout->addStretch();
}

