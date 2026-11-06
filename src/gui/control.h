
#pragma once

#include <QHBoxLayout>


class Control : public QObject
{
    Q_OBJECT

public:
    Control() = default;
    QHBoxLayout* init();

private slots:
    void slotSendPacket();
    void slotLoadPacket();
    void slotSavePacket();
};

