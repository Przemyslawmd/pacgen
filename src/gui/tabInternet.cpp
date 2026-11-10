
#include "tabInternet.h"

#include <QGridLayout>
#include <QLabel>
#include <QVBoxLayout>

#include "errorStorage.h"


void TabInternet::init()
{
    auto* layoutMain = new QVBoxLayout(this);

    boxIpVer = new QGroupBox();

    radioIpV4 = new QRadioButton("IPv4");
    radioIpV6 = new QRadioButton("IPv6");

    layoutMain->addWidget(radioIpV4);
    layoutMain->addWidget(radioIpV6);

    auto* grid = new QGridLayout();
    ipSrc = new QLineEdit();
    ipDst = new QLineEdit();
    grid->addWidget(new QLabel("Source IP"), 0, 0);
    grid->addWidget(ipSrc, 0, 1);
    grid->addWidget(new QLabel("Destination IP"), 1, 0);
    grid->addWidget(ipDst, 1, 1);

    layoutMain->addLayout(grid);
}


std::unique_ptr<InternetLayer> TabInternet::getInternetLayerData()
{
    if (const ErrorCode error = validate(); error != OK) {
        ErrorStorage::putError(error);
        return nullptr;
    }

    auto internetLayer = std::make_unique<InternetLayer>();
    return internetLayer;
}


ErrorCode TabInternet::validate() const
{
    return OK;
}

