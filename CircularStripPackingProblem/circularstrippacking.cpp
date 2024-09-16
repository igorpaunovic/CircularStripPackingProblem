#include "circularstrippacking.h"

std::vector<Krug> CircularStripPacking::generisiNasumicneKrugove(int brojKrugova) {
    const std::vector<QPoint> pozicije = generisiNasumicneTacke(brojKrugova);
    std::vector<Krug> krugovi;
    QRandomGenerator generator;
    for (const QPoint &pozicija : pozicije) {
        int poluprecnik = generator.bounded(80) + 20;
        Krug* krug = new Krug(pozicija, poluprecnik);
        krugovi.push_back(*krug);
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
    }
    // TODO: Dodaj ucitavanje kruga iz fajla
    // else {
    //     _krugovi = ucitajPodatkeIzDatoteke(imeDatoteke);
    // }
}

void CircularStripPacking::pokreniAlgoritam()
{
    while (_pCrtanje && _yPoz < _pCrtanje->height())
    {
        _yPoz += 5;
        AlgoritamBaza_updateCanvasAndBlock()
    }

    emit animacijaZavrsila();
}

void CircularStripPacking::crtajAlgoritam(QPainter *painter) const
{
    if (!painter) return;

    painter->drawRect(_pravougaonik);

    for (const Krug &krug : _krugovi) {
        krug.draw(painter);
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
