
#pragma once

#include <QPlainTextEdit>


class MessagePanel
{
public:
    MessagePanel() = default;

    QPlainTextEdit* init();
    void setMessage(const std::string& message);

private:
    QPlainTextEdit* widget;
};