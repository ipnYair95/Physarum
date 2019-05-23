#ifndef HORMIGA_H
#define HORMIGA_H
#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>

class Hormiga : public QGraphicsItem
{

public:
    Hormiga();
    int x;
    int y;
    int dim;
    int posX;
    int posY;

    int frente;

    QRectF boundingRect(  ) const ;
    void actualizar();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setAttrib( int a, int b, int c );
    void setCoord(int a, int b);
    int getX();
    int getY();
    void setFrente(int a);
    int getFrente();

protected:

};

#endif // RECTANGULO_H
