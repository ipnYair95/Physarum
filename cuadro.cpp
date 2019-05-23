#include "cuadro.h"
#include "ui_cuadro.h"
#include <algorithm>

Cuadro::Cuadro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cuadro)
{

    ui->setupUi(this);
    //Graphics color parameters
    /*ui->graphicWidget->setBackground(QColor(0, 0, 0, 255));
    ui->graphicWidget->xAxis->setTickLabelColor(Qt::white);
    ui->graphicWidget->xAxis->setBasePen(QPen(Qt::white));
    ui->graphicWidget->xAxis->setLabelColor(Qt::white);
    ui->graphicWidget->xAxis->setTickPen(QPen(Qt::white));
    ui->graphicWidget->xAxis->setSubTickPen(QPen(Qt::white));

    ui->graphicWidget->yAxis->setTickLabelColor(Qt::white);
    ui->graphicWidget->yAxis->setBasePen(QPen(Qt::white));
    ui->graphicWidget->yAxis->setLabelColor(Qt::white);
    ui->graphicWidget->yAxis->setTickPen(QPen(Qt::white));
    ui->graphicWidget->yAxis->setSubTickPen(QPen(Qt::white));
*/
}

Cuadro::~Cuadro()
{
    delete ui;
}

void Cuadro::setArreglo(QVector<double> array,QVector<double> tiempo)
{



    double max = *std::max_element(array.constBegin(), array.constEnd());
    double max2 = *std::max_element(tiempo.constBegin(), tiempo.constEnd());

    ui->graphicWidget->addGraph();
    ui->graphicWidget->graph(0)->setData(tiempo,array);

    ui->graphicWidget->xAxis->setLabel("Generation");
    ui->graphicWidget->yAxis->setLabel("Cells");
    // set axes ranges, so we see all data:
    ui->graphicWidget->xAxis->setRange(0, max2 );
    ui->graphicWidget->yAxis->setRange(0, max );
    ui->graphicWidget->replot();

}
