#include <QApplication>
#include "Game.h"

Game* game; //construir objeto juego

int main(int argc, char *argv[]) //inicio de juego
{
    QApplication a(argc, argv);

    game = new Game();
    game->show();
    game->start();

    return a.exec();
}
