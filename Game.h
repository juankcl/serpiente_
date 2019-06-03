#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include "SnakeHead.h"

class Game: public QGraphicsView{
public:
    // constructores
    Game(QWidget* parent=nullptr);

    // metodos
    void start();
    void restart();

    // atributos
    QGraphicsScene* scene;
};

#endif
