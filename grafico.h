#ifndef GRAFICO_H
#define GRAFICO_H


#include <QDialog>
#include <QGraphicsScene>


namespace Ui {
class Grafico;
}


class Grafico : public QDialog
{
    Q_OBJECT

public:
    explicit Grafico(QWidget *parent = 0);
    ~Grafico();
    void set(QGraphicsScene *scene);


public:
    Ui::Grafico *ui;
    QGraphicsScene *nuevo;

};

#endif // GRAFICO_H
