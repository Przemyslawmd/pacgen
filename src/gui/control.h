
#pragma once

#include <QHBoxLayout>

class Control : public QObject
{
    Q_OBJECT

public:
    Control() = default;
    void init(QVBoxLayout* layout);

private slots:
    void slotSendPacket();
    void slotLoadPacket();
    void slotSavePacket();
};

