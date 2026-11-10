
#include "tabLink.h"

#include <array>
#include <regex>

#include <QGridLayout>
#include <QLabel>
#include <QVBoxLayout>

#include "errorStorage.h"
#include "defines/linkLayer.h"
#include "utils/hexToByte.h"


void TabLink::init()
{
    auto* grid = new QGridLayout();
    grid->setContentsMargins(20, 0, 0, 0);
    grid->setAlignment(Qt::AlignLeft);
    grid->setVerticalSpacing(20);

    auto* srcLabel = new QLabel("Source MAC");
    srcLabel->setFixedWidth(120);
    grid->addWidget(srcLabel, 0, 0);
    macSrc = new QLineEdit();
    macSrc->setMaxLength(17);
    macSrc->setFixedWidth(140);
    macSrc->setAlignment(Qt::AlignCenter);
    grid->addWidget(macSrc, 0, 1);

    grid->addWidget(new QLabel("Destination MAC"), 1, 0);
    macDst = new QLineEdit();
    macDst->setMaxLength(17);
    macDst->setFixedWidth(140);
    macDst->setAlignment(Qt::AlignCenter);
    grid->addWidget(macDst, 1, 1);

    grid->addWidget(new QLabel("Ether Type"), 2, 0);
    ethType = new QComboBox();
    ethType->addItem("IPv4", EthTypeVal.at(EthType::IPV4));
    ethType->addItem("IPv6", EthTypeVal.at(EthType::IPV6));
    ethType->addItem("ARP", EthTypeVal.at(EthType::ARP));
    ethType->addItem("IEEE 802.1Q", EthTypeVal.at(EthType::IEEE_802_1AD));
    grid->addWidget(ethType, 2, 1);

    auto* layout = new QVBoxLayout(this);
    layout->addSpacing(20);
    layout->addLayout(grid);
    layout->addStretch();
}


std::unique_ptr<LinkLayer> TabLink::getLinkLayerData()
{
    if (const ErrorCode error = validate(); error != OK) {
        ErrorStorage::putError(error);
        return nullptr;
    }

    const auto fillMac = [](const std::string& macStr, std::array<std::byte, MAC_BYTES>& arr) {
        for (unsigned int i = 0, j = 0; i < MAC_BYTES; i++, j += 3) {
            arr[i] = hexToByte(macStr[j], macStr[j + 1]);
         }
    };

    auto linkLayer = std::make_unique<LinkLayer>();
    fillMac(macSrc->text().toStdString(), linkLayer->macSrc);
    fillMac(macDst->text().toStdString(), linkLayer->macDst);
    linkLayer->ethType = ethType->currentData().toInt();
    return linkLayer;
}


ErrorCode TabLink::validate() const
{
    const std::regex macRegex(R"(^([0-9A-F]{2}[:]){5}([0-9A-F]{2})$)", std::regex::optimize);

    const std::string& srcStr = macSrc->text().toStdString();
    if (srcStr.empty() || !std::regex_match(srcStr.begin(), srcStr.end(), macRegex)) {
        return PAN_MAC_SRC;
    }

    const std::string& dstStr = macDst->text().toStdString();
    if (dstStr.empty() || !std::regex_match(dstStr.begin(), dstStr.end(), macRegex)) {
        return PAN_MAC_DST;
    }
    return OK;
}

