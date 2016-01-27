#ifndef MYLABEL_H
#define MYLABEL_H

#include <QObject>
#include <QLabel>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // MYLABEL_H
