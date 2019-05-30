#include "pared.h"
#include <QBrush>

pared::pared()
{
    // draw
    setRect(0,0,20,600);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::yellow);
    setBrush(brush);

}

void pared::vertical()
{
    setRect(0,0,800,20);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::yellow);
    setBrush(brush);

}

