#include "pared.h"
#include <QBrush>

pared::pared()
{
    // dibujar el objeto pared
    setRect(0,0,20,600);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::yellow);
    setBrush(brush);

}

//cambio de orientacion de objeto pared
void pared::vertical()
{
    setRect(0,0,800,20);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern); //color solido
    brush.setColor(Qt::yellow); //pared es color amarillo
    setBrush(brush);

}

