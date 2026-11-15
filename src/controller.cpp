
#include "controller.h"

#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>
#include <ranges>

#include "defines/common.h"
#include "errorStorage.h"
#include "defines/errors.h"
#include "cretator.h"
#include "sender.h"


void Controller::preparePacket() const
{
    messagePanel.clear();

    auto data = packetPanel.getPacketData();
    if (!data.linkLayer || !data.internetLayer) {
        ErrorCode error = ErrorStorage::getError();
        messagePanel.setMessage(ErrorDesc.at(error));
    }
    auto [buf, size] = createPacket(*data.linkLayer);
    sendPacket(buf.get(), size);
}


void Controller::writePacket(const std::string& file)
{
    messagePanel.clear();
    std::ofstream ofs(file);
    if (!ofs) {
        messagePanel.setMessage(ErrorDesc.at(CON_STREAM));
        return;
    }

    const auto values = packetPanel.getWidgetValues();
    ofs << KEY_MAC_STR << " " << values->at(KEY_MAC_STR) << END_LINE;
    ofs << KEY_MAC_DST << " " << values->at(KEY_MAC_DST) << END_LINE;
    ofs << KEY_ETH_TYPE << " " << values->at(KEY_ETH_TYPE) << END_LINE;
    ofs.close();
}


void Controller::readPacket(const std::string& file)
{
    messagePanel.clear();
    std::ifstream ifs(file);
    if (!ifs) {
        messagePanel.setMessage(ErrorDesc.at(CON_STREAM));
        return;
    }

    auto values = std::make_unique<std::map<std::string, std::string>>();
    std::stringstream buffer;
    buffer << ifs.rdbuf();

    const auto isSpace = [](const char c){
        return std::isspace(static_cast<unsigned char>(c));
    };

    auto view = buffer.str()
        | std::views::chunk_by([&](const char a, const char b) { return isSpace(a) == isSpace(b); })
        | std::views::filter([&](auto chunk) { return !isSpace(chunk.front()); });

    for (auto it = view.begin(); it != view.end();) {
        if (std::next(it) == view.end()) {
            messagePanel.setMessage(ErrorDesc.at(CON_FILE));
            return;
        }
        std::string key((*it).begin(), (*it).end());
        std::string val((*std::next(it)).begin(), (*std::next(it)).end());
        values->insert_or_assign(key, val);
        std::advance(it, 2);
    }
    if (packetPanel.fillWidgetValues(*values) != OK) {
        ErrorCode error = ErrorStorage::getError();
        messagePanel.setMessage(ErrorDesc.at(error));
    }
}

