
#include "packetPanel.h"


QTabWidget* PacketPanel::init()
{
    auto* tabWidget = new QTabWidget();

    tabLink = std::make_unique<TabLink>();
    tabLink->init();

    tabInternet = std::make_unique<TabInternet>();
    tabInternet->init();

    auto* tabTransport = new QWidget();
    auto* tabApplication = new QWidget();

    tabWidget->addTab(tabLink.get(), "Link Layer");
    tabWidget->addTab(tabInternet.get(), "Internet Layer");
    tabWidget->addTab(tabTransport, "Transport Layer");
    tabWidget->addTab(tabApplication, "Application Layer");

    return tabWidget;
}


PacketData PacketPanel::getPacketData()
{
    auto linkData = tabLink->getLinkLayerData();
    auto internetData = tabInternet->getInternetLayerData();
    return { std::move(linkData), std::move(internetData) };
}

