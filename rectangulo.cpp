#include "rectangulo.h"

Rectangulo::Rectangulo()
{
    llave = false;
    estado = 0;
    brocha = 0;

}

QRectF Rectangulo::boundingRect() const
{
    return QRectF(x,y,dim,dim);
}

void Rectangulo::setAttrib(int a, int b, int c)
{
    x = a;
    y = b;
    dim = c;


}

void Rectangulo::getAttrib()
{
     qDebug() << x;
     qDebug() << y;
     qDebug() << dim;

}

void Rectangulo::setEdo(int x)
{
    estado = x;
}

void Rectangulo::setBrocha(int a)
{
    brocha = a;
}

void Rectangulo::setSedo(int a)
{
    subEdo = a;
}

void Rectangulo::setLlave()
{
    llave = !llave;
}

int Rectangulo::getSedo()
{
    return subEdo;
}

int Rectangulo::getEdo()
{
    return estado;
}

void Rectangulo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QRectF rec = boundingRect();

     switch(estado)
     {
             case 0:   // Campo Libre
                    painter->setBrush( QColor(0, 0, 0, 255) );
                    break;
             case 1:   // Nutriente
                     painter->setBrush( QColor(0, 0, 204, 255) );
                     break;
             case 2:  // Repelente
                     painter->setBrush( QColor(255, 0, 0, 255) );
                     break;
             case 3:  // Punto Inicial
                     painter->setBrush( QColor(255,205,0, 255) );
                     break;
             case 4:  // Gel
                     painter->setBrush( QColor(255, 255, 0, 255) );
                     break;
             case 5:  // Plasmodio
                     painter->setBrush( QColor(0,153,0,255) );
                     break;
             case 6:  // Nutriente Exitado
                     painter->setBrush( QColor(255,255,153,255) );
                     break;
             case 7:  // Plasmodio
                     painter->setBrush( QColor(128,128,128,255) );
                     break;
             case 8:

                    painter->setBrush( QColor(64,185,64,255) );

                    break;

     }

    painter->setPen(Qt::NoPen);
    painter->drawRect(rec);


}

void Rectangulo::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if( !llave )
    {
        estado = brocha;
        update();
        QGraphicsItem::mousePressEvent(event);
    }
}
