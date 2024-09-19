#include "circularstrippacking.h"

std::set<Krug*> CircularStripPacking::generisiNasumicneKrugove(int brojKrugova) {
    const std::vector<QPoint> pozicije = generisiNasumicneTacke(brojKrugova);
    std::set<Krug*> krugovi;
    QRandomGenerator generator;
    for (const QPoint &pozicija : pozicije) {
        int poluprecnik = generator.bounded(100) + 30;
        krugovi.insert(new Krug(QPoint(pozicija.x(), pozicija.y()/3), poluprecnik));
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
        qDebug() << "Pripada";
        return true;
    }
}

bool CircularStripPacking::legalanKrug(const Krug& krug) const {
    if (pripadaPravougaoniku(krug) && krug.neSeceKrugove(_postavljeniKrugovi)) {
        return true;
    }
    return false;
}

bool CircularStripPacking::krugDodirujePravougaonik(const Krug& krug) const {
    if (krug._centar.y() + krug._poluprecnik == pravougaonikGore()) {
        return true;
    } else if (krug._centar.y() - krug._poluprecnik == pravougaonikDole()) {
        return true;
    } else if (krug._centar.x() - krug._poluprecnik == pravougaonikLevo()) {
        return true;
    } else {
        return false;
    }
}

bool CircularStripPacking::krugDodirujePravougaonikGore(const Krug& krug) const {
    if (krug._centar.y() + krug._poluprecnik == pravougaonikGore()) {
        return true;
    } else {
        return false;
    }
}

bool CircularStripPacking::krugDodirujePravougaonikDole(const Krug& krug) const {
    if (krug._centar.y() - krug._poluprecnik == pravougaonikDole()) {
        return true;
    } else {
        return false;
    }
}

bool CircularStripPacking::krugDodirujePravougaonikLevo(const Krug& krug) const {
    if (krug._centar.x() - krug._poluprecnik == pravougaonikLevo()) {
        return true;
    } else {
        return false;
    }
}

int izracunajKatetu(int c, int a) {
    return int(qSqrt(c*c - a*a));
}

std::vector<UgaonaPozicija> CircularStripPacking::moguciUglovi(const Krug& krug) const {
    std::vector<UgaonaPozicija> potencijalniUglovi;
    // Uglovi izmedju dve stranice pravougaonika
    QPoint centarLevoDole(pravougaonikLevo() + krug._poluprecnik, pravougaonikDole() + krug._poluprecnik);
    Krug potencijalniKrug(centarLevoDole, krug._poluprecnik);
    if (legalanKrug(potencijalniKrug)) {
        qDebug("DODAT levo dole");
        potencijalniUglovi.push_back(UgaonaPozicija(potencijalniKrug, nullptr, nullptr, StranicaPravougaounika::Dole, StranicaPravougaounika::Levo));
    }
    // Gore levo
    QPoint centarLevoGore(pravougaonikLevo() + krug._poluprecnik, pravougaonikGore() - krug._poluprecnik);
    potencijalniKrug._centar = centarLevoGore;
    if (legalanKrug(potencijalniKrug)) {
        qDebug("Dodat levo gore");
        potencijalniUglovi.push_back(UgaonaPozicija(potencijalniKrug, nullptr, nullptr, StranicaPravougaounika::Gore, StranicaPravougaounika::Levo));
    }

    // Uglovi izmedju stranice i kruga
    int i = 0;
    for (const auto &_krug : _postavljeniKrugovi) {
        i++;
        qDebug() << "iteracija: " << i;
        qDebug("OVDE");
        if (pravougaonikGore()-_krug->gore() <= 2*krug._poluprecnik) {
            qDebug() << "USO gore krug";
            int dx = izracunajKatetu(krug._poluprecnik + _krug->_poluprecnik, krug._poluprecnik - (pravougaonikGore()-_krug->_centar.y()));
            QPoint centar(_krug->_centar.x()+dx, pravougaonikGore()-krug._poluprecnik);
            potencijalniKrug._centar = centar;
            if (legalanKrug(potencijalniKrug)) {
                potencijalniUglovi.push_back(UgaonaPozicija(potencijalniKrug, _krug, nullptr, StranicaPravougaounika::Gore));
                qDebug() << "dodao gore krug";
            }
            centar.setX(_krug->_centar.x()-dx);
            potencijalniKrug._centar = centar;
            if (legalanKrug(potencijalniKrug)) {
                potencijalniUglovi.push_back(UgaonaPozicija(potencijalniKrug, _krug, nullptr, StranicaPravougaounika::Gore));
                qDebug() << "dodao gore krug";
            }
        }
        qDebug() << _krug->dole() - pravougaonikDole() << " " << 2 * krug._poluprecnik;
        if (_krug->dole() - pravougaonikDole() <= 2*krug._poluprecnik) {
            qDebug() << "USO dole krug";
            int dx = izracunajKatetu(krug._poluprecnik + _krug->_poluprecnik, krug._poluprecnik - (_krug->_centar.y()-pravougaonikDole()));
            QPoint centar(_krug->_centar.x()+dx, pravougaonikDole()+krug._poluprecnik);
            potencijalniKrug._centar = centar;
            qDebug() << "Poluprecnik: " << krug._poluprecnik;
            if (legalanKrug(potencijalniKrug)) {
                potencijalniUglovi.push_back(UgaonaPozicija(potencijalniKrug, _krug, nullptr, StranicaPravougaounika::Dole));
                qDebug() << "dodao dole krug";
            }
            centar.setX(_krug->_centar.x()-dx);
            potencijalniKrug._centar = centar;
            if (legalanKrug(potencijalniKrug)) {
                potencijalniUglovi.push_back(UgaonaPozicija(potencijalniKrug, _krug, nullptr, StranicaPravougaounika::Dole));
                qDebug() << "dodao dole krug";
            }
        }
        if (_krug->levo() - pravougaonikLevo() <= 2*krug._poluprecnik) {
            qDebug() << "USO levo krug";
            int dy = izracunajKatetu(krug._poluprecnik + _krug->_poluprecnik, krug._poluprecnik - (_krug->_centar.x()-pravougaonikLevo()));
            QPoint centar(pravougaonikLevo()+krug._poluprecnik, _krug->_centar.y()+dy);
            potencijalniKrug._centar = centar;
            if (legalanKrug(potencijalniKrug)) {
                potencijalniUglovi.push_back(UgaonaPozicija(potencijalniKrug, _krug, nullptr, StranicaPravougaounika::Levo));
                qDebug() << "dodao levo krug";
            }
            centar.setY(_krug->_centar.y()-dy);
            potencijalniKrug._centar = centar;
            if (legalanKrug(potencijalniKrug)) {
                potencijalniUglovi.push_back(UgaonaPozicija(potencijalniKrug, _krug, nullptr, StranicaPravougaounika::Levo));
                qDebug() << "dodao levo krug";
            }
        }
    }
    // Uglovi izmedju dva kruga
    for (const auto &krug1 : _postavljeniKrugovi) {
        qDebug("IZMEDJU DVA KRUGA");
        for (const auto &krug2 : _postavljeniKrugovi) {
            std::vector<QPoint> ugloviIzmedjuDvaKruga= krug.ugaoIzmedjuDvaKruga(*krug1, *krug2);
            for (const auto &ugao : ugloviIzmedjuDvaKruga) {
                potencijalniKrug._centar = ugao;
                if (legalanKrug(potencijalniKrug)) {
                    potencijalniUglovi.push_back(UgaonaPozicija(potencijalniKrug, krug1, krug2));
                }
            }
        }
    }
    return potencijalniUglovi;
}

