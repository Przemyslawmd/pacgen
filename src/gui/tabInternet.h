
#pragma once

#include <QGroupBox>
#include <QLineEdit>
#include <QRadioButton>
#include <QWidget>

#include "defines/errors.h"
#include "defines/internetLayer.h"


class TabInternet : public QWidget
{
public:
    TabInternet() = default;

    void init();
    std::unique_ptr<InternetLayer> getInternetLayerData();

private:
    QGroupBox* boxIpVer;
    QRadioButton* radioIpV4;
    QRadioButton* radioIpV6;

    QLineEdit* ipSrc;
    QLineEdit* ipDst;

    ErrorCode validateV4() const;
    ErrorCode validateV6() const;
};

