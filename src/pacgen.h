
#pragma once

#include <memory>

#include <QMainWindow>

#include "gui/controlPanel.h"
#include "gui/messagePanel.h"
#include "gui/packetPanel.h"


class PacketGen : public QMainWindow
{
    Q_OBJECT

public:
    explicit PacketGen(QWidget* parent = nullptr);

    void init();

private:
    std::unique_ptr<ControlPanel> controlPanel;
    std::unique_ptr<PacketPanel> pacPanel;
    std::unique_ptr<MessagePanel> message;
};
