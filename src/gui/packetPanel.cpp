
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


std::unique_ptr<std::map<std::string, std::string>> PacketPanel::getWidgetValues()
{
    auto values = std::make_unique<std::map<std::string, std::string>>();
    tabLink->getWidgetValues(*values);
    return values;
}


ErrorCode PacketPanel::fillWidgetValues(const std::map<std::string, std::string>& val)
{
    return tabLink->fillWidgetValues(val);
}

