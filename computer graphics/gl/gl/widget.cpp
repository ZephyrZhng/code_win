#include "widget.h"
#include "ui_widget.h"

#include <Gl/glu.h>
#include <QtOpenGL>

Widget::Widget(QGLWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initializeGL()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
}

void Widget::resizeGL(int w, int h)
{
    glViewport(0,0,(GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,(GLfloat)w / (GLfloat)h, 0.1,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0,0.0,-10.0);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0,0.0,1.0);
    glVertex3f(0.0,1.0,0.0);
    glColor3f(0.0,1.0,0.0);
    glVertex3f(-1.0,-1.0,0.0);
    glColor3f(0.0,0.0,1.0);
    glVertex3f(1.0,-1.0,0.0);
    glEnd();
}
