#include <QtGui/QApplication>
#include "clientwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientWidget w;
    w.show();

    return a.exec();
}
