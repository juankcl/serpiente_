#include <iostream>
#include <random>
#include "Fruit.h"
#include <QBrush>
#include "Game.h"
#include "SnakeHead.h"
#include <cstdlib>

using namespace std;

Fruit::Fruit(QGraphicsItem *parent){
    // dibujar
    setRect(0,0,30,30);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);
}

