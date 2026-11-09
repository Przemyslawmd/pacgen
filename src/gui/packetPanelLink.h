
#pragma once

#include <QComboBox>
#include <QLineEdit>
#include <QWidget>

#include "defines/errors.h"
#include "defines/linkLayer.h"


class PacketPanelLink : public QWidget
{
public:
    PacketPanelLink() = default;

    void init();

    std::unique_ptr<LinkLayer> getLinkLayerData();

private:
    QLineEdit* macSrc;
    QLineEdit* macDst;
    QComboBox* ethType;

    ErrorCode validate() const;
};

