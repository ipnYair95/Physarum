#include "hormiga.h"

Hormiga::Hormiga()
{

}

QRectF Hormiga::boundingRect() const
{
    return QRectF(x,y,dim,dim);
}

void Hormiga::actualizar()
{
    update();
}

void Hormiga::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();

    painter->setBrush(  QColor(255,255,255,255) );
    painter->drawEllipse(rec);

}

void Hormiga::setAttrib(int a, int b, int c)
{
    x = a;
    y = b;
    dim = c;
}

void Hormiga::setCoord(int a, int b)
{
    posX = b;
    posY = a;
}

int Hormiga::getX()
{
    return posX;
}

int Hormiga::getY()
{
    return posY;
}

void Hormiga::setFrente(int a)
{
    frente = a;
}

int Hormiga::getFrente()
{
    return frente;
}

