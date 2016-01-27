#ifndef MARKDIALOG_H
#define MARKDIALOG_H

#include <QDialog>

namespace Ui {
class MarkDialog;
}

class MarkDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MarkDialog(int allnum,int hitnum,int dropnum,int maxcontinuenum,QWidget *parent = 0);
    ~MarkDialog();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::MarkDialog *ui;
};

#endif // MARKDIALOG_H
