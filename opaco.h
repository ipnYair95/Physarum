#ifndef OPACO_H
#define OPACO_H

#include <QWidget>
#include <QGraphicsScene>

namespace Ui {
class Opaco;
}

class Opaco : public QWidget
{
    Q_OBJECT

public:
    explicit Opaco(QWidget *parent = 0);
    ~Opaco();

public slots:

    void set();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Opaco *ui;
    QGraphicsScene *sc;
};

#endif // OPACO_H
