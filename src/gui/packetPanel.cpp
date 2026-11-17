
#include "packetPanel.h"


QTabWidget* PacketPanel::init()
{
    auto* tabWidget = new QTabWidget();

    tabLink = std::make_unique<TabLink>();
    tabLink->init();

    tabInternet = std::make_unique<TabInternet>();
    tabInternet->init();

    tabTransport = std::make_unique<TabTransport>();
    tabTransport->init();

    auto* tabApplication = new QWidget();

    tabWidget->addTab(tabLink.get(), "Link Layer");
    tabWidget->addTab(tabInternet.get(), "Internet Layer");
    tabWidget->addTab(tabTransport.get(), "Transport Layer");
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
    tabInternet->getWidgetValues(*values);
    return values;
}


ErrorCode PacketPanel::fillWidgetValues(const std::map<std::string, std::string>& val)
{
    ErrorCode code = tabLink->fillWidgetValues(val);
    if (code != OK) {
        return code;
    }
    return tabInternet->fillWidgetValues(val);
}