int CircularStripPacking::MLDP(const Krug& krug) const {
    double mldp = 99999;

    for (const auto& _krug : _postavljeniKrugovi) {
        int tmp = krug.udaljenostOrKruga(*_krug);
        if (tmp < mldp) {
            mldp = tmp;
        }
    }

    int tmp = pravougaonikGore() - krug.gore();
    if (tmp < mldp) {
        mldp = tmp;
    }

    tmp = krug.dole() - pravougaonikDole();
    if (tmp < mldp) {
        mldp = tmp;
    }

    tmp = krug.levo() - pravougaonikLevo();
    if (tmp < mldp) {
        mldp = tmp;
    }

    return mldp;
}

// bool CircularStripPacking::BSLA(std::vector<Krug>& krugovi, bool& zadovoljivo) const {
//     int w = krugovi.size();
//     std::vector<QPoint>
// }

void CircularStripPacking::pokreniAlgoritam()
{
    for (auto it = _nepostavljeniKrugovi.begin(); it != _nepostavljeniKrugovi.end();) {
        Krug* krug = *it;
        std::vector<UgaonaPozicija> potencijalnePozicije = moguciUglovi(*krug);
        qDebug() << "Broj mogucih pozicija" << potencijalnePozicije.size();
        if (potencijalnePozicije.size() > 0) {
            qDebug() << potencijalnePozicije[0]._krug._centar.x() << " " << potencijalnePozicije[0]._krug._centar.y();
            krug->pomeri(potencijalnePozicije[0]._krug._centar);
            _postavljeniKrugovi.insert(krug);
            qDebug() << "Ostalo postaviti: " << _nepostavljeniKrugovi.size();
            _nepostavljeniKrugovi.erase(it++);
            AlgoritamBaza_updateCanvasAndBlock();
        } else {
            ++it;
        }
    }
    AlgoritamBaza_updateCanvasAndBlock();

    emit animacijaZavrsila();
}

void CircularStripPacking::crtajAlgoritam(QPainter *painter) const
{
    if (!painter) return;

    painter->drawRect(_pravougaonik);

    for (const auto &krug : _postavljeniKrugovi) {
        krug->crtaj(painter);
    }

    for (const auto &krug : _nepostavljeniKrugovi) {
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
