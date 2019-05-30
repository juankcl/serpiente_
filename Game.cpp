#include "Game.h"
#include "SnakeHead.h"
#include "Fruit.h"
#include <cstdlib>
#include <random>
#include <QCoreApplication>

using namespace std;

Game::Game(QWidget *parent): QGraphicsView(parent){
    // set the scene
    scene = new QGraphicsScene(0,0,800,600);
    this->setFixedSize(800,600);
    setScene(scene);
}

void Game::start(){
    //fondo

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QString filepath = QCoreApplication::applicationDirPath(); //carga ruta del ejecutable
    filepath = filepath + "/suelo.png";
    QGraphicsPixmapItem *fondo = new QGraphicsPixmapItem;
    fondo->setPixmap(filepath);
    scene->addItem(fondo);

    //this->QgraphicsView->setScene(scene);


    // create snakeHead
    SnakeHead* snakeHead = new SnakeHead();
    scene->addItem(snakeHead);
    snakeHead->setFocus();



    // agregar fruta
    Fruit* f1 = new Fruit();
    int equix,ye;

    //posicion aleatoria de fruta
    random_device rd; // obtain a random number from hardware
    mt19937 eng(rd()); // seed the generator
    uniform_int_distribution<> distr(10, 500); // define the range

    equix= distr(eng); // generate numbers
    ye=distr(eng);


      f1->setPos(equix,ye);
      scene->addItem(f1);
}

void Game::restart(){
//    //fondo

//    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

//    QString filepath = QCoreApplication::applicationDirPath(); //carga ruta del ejecutable
//    filepath = filepath + "/suelo.png";
//    QGraphicsPixmapItem *fondo = new QGraphicsPixmapItem;
//    fondo->setPixmap(filepath);
//    scene->addItem(fondo);

//    //this->QgraphicsView->setScene(scene);


    // create snakeHead
    SnakeHead* snakeHead = new SnakeHead();
    scene->addItem(snakeHead);
    snakeHead->setFocus();

}
