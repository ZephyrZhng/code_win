#include "logindialog.h"
#include "ui_logindialog.h"
#include <QTime>

int max(int a,int b){
    if(a>b)return a;
    else return b;
}
int min(int a,int b){
    if(a>b)return b;
    else return a;
}

LogInDialog::LogInDialog(QSize *startSize,int *perBuild,int *endnum,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogInDialog)
{
    ui->setupUi(this);
    qsrand(QTime(0,0).secsTo(QTime::currentTime()));
    QPalette palette = ui->label_out->palette();
    palette.setColor(QPalette::WindowText,QColor(qrand()%255 + 1,qrand()%255 + 1,qrand()%255 + 1));
    ui->label_out->setPalette(palette);
    ui->label_out->setStyleSheet(tr("background-color:rgb(%1,%2,%3)")
                                 .arg(qrand()%255 +1).arg(qrand()%255 +1).arg(qrand()%255 +1));
    this->startSize = startSize;
    this->perBuild = perBuild;
    this->endnum = endnum;
    (*startSize) = QSize(30,15);
    (*perBuild) = 1000;
    (*endnum) = 100;

    setMaximumSize(size());
    setMinimumSize(size());
}

LogInDialog::~LogInDialog()
{
    delete ui;
}

void LogInDialog::on_buttonBox_accepted()
{
    accept();
}


void LogInDialog::on_SpinBox_valueChanged(int arg1)
{
    arg1 = min(max(30,arg1),100);
    ui->SpinBox->setValue(arg1);
    startSize->setWidth(arg1);
    ui->label_out->resize(arg1,ui->label_out->height());
}

void LogInDialog::on_SpinBox_2_valueChanged(int arg1)
{
    arg1 = min(max(15,arg1),50);
    ui->SpinBox_2->setValue(arg1);
    startSize->setHeight(arg1);
    ui->label_out->resize(ui->label_out->width(),arg1);
}



void LogInDialog::on_spinBox1_valueChanged(int arg1)
{
    arg1 = min(max(0,arg1),2000);
    ui->spinBox1->setValue(arg1);
    (*perBuild) = arg1;
}

void LogInDialog::on_spinBoxend_valueChanged(int arg1)
{
    arg1 = min(max(10,arg1),500);
    ui->spinBoxend->setValue(arg1);
    (*endnum) = arg1;
}
