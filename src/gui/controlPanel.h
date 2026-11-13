
#pragma once

#include <QHBoxLayout>

#include "controller.h"


class ControlPanel : public QObject
{
    Q_OBJECT

public:
    ControlPanel(Controller& controller) : controller(controller) {};
    QHBoxLayout* init();

private slots:
    void slotSendPacket();
    void slotLoadPacket();
    void slotSavePacket();
    void slotSettings();

private:
    Controller& controller;
};

