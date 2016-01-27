#include "widget.h"
#include "logindialog.h"
#include <QApplication>
#include <QPoint>

QSize startSize;
int perBuild,endnum;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogInDialog login(&startSize,&perBuild,&endnum);
    if(login.exec() == QDialog::Accepted){
        Widget w(startSize,perBuild,endnum);
        w.show();
        return a.exec();
    }
    else return 0;

}
