
#include "packetPanel.h"

#include "packetPanelLink.h"


QTabWidget* PacketPanel::init()
{
    auto* tabWidget = new QTabWidget();

    auto* tabLink = new PacketPanelLink();
    tabLink->init();

    auto* tabInternet = new QWidget();
    auto* tabTransport = new QWidget();
    auto* tabApplication = new QWidget();

    tabWidget->addTab(tabLink, "Link Layer");
    tabWidget->addTab(tabInternet, "Internet Layer");
    tabWidget->addTab(tabTransport, "Transport Layer");
    tabWidget->addTab(tabApplication, "Application Layer");

    return tabWidget;
}
