#include "Game.h"
#include "SnakeHead.h"
#include "Fruit.h"
#include "pared.h"
#include <cstdlib>
#include <random>
#include <QCoreApplication>

using namespace std;

Game::Game(QWidget *parent): QGraphicsView(parent){
    // colocar la escena de qt
    scene = new QGraphicsScene(0,0,800,600);
    this->setFixedSize(800,600);
    setScene(scene);
}

void Game::start(){
    //fondo

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //anular la barra de desplazamiento horizontal de la ventana
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //anular la barra de desplazamiento vertical de la ventana

    QString filepath = QCoreApplication::applicationDirPath(); //carga ruta del ejecutable
    filepath = filepath + "/suelo.png";                         //Añade a ruta la imagen de fondo
    QGraphicsPixmapItem *fondo = new QGraphicsPixmapItem;
    fondo->setPixmap(filepath);
    scene->addItem(fondo);                                      //añadir la imagen a la escena

    // crear snakeHead
    SnakeHead* snakeHead = new SnakeHead();
    scene->addItem(snakeHead);
    snakeHead->setFocus();

    //colocar las 4 paredes de la ventana
    pared * muro = new pared ();
    muro->setPos(-5,0);
    scene->addItem(muro);
    
    pared * muro1 = new pared ();
    muro1->vertical();
    muro1->setPos(0,-5);
    scene->addItem(muro1);

    pared * muro2 = new pared ();
    muro2->vertical();
    muro2->setPos(0,585);
    scene->addItem(muro2);

    pared * muro4 = new pared ();
    muro4->setPos(785,0);
    scene->addItem(muro4);



    // agregar fruta con funcion rand de manera aleatoria
    Fruit* f1 = new Fruit();
    int equix,ye;

    //posicion aleatoria de fruta
    random_device rd; // obtener u numero random
    mt19937 eng(rd()); 
    uniform_int_distribution<> distr(10, 500); // definir el rango

    equix= distr(eng); // generar los numeros
    ye=distr(eng);


      f1->setPos(equix,ye);
      scene->addItem(f1); //colocar fruta en escena
}

//funcion de reiniciar el juego
void Game::restart(){
    // crear snakeHead
    SnakeHead* snakeHead = new SnakeHead();
    scene->addItem(snakeHead);
    snakeHead->setFocus();
}
