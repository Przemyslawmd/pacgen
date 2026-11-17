
#pragma once

#include <QRadioButton>
#include <QWidget>


class TabTransport : public QWidget
{
public:
    TabTransport() = default;

    void init();

private:
    QRadioButton* radioTCP;
    QRadioButton* radioUDP;
};

