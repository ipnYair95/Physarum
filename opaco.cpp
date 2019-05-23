#include "opaco.h"
#include "ui_opaco.h"
#include <QDebug>

Opaco::Opaco(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Opaco)
{
    ui->setupUi(this);
}

Opaco::~Opaco()
{
    delete ui;
}

void Opaco::set()
{

}

void Opaco::on_pushButton_clicked()
{
    ui->textEdit->setText("sda");
}
