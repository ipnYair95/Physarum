#ifndef CUADRO_H
#define CUADRO_H

#include <QDialog>

namespace Ui {
class Cuadro;
}

class Cuadro : public QDialog
{
    Q_OBJECT

public:
    explicit Cuadro(QWidget *parent = 0);
    ~Cuadro();

    void setArreglo(QVector<double> array,QVector<double> tiempo);

private:
    Ui::Cuadro *ui;


};

#endif // CUADRO_H
