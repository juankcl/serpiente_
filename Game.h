#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include "SnakeHead.h"

class Game: public QGraphicsView{
public:
    // constructors
    Game(QWidget* parent=nullptr);

    // public methods
    void start();

    // public attributes
    QGraphicsScene* scene;

private:

};

#endif // GAME_H
