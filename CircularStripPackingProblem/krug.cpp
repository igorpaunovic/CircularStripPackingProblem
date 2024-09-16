#include "krug.h"

Krug::Krug(const QPoint& centar, int poluprecnik, const QColor& boja, QWidget *pCrtanja)
    : _centar(centar), _poluprecnik(poluprecnik), _boja(boja), _pCrtanja(pCrtanja)
{};

void Krug::draw(QPainter *painter) const {
    painter->setPen(Qt::blue);
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(_centar.x(), _centar.y()/3, 2*_poluprecnik, 2*_poluprecnik);
}
