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
        for (const auto &krug : _krugovi) {
            _nepostavljeniKrugovi.insert(new Krug(krug->_centar, krug->_poluprecnik));
        }
    }
    // TODO: Dodaj ucitavanje kruga iz fajla
    // else {
    //     _krugovi = ucitajPodatkeIzDatoteke(imeDatoteke);
    // }
}

int CircularStripPacking::pravougaonikLevo() const {
    return _pravougaonik.left();
};

int CircularStripPacking::pravougaonikGore() const {
    return _pravougaonik.bottom();
};

int CircularStripPacking::pravougaonikDole() const {
    return _pravougaonik.top();
};

bool CircularStripPacking::pripadaPravougaoniku(Krug krug) const {
    if (krug.gore() > pravougaonikGore()) {
        return false;
    } else if (krug.dole() < pravougaonikDole()) {
        return false;
    } else if (krug.levo() < pravougaonikLevo()) {
        return false;
    } else {
        return true;
    }
}



std::set<QPoint> CircularStripPacking::moguciUglovi(const Krug& krug) const {

};

// double CircularStripPacking::MLDP() {

// }

void CircularStripPacking::pokreniAlgoritam()
{
    QRandomGenerator generator;
    while (true) {
        for (const auto &krug : _krugovi) {
            if (!pripadaPravougaoniku(*krug)) {
                int x = generator.bounded(1000);
                int y = generator.bounded(1000);
                Krug* potencijalniKrug = new Krug(QPoint(x,y), krug->_poluprecnik);
                if (pripadaPravougaoniku(*potencijalniKrug) and potencijalniKrug->neSeceKrugove(_postavljeniKrugovi)) {
                    krug->pomeri(QPoint(x,y));
                    _postavljeniKrugovi.insert(krug);
                }
                delete potencijalniKrug;
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
