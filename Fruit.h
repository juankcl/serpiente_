#ifndef FRUIT_H
#define FRUIT_H

#include <QGraphicsEllipseItem>

class Fruit: public QGraphicsEllipseItem{
public:
    Fruit(QGraphicsItem* parent=nullptr);
    //~Fruit();
};

#endif // FRUIT_H
