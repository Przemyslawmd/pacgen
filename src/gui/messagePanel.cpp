
#include "messagePanel.h"


QPlainTextEdit* MessagePanel::init()
{
    auto* text = new QPlainTextEdit();
    text->setFixedHeight(40);
    text->setReadOnly(true);

    return text;
}

