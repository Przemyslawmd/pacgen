
#include "controller.h"

#include "errorStorage.h"
#include "defines/errors.h"


void Controller::preparePacket() const
{
    messagePanel.clear();

    auto data = packetPanel.getPacketData();
    if (!data.linkLayer || !data.internetLayer) {
        ErrorCode error = ErrorStorage::getError();
        messagePanel.setMessage(ErrorDesc.at(error));
    }
}