#include "menu.h"
#include "ui_menu.h"

//menu generador de la ventana
menu::menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
}
//destructor de ventana
menu::~menu()
{
    delete ui;
}
