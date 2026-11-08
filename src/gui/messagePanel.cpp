
#include "messagePanel.h"


QPlainTextEdit* MessagePanel::init()
{
    widget = new QPlainTextEdit();
    widget->setFixedHeight(40);
    widget->setReadOnly(true);
    return widget;
}


void MessagePanel::setMessage(const std::string& message) const
{
    widget->setPlainText(QString::fromStdString(message));
}


void MessagePanel::clear() const
{
    widget->clear();
}

