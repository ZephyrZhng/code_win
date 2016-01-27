#include "widget.h"
#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w0;
    w0.setType(0);
    w0.show();
    Widget w1;
    w1.setType(1);
    w1.show();
    Widget w2;
    w2.setType(2);
    w2.show();

    return a.exec();
}
