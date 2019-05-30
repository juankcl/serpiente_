#include "SnakeBody.h"
#include <QBrush>

SnakeBody::SnakeBody(QGraphicsItem *parent){
    // draw
    setRect(20,20,50,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkGreen);
    setBrush(brush);
}
