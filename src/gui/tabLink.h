
#pragma once

#include <QComboBox>
#include <QLineEdit>
#include <QWidget>

#include "defines/errors.h"
#include "defines/linkLayer.h"


class TabLink : public QWidget
{
public:
    TabLink() = default;

    void init();

    std::unique_ptr<LinkLayer> getLinkLayerData();

    void getWidgetValues(std::map<std::string, std::string>&) const;
    ErrorCode fillWidgetValues(const std::map<std::string, std::string>&);

private:
    QLineEdit* macSrc;
    QLineEdit* macDst;
    QComboBox* ethType;

    ErrorCode validate() const;
};

