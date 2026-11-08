
#include "packetPanel.h"


QTabWidget* PacketPanel::init()
{
    auto* tabWidget = new QTabWidget();

    tabLink = std::make_unique<PacketPanelLink>();
    tabLink->init();

    auto* tabInternet = new QWidget();
    auto* tabTransport = new QWidget();
    auto* tabApplication = new QWidget();

    tabWidget->addTab(tabLink.get(), "Link Layer");
    tabWidget->addTab(tabInternet, "Internet Layer");
    tabWidget->addTab(tabTransport, "Transport Layer");
    tabWidget->addTab(tabApplication, "Application Layer");

    return tabWidget;
}


std::unique_ptr<LinkLayer> PacketPanel::getLinkLayerData()
{
    return tabLink->getLinkLayerData();
}

