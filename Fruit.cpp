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

void Fruit::teletransporte(Fruit * f1)
{
    //    // agregar fruta
    //Fruit* f1 = new Fruit();
    int equix,ye;

    //posicion aleatoria de fruta
    random_device rd; // obtain a random number from hardware
    mt19937 eng(rd()); // seed the generator
    uniform_int_distribution<> distr(100, 600); // define the range

    equix= distr(eng); // generate numbers
    ye=distr(eng);


    f1->setPos(equix,ye);
    //return f1;
}
