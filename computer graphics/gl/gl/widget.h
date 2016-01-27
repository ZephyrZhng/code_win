#ifndef WIDGET_H
#define WIDGET_H

#include <qgl.h>
#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QGLWidget
{
    Q_OBJECT

public:
    explicit Widget(QGLWidget *parent = 0);
    ~Widget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
