#include "blockclient.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BlockClient w;
    w.show();
    return a.exec();
}
