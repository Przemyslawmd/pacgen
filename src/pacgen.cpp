
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

    controlPanel = std::make_unique<ControlPanel>();
    auto* layoutControl = controlPanel->init();

    pacPanel = std::make_unique<PacketPanel>();
    auto* widget = pacPanel->init();

    layoutMain->addSpacing(20);
    layoutMain->addLayout(layoutControl);
    layoutMain->addSpacing(20);
    layoutMain->addWidget(widget);
    layoutMain->addStretch();

    setCentralWidget(mainPanel);
}

