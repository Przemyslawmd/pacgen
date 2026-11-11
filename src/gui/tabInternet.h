
#pragma once

#include <QComboBox>
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

    QComboBox* protocol;
    QLineEdit* ttl;

    std::unique_ptr<InternetV4Layer> getInternetLayerV4Data();
    std::unique_ptr<InternetV6Layer> getInternetLayerV6Data();
    ErrorCode validateV4() const;
    ErrorCode validateV6() const;
};

