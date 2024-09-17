#include "circularstrippacking.h"

std::vector<Krug*> CircularStripPacking::generisiNasumicneKrugove(int brojKrugova) {
    const std::vector<QPoint> pozicije = generisiNasumicneTacke(brojKrugova);
    std::vector<Krug*> krugovi;
    QRandomGenerator generator;
    for (const QPoint &pozicija : pozicije) {
        int poluprecnik = generator.bounded(100) + 30;
        krugovi.push_back(new Krug(QPoint(pozicija.x(), pozicija.y()/3), poluprecnik));
    }
    return krugovi;
};

CircularStripPacking::CircularStripPacking(QWidget *pCrtanje,
                           int pauzaKoraka,
                           const bool &naivni,
                           std::string imeDatoteke,
                           int brojKrugova)
    : AlgoritamBaza(pCrtanje, pauzaKoraka, naivni), _yPoz(0), _pravougaonik(QRect(50, 450, 1400, 400))
{
    if (imeDatoteke == "") {
        // TODO: pozicija kruga nije bitna na pocetku, bitni su samo poluprecnici, uprosti to stavljajuci ih sve na nule
        _krugovi = generisiNasumicneKrugove(brojKrugova);
        qDebug() << _pravougaonik.left() << " " << _pravougaonik.right();
        qDebug() << _pravougaonik.bottom() << " " << _pravougaonik.top();
    }
    // TODO: Dodaj ucitavanje kruga iz fajla
    // else {
    //     _krugovi = ucitajPodatkeIzDatoteke(imeDatoteke);
    // }
}

bool CircularStripPacking::uPravougaoniku(Krug krug) const {
    if (krug._centar.y() + krug._poluprecnik > _pravougaonik.bottom()) {
        return false;
    } else if (krug._centar.y() - krug._poluprecnik < _pravougaonik.top()) {
        return false;
    } else if (krug._centar.x() - krug._poluprecnik < _pravougaonik.left()) {
        return false;
    } else {
        return true;
    }
}

// double CircularStripPacking::MLDP() {

// }

void CircularStripPacking::pokreniAlgoritam()
{
    QRandomGenerator generator;
    while (true) {
        for (const auto &krug : _krugovi) {
            if (!uPravougaoniku(*krug)) {
                int x = generator.bounded(1000);
                int y = generator.bounded(1000);
                if (uPravougaoniku(Krug(QPoint(x,y), krug->_poluprecnik))) {
                    krug->pomeri(QPoint(x,y));
                }
            }
        }
        AlgoritamBaza_updateCanvasAndBlock();
    }

    emit animacijaZavrsila();
}

void CircularStripPacking::crtajAlgoritam(QPainter *painter) const
{
    if (!painter) return;

    painter->drawRect(_pravougaonik);

    for (const auto &krug : _krugovi) {
        krug->crtaj(painter);
    }
}

void CircularStripPacking::pokreniNaivniAlgoritam()
{
    emit animacijaZavrsila();
}

void CircularStripPacking::crtajNaivniAlgoritam(QPainter *painter) const
{
    if (!painter) return;
}
