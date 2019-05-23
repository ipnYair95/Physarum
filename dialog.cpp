#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QPixmap bkgnd("phy.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);


    QPixmap pix("logoescom.png");
    int w = ui->escomLabel->width();
    int h = ui->escomLabel->height();
    ui->escomLabel->setPixmap( pix.scaled(w,h,Qt::KeepAspectRatio) );

    QPixmap pix2("logoipn.png");
    w = ui->ipnLabel->width();
    h = ui->ipnLabel->height();
    ui->ipnLabel->setPixmap( pix2.scaled(w,h,Qt::KeepAspectRatio) );

}

Dialog::~Dialog()
{
    delete ui;
}
