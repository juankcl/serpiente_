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
    connect(timer, SIGNAL(timeout()),this,SLOT(move())); //Conectar la funcion mover con el timer
    timer->start(150); //cambio de posicion cada 150 ms
    // dibujar cabeza de serpiente
    setRect(20,20,50,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern); //color solido
    brush.setColor(Qt::green); //color de la cabeza verde
    setBrush(brush);

    // enfocar el objeto cabeza de serpiente
    setFlag(QGraphicsItem::ItemIsFocusable,true);

    SnakeBody* b1 = new SnakeBody(); //crear objeto cuerpo de serpiente
    b1->setPos(50,0); 		     //colocar detras de la cabeza 
    game->scene->addItem(b1); 	     //añadir a la escena 
    snakeBodies.prepend(b1);         //añadir a la lista del cuerpo
    vida=true; 			     //esta vivo
    direccion = DOWN;		     //empieza el juego hacia abajo

    //puntuacion de juego, fruta vale 10 pts
    puntuacion = new QGraphicsTextItem("Score: 0"); //empieza en cero
    puntuacion->setFont(QFont("arial",25));	   
    puntuacion->setDefaultTextColor(Qt::white);
    puntuacion->setPos(10,10);			    //colocar en la esquina superior izq
	puntuacion->setZValue(50);
	game->scene->addItem(puntuacion);		    //añadir a la escena

    gameover = nullptr; //inicializar el objeto gameover
    score = 0; //iniciar la puntuacion en cero
}

//este evento define la direccion del movimiento del timer
void SnakeHead::keyPressEvent(QKeyEvent *event){
    // mover arriba
    if (event->key() == Qt::Key_Up){
        if (direccion != DOWN)
          direccion = UP;
    }

    // mover abajo
    if (event->key() == Qt::Key_Down){
        if (direccion != UP)
        direccion = DOWN;
    }

    // mover derecha
    if (event->key() == Qt::Key_Right){
        if (direccion != LEFT)
        direccion = RIGHT;
    }

    // mover izquierda
    if (event->key() == Qt::Key_Left){
        if (direccion != RIGHT)
        direccion = LEFT;
    }

    // alargar cuerpo de serpiente si colisiona con fruta
    QList<QGraphicsItem*> cItems = collidingItems();
    for (size_t i = 0, n = cItems.size(); i < n; ++i){
        if (typeid(*cItems[i]) == typeid(Fruit)){
            // fruta encontrada en lista de colision
            elongate();
			teletransporte(cItems[i]);
        }
    }

    if(event->key() == Qt::Key_Space){
        //al presionar spacebar y la variable vida es false se reinicia el juego
        if(!vida){
            game->scene->clear();
            game->start();
            }
    }
    qDebug()<< direccion;

}

void SnakeHead::elongate(){
    // añadir nuevo cuerpo de serpiente a la lista
    SnakeBody* body = new SnakeBody();
    snakeBodies.prepend(body);

    // añadir correctamente la posicion del cuerpo
    body->setPos(-200,-200); 
    game->scene->addItem(body); //agregar a la escena
}

//con esta funcion movemos la fruta cada que hay colision
void SnakeHead::teletransporte(QGraphicsItem *fruta)
{
	int equix,ye;

	bool exit = false;

	//Ciclo para encontrar un lugar en donde poner la fruta
	do{
		//Posicion random
		random_device rd; // obtner numero random
		mt19937 eng(rd());
        uniform_int_distribution<> distr(0, 15); // definir rango

		equix= distr(eng); // generar numeros para x

        random_device rdA; 
        mt19937 engA(rdA());
        uniform_int_distribution<> distrA(0, 12);


        	ye=distrA(engA); //generar numero para y
        fruta->setPos(equix*50,ye*50); //colocar posicion en la escena

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
    // atraviesa la lista de cuerpos y los mueve adecuadamente
    // mover todos los cuerpos de atras hacia adelante
    for (size_t i = 0, n = snakeBodies.size()-1; i < n; ++i){
        snakeBodies[i]->setPos(snakeBodies[i+1]->pos());
    }

    // mover el cuerpo frontal a la posicion antes de la cabeza
    snakeBodies.last()->setPos(prevPos);
}

//movimiento es continuo, solo indicaremos la direccion del mismo
void SnakeHead::move()
{
	//establecer limites de serpiente
    if (x()<0 || x()>800 || y()<0 || y()>600)
        vida=false;

    if(vida){ //condicion de movimiento
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

    if (!vida) // si la serpiente muere, colocar los objetos de texto gameover
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
