#include "SnakeBody.h"
#include <QBrush>

SnakeBody::SnakeBody(QGraphicsItem *parent){
    // dibujar
    setRect(20,20,50,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern); //color solido
    brush.setColor(Qt::darkGreen); //serpiente color verde oscuro
    setBrush(brush);
}
