#include "menu.h"
#include "ui_menu.h"

menu::menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);

    //->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

menu::~menu()
{
    delete ui;
}
