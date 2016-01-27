#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LogInDialog;
}

class LogInDialog : public QDialog
{
    Q_OBJECT
private:
    QSize * startSize;
    int * perBuild,* endnum;
public:
    explicit LogInDialog(QSize *startSize,int *perBuild,int *endnum,QWidget *parent = 0);
    ~LogInDialog();
    
private slots:
    void on_buttonBox_accepted();

    void on_SpinBox_valueChanged(int arg1);

    void on_SpinBox_2_valueChanged(int arg1);

    void on_spinBox1_valueChanged(int arg1);

    void on_spinBoxend_valueChanged(int arg1);

private:
    Ui::LogInDialog *ui;
};

#endif // LOGINDIALOG_H
