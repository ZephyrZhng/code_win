#include "widget.h"
#include "ui_widget.h"

#include <cmath>
#include <iostream>
#include <limits>

#include <QBrush>
#include <QColor>
#include <QPainter>
#include <QPoint>
#include <QString>

using namespace std;

const double PI = 3.1415926;
const int LIMIT = 50000;
const int R = 1;

bool isPrime(long long x)
{
    if(x <= 1)
    {
        return false;
    }
    for(int i = 2; i * i <= x; ++i)
    {
        if(x % i == 0)
        {
            return false;
        }
    }
    return true;
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(500, 500);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setType(int _type)
{
    type = _type;
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QBrush brush(QColor(Qt::red));
    painter.setBrush(brush);
    QPointF point;

    if(type == 0)
    {
        int step = 2;
        setWindowTitle(QString("prime distribution 0"));
        point.setX(this->width() / 2);
        point.setY(this->height() / 2);
        int idx = 1;
        for(long long i = 1; i < LIMIT; ++i)
        {
            if(isPrime(i))
            {
                painter.drawEllipse(point, R, R);
            }

            if(i > 4 * idx * idx - 4 * idx + 1)
            {
                ++idx;
            }

            if(i < 4 * idx * idx - 10 * idx + 7)
            {
                point.setY(point.y() - step);
            }
            else if(i >= 4 * idx * idx - 10 * idx + 7
                    && i < 4 * idx * idx - 8 * idx + 5)
            {
                point.setX(point.x() - step);
            }
            else if(i >= 4 * idx * idx - 8 * idx + 5
                    && i < 4 * idx * idx - 6 * idx + 3)
            {
                point.setY(point.y() + step);
            }
            else if(i >= 4 * idx * idx - 6 * idx + 3
                    && i <= 4 * idx * idx - 4 * idx + 1)
            {
                point.setX(point.x() + step);
            }
        }
    }

    if(type == 1)
    {
        setWindowTitle(QString("prime distribution 1"));
        double r = 0;
        double theta = 0;
        for(long long i = 1; i < LIMIT; ++i)
        {
            if(isPrime(i))
            {
                r = sqrt(i);
                theta = sqrt(i);
                point.setX(this->width() / 2 + r * cos(theta * 2 * PI));
                point.setY(this->height() / 2 + r * sin(theta * 2 * PI));
                painter.drawEllipse(point, R, R);
            }
        }
    }

    if(type == 2)
    {
        setWindowTitle(QString("prime distribution 2"));
        int scale = 250;
        for(long long i = 1; i < LIMIT; ++i)
        {
            if(isPrime(i))
            {
                point.setX(qreal(this->width() / 2 + i * cos(i) / scale));
                point.setY(qreal(this->height() / 2 + i * sin(i) / scale));
                painter.drawEllipse(point, R, R);
            }
        }
    }
}
