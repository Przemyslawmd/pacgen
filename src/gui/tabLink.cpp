
#include "tabLink.h"

#include <regex>

#include <QGridLayout>
#include <QLabel>
#include <QVBoxLayout>

#include "errorStorage.h"
#include "../defines/layer/link.h"
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
    ethType->addItem("IEEE_802.1Q", EthTypeVal.at(EthType::IEEE_802_1AD));
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

    auto linkLayer = std::make_unique<LinkLayer>();
    macStrToBytes(macSrc->text().toStdString(), linkLayer->macSrc);
    macStrToBytes(macDst->text().toStdString(), linkLayer->macDst);
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


void TabLink::getWidgetValues(std::map<std::string, std::string>& values) const
{
    values.emplace(KEY_MAC_SRC, macSrc->text().toStdString());
    values.emplace(KEY_MAC_DST, macDst->text().toStdString());
    values.emplace(KEY_ETH_TYPE, ethType->currentText().toStdString());
}


ErrorCode TabLink::fillWidgetValues(const std::map<std::string, std::string>& values)
{
    if (!values.contains(KEY_MAC_SRC)) {
        return FILE_NO_MAC_STR;
    }
    if (!values.contains(KEY_MAC_DST)) {
        return FILE_NO_MAC_DST;
    }
    if (!values.contains(KEY_ETH_TYPE)) {
        return FILE_NO_ETH_TYPE;
    }
    macSrc->setText(values.at(KEY_MAC_SRC).data());
    macDst->setText(values.at(KEY_MAC_DST).data());
    ethType->setCurrentText(values.at(KEY_ETH_TYPE).data());
    return OK;
}

