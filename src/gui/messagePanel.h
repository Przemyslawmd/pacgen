
#pragma once

#include <QPlainTextEdit>


class MessagePanel
{
public:
    MessagePanel() = default;

    QPlainTextEdit* init();
    void setMessage(const std::string& message) const;
    void clear() const;

private:
    QPlainTextEdit* widget;
};