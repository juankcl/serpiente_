#include <iostream>
#include <random>
#include "Fruit.h"
#include <QBrush>
#include "Game.h"
#include "SnakeHead.h"
#include <cstdlib>

using namespace std;

Fruit::Fruit(QGraphicsItem *parent){
    // draw
    setRect(0,0,50,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);
}

