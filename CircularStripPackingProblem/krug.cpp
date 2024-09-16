#include "krug.h"

Krug::Krug(QObject *parent)
    : QObject(parent) {
}

Krug::Krug(const QPoint& centar, const int poluprecnik, const QColor& boja, QWidget *pCrtanja, QObject *parent)
    : QObject(parent), _centar(centar), _poluprecnik(poluprecnik), _boja(boja), _pCrtanja(pCrtanja)
{};

void Krug::crtaj(QPainter *painter) const {
    painter->setPen(Qt::blue);
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(_centar.x(), _centar.y()/3, 2*_poluprecnik, 2*_poluprecnik);
}

void Krug::pomeri(QPoint noviCentar) {
    auto animation = new QPropertyAnimation(this, "position");
    animation->setDuration(2000); // Duration in milliseconds
    animation->setStartValue(_centar);
    animation->setEndValue(noviCentar);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->start();
    _centar = noviCentar;
}
