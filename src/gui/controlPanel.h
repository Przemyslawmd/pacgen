
#pragma once

#include <QHBoxLayout>


class ControlPanel : public QObject
{
    Q_OBJECT

public:
    ControlPanel() = default;
    QHBoxLayout* init();

private slots:
    void slotSendPacket();
    void slotLoadPacket();
    void slotSavePacket();
};

