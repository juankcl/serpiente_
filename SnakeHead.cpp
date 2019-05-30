#include "SnakeHead.h"
#include <QBrush>
#include "Fruit.h"
#include "SnakeBody.h"
#include "pared.h"
#include "Game.h"
#include <random>
#include <QTimer>
#include <QGraphicsTextItem>

using namespace std;

extern Game* game;

SnakeHead::SnakeHead(QGraphicsItem *parent): QObject (), QGraphicsRectItem (parent){
    //tiempo
    QTimer * timer  = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT(move()));
    timer->start(150);
    // draw
    setRect(20,20,50,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::green);
    setBrush(brush);

    // make focusable
    setFlag(QGraphicsItem::ItemIsFocusable,true);

    // TODO remove, test
    SnakeBody* b1 = new SnakeBody();
    b1->setPos(50,0);
    game->scene->addItem(b1);
    snakeBodies.prepend(b1);
    vida=true;
    direccion = DOWN;

    //el marcador
    puntuacion = new QGraphicsTextItem("Score: 0");
    puntuacion->setFont(QFont("arial",25));
    puntuacion->setDefaultTextColor(Qt::white);
    puntuacion->setPos(10,10);
    game->scene->addItem(puntuacion);

    gameover = nullptr;
    score = 0;

}
void SnakeHead::keyPressEvent(QKeyEvent *event){
    // move up
    if (event->key() == Qt::Key_Up){
        if (direccion != DOWN)
          direccion = UP;
//        prevPos = pos();
//        int xPos = x();
//        int yPos = y() - boundingRect().height();
//        setPos(xPos,yPos);
//        moveBodies();
    }

    // move down
    if (event->key() == Qt::Key_Down){
        if (direccion != UP)
        direccion = DOWN;
//        prevPos = pos();
//        int xPos = x();
//        int yPos = y() + boundingRect().height();
//        setPos(xPos,yPos);
//        moveBodies();
    }

    // move right
    if (event->key() == Qt::Key_Right){
        if (direccion != LEFT)
        direccion = RIGHT;
//        prevPos = pos();
//        int xPos = x() + boundingRect().width();
//        int yPos = y();
//        setPos(xPos,yPos);
//        moveBodies();
    }

    // move left
    if (event->key() == Qt::Key_Left){
        if (direccion != RIGHT)
        direccion = LEFT;
//        prevPos = pos();
//        int xPos = x() - boundingRect().width();
//        int yPos = y();
//        setPos(xPos,yPos);
//        moveBodies();
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

    if(event->key() == Qt::Key_Space){

//        prevPos = pos();
//        int xPos = x() + boundingRect().width();
//        int yPos = y();
//        setPos(xPos,yPos);
//        moveBodies();
        //reinicio
        if(!vida){
            game->scene->clear();
            game->start();
            }
    }
    qDebug()<< direccion;

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
        uniform_int_distribution<> distr(0, 15); // define the range

		equix= distr(eng); // generate numbers

        random_device rdA; // obtain a random number from hardware
        mt19937 engA(rdA()); // seed the generator
        uniform_int_distribution<> distrA(0, 11); // define the range


        ye=distrA(engA);
        fruta->setPos(equix*50,ye*50);

		//QDebug te deja imprimir dentro del ide de Qt como si fuera cout con motivos de debug
		qDebug() << fruta->collidingItems().size() ;

		//Si la fruta no colisiona con nada, salir del ciclo
		//(Si se agrega un fondo, probablemente se tiene que cambiar esta condicion a 1)
        if (fruta->collidingItems().size() == 1)
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

void SnakeHead::move()
{
    if (x()<0 || x()>800 || y()<0 || y()>600)
        vida=false;

    if(vida){
        switch (direccion) {
            case UP:{
                prevPos = pos();
                int xPos = x();
                int yPos = y() - boundingRect().height();
                setPos(xPos,yPos);
                moveBodies();
                break;
            }
            case DOWN:{
                prevPos = pos();
                int xPos = x();
                int yPos = y() + boundingRect().height();
                setPos(xPos,yPos);
                moveBodies();
                break;
            }
            case RIGHT:{
                prevPos = pos();
                int xPos = x() + boundingRect().width();
                int yPos = y();
                setPos(xPos,yPos);
                moveBodies();
                break;
            }
            case LEFT:{
                prevPos = pos();
                int xPos = x() - boundingRect().width();
                int yPos = y();
                setPos(xPos,yPos);
                moveBodies();
                break;
            }
        }
    }

    //alargar serpiente
    QList<QGraphicsItem*> cItems = collidingItems();
    for (size_t i = 0, n = cItems.size(); i < n; ++i){
        if (typeid(*cItems[i]) == typeid(Fruit)){
            // fruta encontrada en lista de colision
            elongate();
            teletransporte(cItems[i]);
            score+=10;
            puntuacion->setPlainText(QString("Score: " + QString::number(score)));
        }
        //colision con su cuerpo
        else if (typeid(*cItems[i]) == typeid(SnakeBody))
            vida=false;
        else if (typeid(*cItems[i]) == typeid(pared))
            vida=false;
    }

    if (!vida)
    {
        if (gameover == nullptr)
        {
            gameover = new QGraphicsTextItem("GAME\nOVER!");
            gameover->setFont(QFont("arial",150,99));
            gameover->setDefaultTextColor(Qt::red);
            gameover->setPos(90,50);
            scene()->addItem(gameover);

            //la instruccion de reiniciar
            puntuacion = new QGraphicsTextItem("Press Space Bar to Restart");
            puntuacion->setFont(QFont("Helvetica",20,99,true));
            puntuacion->setDefaultTextColor(Qt::green);
            puntuacion->setPos(230,500);
            game->scene->addItem(puntuacion);

        }
    }
}
