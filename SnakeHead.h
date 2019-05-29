#ifndef SNAKEHEAD_H
#define SNAKEHEAD_H

#include "SnakeBody.h"
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QList>
#include <QPointF>

#include <QDebug>
#include <QObject>

class SnakeHead: public QObject, QGraphicsRectItem{
    Q_OBJECT
public:
    // constructors
    SnakeHead(QObject *parent1=nullptr, QGraphicsItem *parent=nullptr);

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
};

#endif // SNAKEHEAD_H
