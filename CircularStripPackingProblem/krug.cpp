#include "krug.h"

Krug::Krug(const QPoint& centar, int poluprecnik, const QColor& boja, QWidget *pCrtanja)
    : _centar(centar), _poluprecnik(poluprecnik), _boja(boja), _pCrtanja(pCrtanja)
{};

void Krug::crtaj(QPainter *painter) const {
    painter->setPen(Qt::blue);
    painter->setBrush(_boja);
    painter->drawEllipse(_centar, _poluprecnik, _poluprecnik);
}

void Krug::pomeri(QPoint noviCentar) {
    _centar = noviCentar;
    _boja = Qt::red;
}

int Krug::gore() const {
    return _centar.y() + _poluprecnik;
};

int Krug::dole() const {
    return _centar.y() - _poluprecnik;
};

int Krug::levo() const {
    return _centar.x() - _poluprecnik;
};

int Krug::desno() const {
    return _centar.x() + _poluprecnik;
};
