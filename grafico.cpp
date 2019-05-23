#include "grafico.h"
#include "ui_grafico.h"
#include "QDebug"

Grafico::Grafico(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Grafico)
{
    ui->setupUi(this);
}

Grafico::~Grafico()
{
    delete ui;
}

void Grafico::set(QGraphicsScene *scene)
{
   qDebug() << ui->graphicsView->width();
}

