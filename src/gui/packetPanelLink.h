
#pragma once

#include <QComboBox>
#include <QLineEdit>
#include <QWidget>


class PacketPanelLink : public QWidget
{
public:
    PacketPanelLink() = default;

    void init();


private:
    QLineEdit* macSrc;
    QLineEdit* macDst;
    QComboBox* ethType;
};

