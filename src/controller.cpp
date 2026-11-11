
#include "controller.h"

#include "errorStorage.h"
#include "defines/errors.h"
#include "defines/internetLayer.h"

#include <iostream>

void Controller::preparePacket() const
{
    messagePanel.clear();

    auto data = packetPanel.getPacketData();
    if (!data.linkLayer || !data.internetLayer) {
        ErrorCode error = ErrorStorage::getError();
        messagePanel.setMessage(ErrorDesc.at(error));
    }
    // temp
    auto* in = data.internetLayer.get();
    InternetV4Layer* v4 = dynamic_cast<InternetV4Layer*>(in);
    std::cout << "TEST" << std::endl;

    
}