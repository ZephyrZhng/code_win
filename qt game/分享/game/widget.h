#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include <QVector>
#include <QtAlgorithms>

namespace Ui {
class Widget;
}

class MyTimer{
public:
    int key,add;
    QLabel * label;
    QTimer * timer;
    MyTimer(){}
    bool operator <(const MyTimer&B)const{
        return key<B.key;
    }
};

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QSize startSize,int perBuild,int endnum,QWidget *parent = 0);
    ~Widget();
    //bool eventFilter(QObject *obj, QEvent *event);
private:
    Ui::Widget *ui;
    QVector<MyTimer> data;
    QTime start_time;
    int allnum,hitnum,dropnum,continuenum,maxcontinuenum;
    int perBuild,endnum;
    QPoint moveto;
    QSize startSize;
    bool isend;
protected:
    void timerEvent(QTimerEvent *event);
    void mousePressEvent(QMouseEvent *event);
private:
    void deal_build();
    QLabel* outQLabel(QPoint pos);
    void GameOver();
private slots:
    void deallabel();
};

#endif // WIDGET_H
