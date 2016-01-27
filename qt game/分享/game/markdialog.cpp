#include "markdialog.h"
#include "ui_markdialog.h"

MarkDialog::MarkDialog(int allnum, int hitnum, int dropnum, int maxcontinuenum, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MarkDialog)
{
    ui->setupUi(this);
    ui->labelall->setText(tr("总数：%1").arg(allnum));
    ui->labelhit->setText(tr("击杀：%1").arg(hitnum));
    ui->labeldrop->setText(tr("掉落：%1").arg(dropnum));
    ui->labelcontinue->setText(tr("最大连杀数：%1").arg(maxcontinuenum));

    setMaximumSize(size());
    setMinimumSize(size());
}

MarkDialog::~MarkDialog()
{
    delete ui;
}

void MarkDialog::on_pushButton_clicked()
{
    close();
}
