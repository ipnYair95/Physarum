#ifndef RECTANGULO_H
#define RECTANGULO_H
#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>


class Rectangulo : public QGraphicsItem
{
public:
    Rectangulo();

    int indX;
    int indY;

    int x;
    int y;
    int dim;
    int estado;
    int brocha;
    int subEdo;
    bool llave;


    QRectF boundingRect(  ) const ;
    void setAttrib( int a, int b, int c );
    void getAttrib( );
    void setEdo(int x);
    void setBrocha(int a);
    void setSedo(int a);
    void setLlave();
    int getSedo();
    int getEdo();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

    QRectF** rec;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

};

#endif // RECTANGULO_H
