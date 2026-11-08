
#include "controller.h"

#include "errorStorage.h"
#include "defines/errors.h"


void Controller::preparePacket() const
{
    messagePanel.clear();

    auto data = packetPanel.getLinkLayerData();
    if (!data) {
        ErrorCode error = ErrorStorage::getError();
        messagePanel.setMessage(ErrorDesc.at(error));
    }
}