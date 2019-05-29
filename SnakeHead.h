#ifndef SNAKEHEAD_H
#define SNAKEHEAD_H

#include "SnakeBody.h"
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QList>
#include <QPointF>

#include <QDebug>
#include <QObject>

enum posicion{ UP, DOWN, LEFT, RIGHT};

class SnakeHead: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    // constructors
    SnakeHead(QGraphicsItem *parent=nullptr);

    // events
    void keyPressEvent(QKeyEvent* event);

    // public method
    void elongate();
	void teletransporte(QGraphicsItem *fruta);
    void moveBodies();
 public slots:
    void move();
private:
    QList<SnakeBody*> snakeBodies;
    QPointF prevPos;
    posicion direccion;
    bool vida;
};

#endif // SNAKEHEAD_H
