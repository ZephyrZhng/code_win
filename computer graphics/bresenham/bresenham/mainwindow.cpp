#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QBrush>
#include <QPainter>
#include <QPoint>
#include <QPointF>
#include <QString>

#include <cmath>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(500, 500);
    setWindowTitle(QString("bresenham"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    int height = this->height();
    int width = this->width();
    int step = 10;
    QPainter painter(this);
    QPointF pp0;
    QPointF pp1;
    pp0.setY(0);
    pp1.setY(height);
    for(int i = 0; i < width; i += step)
    {
        pp0.setX(i);
        pp1.setX(i);
        painter.drawLine(pp0, pp1);
    }
    pp0.setX(0);
    pp1.setX(width);
    for(int i = 0; i < height; i += step)
    {
        pp0.setY(i);
        pp1.setY(i);
        painter.drawLine(pp0, pp1);
    }

    QBrush brush(QColor(Qt::red));
    painter.setBrush(brush);
    QPoint p0(0 * step, 0 * step);
    QPoint p1(50 * step, 20 * step);
    int x0 = p0.x();
    int y0 = p0.y();
    int x1 = p1.x();
    int y1 = p1.y();
    int r = 3;

    int dx = x1 - x0;
    int dy = y1 - y0;
    int d = dx - 2 * dy;
    QPoint point(x0, y0);


    while(point.x() <= x1)
    {
        painter.drawEllipse(point, r, r);
        if(d < 0)
        {
            point.setX(point.x() + step);
            point.setY(point.y() + step);
            d = d + 2 * dx - 2 * dy;
        }
        else
        {
            point.setX(point.x() + step);
            point.setY(point.y());
            d = d - 2 * dy;
        }
    }
}
