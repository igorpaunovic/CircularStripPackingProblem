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

bool Krug::neSeceKrug(Krug& krug) const {
    int udaljenostX = (_centar.x() - krug._centar.x());
    int udaljenostY = (_centar.y() - krug._centar.y());
    qDebug() << "Udaljenost centara: " << int(qSqrt(udaljenostX*udaljenostX + udaljenostY*udaljenostY));
    qDebug() << "Zbir Poluprecnika: " << int(qSqrt(udaljenostX*udaljenostX + udaljenostY*udaljenostY));
    return (_poluprecnik + krug._poluprecnik <= int(qSqrt(udaljenostX*udaljenostX + udaljenostY*udaljenostY)));
};

bool Krug::neSeceKrugove(std::vector<Krug*>& krugovi) const {
    for (const auto &krug : krugovi) {
        if (!neSeceKrug(*krug)) {
            qDebug() << "NE SECE";
            return false;
        }
    }
    qDebug() << "SECE";
    return true;
};
