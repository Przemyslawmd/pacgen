
#include "pacgen.h"

#include <QVBoxLayout>
#include <QWidget>


PacketGen::PacketGen(QWidget* parent) : QMainWindow(parent) {}


void PacketGen::init()
{
    resize(900, 600);

    auto* mainPanel = new QWidget(this);
    mainPanel->setContentsMargins(20, 20, 20, 20);
    auto* layoutMain = new QVBoxLayout(mainPanel);

    control = std::make_unique<Control>();
    auto* layoutControl = control->init();

    layoutMain->addSpacing(20);
    layoutMain->addLayout(layoutControl);
    layoutMain->addStretch();

    setCentralWidget(mainPanel);
}

