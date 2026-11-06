
#pragma once

#include <memory>

#include <QMainWindow>

#include "gui/control.h"
#include "gui/message.h"
#include "gui/panel.h"


class PacketGen : public QMainWindow
{
    Q_OBJECT

public:
    explicit PacketGen(QWidget* parent = nullptr);

    void init();

private:
    std::unique_ptr<Control> control;
    std::unique_ptr<Panel> panel;
    std::unique_ptr<Message> message;
};
