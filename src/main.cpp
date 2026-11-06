
#include <QApplication>

#include "pacgen.h"


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    PacketGen pac;
    pac.init();
    pac.show();
    return app.exec();
}