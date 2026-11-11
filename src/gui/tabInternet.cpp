
#include "tabInternet.h"

#include <regex>

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
    ipSrc->setFixedWidth(100);
    ipDst = new QLineEdit();
    grid->addWidget(new QLabel("Source IP"), 0, 0);
    grid->addWidget(ipSrc, 0, 1);
    grid->addWidget(new QLabel("Destination IP"), 1, 0);
    grid->addWidget(ipDst, 1, 1);

    using enum Protocol;
    protocol = new QComboBox();
    protocol->addItem("TCP", ProtocolVal.at(TCP));
    protocol->addItem("UDP", ProtocolVal.at(UDP));
    protocol->addItem("ICMP", ProtocolVal.at(ICMP));
    protocol->addItem("IGMP", ProtocolVal.at(IGMP));
    protocol->addItem("IPv6", ProtocolVal.at(IPv6));
    protocol->addItem("GRE", ProtocolVal.at(GRE));
    protocol->addItem("ESP", ProtocolVal.at(ESP));
    protocol->addItem("AH", ProtocolVal.at(AH));
    protocol->addItem("ICMPv6", ProtocolVal.at(ICMPv6));
    protocol->addItem("OSPF", ProtocolVal.at(OSPF));
    protocol->addItem("SCTP", ProtocolVal.at(SCTP));
    grid->addWidget(new QLabel("Protocol"), 2, 0);
    grid->addWidget(protocol, 2, 1);

    ttl = new QLineEdit();
    grid->addWidget(new QLabel("TTL"), 3, 0);
    grid->addWidget(ttl, 3, 1);

    layoutMain->addLayout(grid);
}


std::unique_ptr<InternetLayer> TabInternet::getInternetLayerData()
{
    if (radioIpV4->isChecked()) {
        return getInternetLayerV4Data();
    }
    return getInternetLayerV6Data();
}


std::unique_ptr<InternetV4Layer> TabInternet::getInternetLayerV4Data()
{
    if (const ErrorCode error = validateV4(); error != OK) {
        ErrorStorage::putError(error);
        return nullptr;
    }

    const auto getIP = [](const std::string& ipStr) -> uint32_t {
        auto ipView = ipStr | std::views::split('.');
        uint8_t octet;
        uint32_t ip = 0;
        for (const auto& v : ipView) {
            std::string_view segment(v);
            std::from_chars(segment.data(), segment.data() + segment.size(), octet);
            ip = (ip << 8) | octet;
        }
        return ip;
    };

    auto internetLayer = std::make_unique<InternetV4Layer>();
    internetLayer->ipSrc = getIP(ipSrc->text().toStdString());
    internetLayer->ipDst = getIP(ipDst->text().toStdString());
    return internetLayer;
}


std::unique_ptr<InternetV6Layer> TabInternet::getInternetLayerV6Data()
{
    if (const ErrorCode error = validateV6(); error != OK) {
        ErrorStorage::putError(error);
        return nullptr;
    }

    auto internetLayer = std::make_unique<InternetV6Layer>();
    return internetLayer;
}


ErrorCode TabInternet::validateV4() const
{
    const std::regex macRegex(
        R"(^(?:(?:25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\.){3}(?:25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])$)",
        std::regex::optimize);

    const std::string& src = ipSrc->text().toStdString();
    if (src.empty() || !std::regex_match(src.begin(), src.end(), macRegex)) {
        return PAN_IP4_SRC;
    }

    const std::string& dst = ipDst->text().toStdString();
    if (dst.empty() || !std::regex_match(dst.begin(), dst.end(), macRegex)) {
        return PAN_IP4_DST;
    }
    return OK;
}


ErrorCode TabInternet::validateV6() const
{
    const std::regex macRegex(
        R"(^(?:[0-9a-fA-F]{1,4}:){1,7}:|^(?:[0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}$|^(?:[0-9a-fA-F]{1,4}:){1,6}:
            [0-9a-fA-F]{1,4}$|^(?:[0-9a-fA-F]{1,4}:){1,5}(?::[0-9a-fA-F]{1,4}){1,2}$|^(?:[0-9a-fA-F]{1,4}:){1,4}
            (?::[0-9a-fA-F]{1,4}){1,3}$|^(?:[0-9a-fA-F]{1,4}:){1,3}(?::[0-9a-fA-F]{1,4}){1,4}$|^(?:[0-9a-fA-F]{1,4}:)
            {1,2}(?::[0-9a-fA-F]{1,4}){1,5}$|^[0-9a-fA-F]{1,4}:(?::[0-9a-fA-F]{1,4}){1,6}$|^:(?::[0-9a-fA-F]{1,4}){1,7}$|^::$)",
        std::regex::optimize);

    const std::string& src = ipSrc->text().toStdString();
    if (src.empty() || !std::regex_match(src.begin(), src.end(), macRegex)) {
        return PAN_IP6_SRC;
    }

    const std::string& dst = ipDst->text().toStdString();
    if (dst.empty() || !std::regex_match(dst.begin(), dst.end(), macRegex)) {
        return PAN_IP6_DST;
    }
    return OK;
}

