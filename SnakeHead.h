#ifndef SNAKEHEAD_H
#define SNAKEHEAD_H

#include "SnakeBody.h"
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>

#include <QKeyEvent>
#include <QList>
#include <QPointF>

#include <QDebug>
#include <QObject>

enum posicion{ UP, DOWN, LEFT, RIGHT};

class SnakeHead: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    // constructores
    SnakeHead(QGraphicsItem *parent=nullptr);

    // eventos
    void keyPressEvent(QKeyEvent* event);

    // metodos
    void elongate();
	void teletransporte(QGraphicsItem *fruta);
    void moveBodies();
	
public slots:
    void move();
	
private:
    QList<SnakeBody*> snakeBodies;
    QPointF prevPos;

    QGraphicsTextItem *gameover, *puntuacion, *instruccion_restart;

    posicion direccion;
    bool vida;
    int score;
};

#endif 
