
#include "tabTransport.h"

#include <QButtonGroup>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

#include "controlPanel.h"


void TabTransport::init()
{
    auto* layMain = new QVBoxLayout(this);

    auto* layUpper = new QHBoxLayout();
    layMain->addLayout(layUpper);

    auto* frameTCP = new QFrame();
    frameTCP->setObjectName("frameTCP");
    frameTCP->setStyleSheet("#frameTCP { border: 1px solid palette(mid); margin: 10px; margin-right: 5px; padding: 10px }");

    auto* layTCP = new QVBoxLayout(frameTCP);
    radioTCP = new QRadioButton("TCP");
    layTCP->addWidget(radioTCP);
    layTCP->addStretch();

    auto* frameUDP = new QFrame();
    frameUDP->setObjectName("frameUDP");
    frameUDP->setStyleSheet("#frameUDP { border: 1px solid palette(mid); margin: 10px; margin-left: 5px; padding: 10px }");

    auto* layUDP = new QVBoxLayout(frameUDP);
    radioUDP = new QRadioButton("UDP");
    layUDP->addWidget(radioUDP);
    layUDP->addStretch();

    layUpper->addWidget(frameTCP);
    layUpper->addWidget(frameUDP);

    auto* radioGroup = new QButtonGroup();
    radioGroup->addButton(radioTCP, 1);
    radioGroup->addButton(radioUDP, 2);
    radioTCP->setChecked(true);

    auto* grid = new QGridLayout();
    grid->setContentsMargins(10, 10, 10, 10);
    portSrc = new QLineEdit();
    portSrc->setFixedWidth(60);
    portDst = new QLineEdit();
    portDst->setFixedWidth(60);
    auto* label = new QLabel("Source Port");
    label->setFixedWidth(120);
    grid->addWidget(label, 0, 0);
    grid->addWidget(portSrc, 0, 1);
    grid->addWidget(new QLabel("Destination Port"), 1, 0);
    grid->addWidget(portDst, 1, 1);

    auto *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    grid->addItem(spacer, 0, 2);

    layMain->addLayout(grid);
}

