
#include "pacgen.h"

#include <QVBoxLayout>
#include <QWidget>


PacketGen::PacketGen(QWidget* parent) : QMainWindow(parent) {}


void PacketGen::init()
{
    resize(1200, 800);

    auto* mainPanel = new QWidget(this);
    mainPanel->setContentsMargins(20, 20, 20, 20);
    auto* layoutMain = new QVBoxLayout(mainPanel);

    packetPanel = std::make_unique<PacketPanel>();
    auto* widget = packetPanel->init();

    messagePanel = std::make_unique<MessagePanel>();
    auto* widgetMessage = messagePanel->init();

    controller = std::make_unique<Controller>(*messagePanel, *packetPanel);

    controlPanel = std::make_unique<ControlPanel>(*controller);
    auto* layoutControl = controlPanel->init();

    layoutMain->addSpacing(20);
    layoutMain->addLayout(layoutControl);
    layoutMain->addSpacing(30);
    layoutMain->addWidget(widget);
    layoutMain->addSpacing(20);
    layoutMain->addWidget(widgetMessage);
    layoutMain->addSpacing(20);

    setCentralWidget(mainPanel);
}

