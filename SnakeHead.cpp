#include "SnakeHead.h"
#include <QBrush>
#include "Fruit.h"
#include "SnakeBody.h"
#include "Game.h"
#include <random>

using namespace std;

extern Game* game;

SnakeHead::SnakeHead(QGraphicsItem *parent){
    // draw
    setRect(0,0,50,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::green);
    setBrush(brush);

    // make focusable
    setFlag(QGraphicsItem::ItemIsFocusable,true);

    // TODO remove, test
    SnakeBody* b1 = new SnakeBody();
    b1->setPos(0,50);
    game->scene->addItem(b1);
    snakeBodies.prepend(b1);

}

void SnakeHead::keyPressEvent(QKeyEvent *event){
    // move up
    if (event->key() == Qt::Key_Up){
        prevPos = pos();
        int xPos = x();
        int yPos = y() - boundingRect().height();
        setPos(xPos,yPos);
        moveBodies();
    }

    // move down
    if (event->key() == Qt::Key_Down){
        prevPos = pos();
        int xPos = x();
        int yPos = y() + boundingRect().height();
        setPos(xPos,yPos);
        moveBodies();
    }

    // move right
    if (event->key() == Qt::Key_Right){
        prevPos = pos();
        int xPos = x() + boundingRect().width();
        int yPos = y();
        setPos(xPos,yPos);
        moveBodies();
    }

    // move left
    if (event->key() == Qt::Key_Left){
        prevPos = pos();
        int xPos = x() - boundingRect().width();
        int yPos = y();
        setPos(xPos,yPos);
        moveBodies();
    }

    // alargar si choca con fruta
    QList<QGraphicsItem*> cItems = collidingItems();
    for (size_t i = 0, n = cItems.size(); i < n; ++i){
        if (typeid(*cItems[i]) == typeid(Fruit)){
            // fruta encontrada en lista de colision
            elongate();
			teletransporte(cItems[i]);
        }
    }
}

void SnakeHead::elongate(){
    // add new SnakeBody to list
    SnakeBody* body = new SnakeBody();
    snakeBodies.prepend(body);

    // properly position the body
    body->setPos(-200,-200); // TODO
    game->scene->addItem(body);
}
void SnakeHead::teletransporte(QGraphicsItem *fruta)
{
	int equix,ye;

	bool exit = false;

	//Ciclo para encontrar un lugar en donde poner la fruta
	do{
		//Posicion random
		random_device rd; // obtain a random number from hardware
		mt19937 eng(rd()); // seed the generator
		uniform_int_distribution<> distr(100, 600); // define the range

		equix= distr(eng); // generate numbers
		ye=distr(eng);
		fruta->setPos(equix,ye);

		//QDebug te deja imprimir dentro del ide de Qt como si fuera cout con motivos de debug
		qDebug() << fruta->collidingItems().size() ;

		//Si la fruta no colisiona con nada, salir del ciclo
		//(Si se agrega un fondo, probablemente se tiene que cambiar esta condicion a 1)
		if (fruta->collidingItems().size() == 0)
			exit = false;
		else
			exit = true;
	}while (exit);
}


void SnakeHead::moveBodies(){
    // traverses through list of bodies and moves them properly

    // move all bodies from back to front
    for (size_t i = 0, n = snakeBodies.size()-1; i < n; ++i){
        snakeBodies[i]->setPos(snakeBodies[i+1]->pos());
    }

    // move front body to previous position of head
    snakeBodies.last()->setPos(prevPos);
}
