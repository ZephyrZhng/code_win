#include "widget.h"
#include "ui_widget.h"
#include "markdialog.h"

#include <QDebug>
#include <QPalette>
#include <QMouseEvent>

Widget::Widget(QSize startSize, int perBuild,int endnum,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    startTimer(perBuild);
    start_time = QTime::currentTime();
    this->startSize = startSize;
    this->perBuild = perBuild;
    this->endnum = endnum;

    moveto = QPoint(10000000,10000000);
    hitnum = 0;
    dropnum = 0;
    allnum = 0;
    continuenum = 0;
    maxcontinuenum = 0;
    isend = false;

    setFocus();

    setMaximumSize(size());
    setMinimumSize(size());
}

Widget::~Widget()
{
    delete ui;
}

void Widget::timerEvent(QTimerEvent *event)
{
    if(isend)return;

    qDebug()<<"timer";
    QLabel * label = new QLabel(this);
    QTimer * timer = new QTimer(this);
    label->setText("drop");
    label->move(qrand()%(this->width()-label->width()),0);
    QPalette palette = label->palette();
    palette.setColor(QPalette::WindowText,QColor(qrand()%255 + 1,qrand()%255 + 1,qrand()%255 + 1));
    label->setPalette(palette);
    label->setStyleSheet(tr("background-color:rgb(%1,%2,%3)")
                         .arg(qrand()%255 +1).arg(qrand()%255 +1).arg(qrand()%255 +1));
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label->resize(startSize);
    label->show();

    int value = qrand()%1000+100;
    timer->start(value);
    MyTimer mytimer;
    mytimer.add = value;
    mytimer.key = start_time.msecsTo(QTime::currentTime()) + value;
    mytimer.label = label;
    mytimer.timer = timer;
    data.push_back(mytimer);
    connect(timer,SIGNAL(timeout()),this,SLOT(deallabel()));

    allnum++;
    ui->labelall->setText(tr("总数：%1").arg(allnum));
}
void Widget::deallabel()
{
    if(isend)return;

    qDebug()<<"label";
    qDebug()<<"-------------   "<<data.size()<<endl;

    qStableSort(data.begin(),data.end());
    MyTimer mytimer = data[0];
    data.pop_front();

    QLabel * label = mytimer.label;
    QTimer * timer = mytimer.timer;
    if(label->pos()==moveto){
        qDebug()<<"del";
        timer->stop();
        delete timer;
        delete label;
        return;
    }

    label->move(label->pos()+QPoint(0,10));
    if(label->y() < (this->height())){
        mytimer.key += mytimer.add;
        data.push_back(mytimer);
    }else{
        qDebug()<<"del";
        timer->stop();
        delete timer;
        delete label;

        dropnum++;
        ui->labeldrop->setText(tr("掉落：%1").arg(dropnum));
        if(dropnum > endnum)GameOver();
    }
}
QLabel* Widget::outQLabel(QPoint pos)
{
    pos = pos - QPoint(this->geometry().x(),this->geometry().y());
    for(int i=0;i<data.size();i++){
        QLabel * label = data[i].label;
        if(label->pos().y() <= pos.y() && label->pos().y() + label->height()>= pos.y()
                && label->pos().x() <= pos.x() && label->pos().x() + label->width() >= pos.x())
            return label;
    }
    return 0;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(isend)return;

    qDebug()<<"mouse";
    if(event->button() == Qt::LeftButton){
        QPoint pos = event->globalPos();
        QLabel * label = outQLabel(pos);
        if(label == 0){
            continuenum = 0;
            ui->labelcontinue->setText(tr("连杀：0"));
            return;
        }
        label->move(moveto);
        hitnum++;
        ui->labelhit->setText(tr("击落：%1").arg(hitnum));
        continuenum++;
        ui->labelcontinue->setText(tr("连杀：%1").arg(continuenum));
        if(maxcontinuenum<continuenum)
            maxcontinuenum = continuenum;
    }
}
void Widget::GameOver()
{
    isend = true;
    for(int i=0;i<data.size();i++){
        MyTimer mytimer = data[i];
        mytimer.timer->stop();
    }

    MarkDialog * dialog = new MarkDialog(allnum,hitnum,dropnum,maxcontinuenum,this);
    connect(dialog,SIGNAL(finished(int)),this,SLOT(close()));
    dialog->show();
}
