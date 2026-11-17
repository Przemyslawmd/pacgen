
#include "tabTransport.h"

#include <QButtonGroup>
#include <QFrame>
#include <QHBoxLayout>

#include "controlPanel.h"


void TabTransport::init()
{
    auto* layMain = new QHBoxLayout(this);

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

    layMain->addWidget(frameTCP);
    layMain->addWidget(frameUDP);

    auto* radioGroup = new QButtonGroup();
    radioGroup->addButton(radioTCP, 1);
    radioGroup->addButton(radioUDP, 2);
    radioTCP->setChecked(true);
}

