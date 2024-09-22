#include "circularstrippacking.h"

std::vector<Krug> CircularStripPacking::generisiNasumicneKrugove(int brojKrugova) {
    const std::vector<QPoint> pozicije = generisiNasumicneTacke(brojKrugova);
    std::vector<Krug> krugovi;
    QRandomGenerator generator;
    for (const QPoint &pozicija : pozicije) {
        int poluprecnik = generator.bounded(70) + 15;
        krugovi.push_back(Krug(QPoint(pozicija.x(), pozicija.y()/3), poluprecnik));
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
        _krugovi = generisiNasumicneKrugove(brojKrugova);
        for (auto &_krug : _krugovi) {
            Krug krug(_krug._centar, _krug._poluprecnik);
            _preostaliKrugovi.insert(krug);
            _ukupnaPovrsinaKrugova += krug._poluprecnik * _krug._poluprecnik;
        }
        _ukupnaPovrsinaKrugova *= M_PI;
    }
}

int CircularStripPacking::pravougaonikLevo() const {
    return _pravougaonik.left();
};

int CircularStripPacking::pravougaonikDesno() const {
    return _pravougaonik.right();
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
    } else if (krug.desno() > pravougaonikDesno()) {
        return false;
    } else {
        return true;
    }
}

bool CircularStripPacking::legalanKrug(const Krug& krug, std::vector<Krug>& postavljeniKrugovi) const {
    if (pripadaPravougaoniku(krug) && krug.neSeceKrugove(postavljeniKrugovi)) {
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

int CircularStripPacking::MLDP(Krug& krug, std::vector<Krug>& postavljeniKrugovi, Krug* krug1, Krug* krug2, StranicaPravougaounika stranica1, StranicaPravougaounika stranica2) const {
    double mldp = 99999;

    for (Krug _krug : postavljeniKrugovi) {
        if ((krug1 && (_krug == *krug1)) || (krug2 && (_krug == *krug2))) {
            continue;
        }
        int tmp = krug.udaljenostOrKruga(_krug);
        if (tmp < mldp) {
            mldp = tmp;
        }
    }

    int tmp = pravougaonikGore() - krug.gore();
    if (stranica1 != StranicaPravougaounika::Gore && stranica2 != StranicaPravougaounika::Gore && tmp < mldp) {
        mldp = tmp;
    }

    tmp = krug.dole() - pravougaonikDole();
    if (stranica1 != StranicaPravougaounika::Dole && stranica2 != StranicaPravougaounika::Dole && tmp < mldp) {
        mldp = tmp;
    }

    tmp = krug.levo() - pravougaonikLevo();
    if (stranica1 != StranicaPravougaounika::Levo && stranica2 != StranicaPravougaounika::Levo && tmp < mldp) {
        mldp = tmp;
    }

    return mldp;
}

std::vector<UgaonaPozicija> CircularStripPacking::moguciUglovi(Krug* krug, std::vector<Krug>& postavljeniKrugovi) const {
    qDebug() << "Moguci uglovi";
    qDebug() << "Broj postavljenih krugova: " << postavljeniKrugovi.size();
    std::vector<UgaonaPozicija> potencijalniUglovi;
    // Uglovi izmedju dve stranice pravougaonika
    QPoint centarLevoDole(pravougaonikLevo() + krug->_poluprecnik, pravougaonikDole() + krug->_poluprecnik);
    Krug potencijalniKrug(centarLevoDole, krug->_poluprecnik);
    if (legalanKrug(potencijalniKrug, postavljeniKrugovi)) {
        qDebug("DODAT levo dole");
        potencijalniUglovi.push_back(
            UgaonaPozicija(
                centarLevoDole,
                krug,
                MLDP(potencijalniKrug, postavljeniKrugovi, nullptr, nullptr, StranicaPravougaounika::Dole, StranicaPravougaounika::Levo)
            )
        );
    }
    // Gore levo
    QPoint centarLevoGore(pravougaonikLevo() + krug->_poluprecnik, pravougaonikGore() - krug->_poluprecnik);
    potencijalniKrug._centar = centarLevoGore;
    if (legalanKrug(potencijalniKrug, postavljeniKrugovi)) {
        qDebug("DODAT levo gore");
        potencijalniUglovi.push_back(
            UgaonaPozicija(
                centarLevoGore,
                krug,
                MLDP(potencijalniKrug, postavljeniKrugovi, nullptr, nullptr, StranicaPravougaounika::Gore, StranicaPravougaounika::Levo)
            )
        );
    }

    // Uglovi izmedju stranice i kruga
    for (auto &_krug : postavljeniKrugovi) {
        qDebug() << "Krug: " << krug->_centar << ", poluprecnik: " << krug->_poluprecnik;
        if (pravougaonikGore()-_krug.gore() <= 2*krug->_poluprecnik) {
            int dx = izracunajKatetu(krug->_poluprecnik + _krug._poluprecnik, krug->_poluprecnik - (pravougaonikGore()-_krug._centar.y()));
            QPoint centar(_krug._centar.x()+dx, pravougaonikGore()-krug->_poluprecnik);
            potencijalniKrug._centar = centar;
            if (legalanKrug(potencijalniKrug, postavljeniKrugovi)) {
                qDebug("DODAT izmedju gornje stranice i kruga 1");
                potencijalniUglovi.push_back(
                    UgaonaPozicija(
                        centar,
                        krug,
                        MLDP(potencijalniKrug, postavljeniKrugovi, &_krug, nullptr, StranicaPravougaounika::Gore)
                    )
                );
            }
            centar.setX(_krug._centar.x()-dx);
            potencijalniKrug._centar = centar;
            if (legalanKrug(potencijalniKrug, postavljeniKrugovi)) {
                qDebug("DODAT izmedju gornje stranice i kruga 2");
                potencijalniUglovi.push_back(
                    UgaonaPozicija(
                        centar,
                        krug,
                        MLDP(potencijalniKrug, postavljeniKrugovi, &_krug, nullptr, StranicaPravougaounika::Gore)
                    )
                );
            }
        }
        if (_krug.dole() - pravougaonikDole() <= 2*krug->_poluprecnik) {
            int dx = izracunajKatetu(krug->_poluprecnik + _krug._poluprecnik, krug->_poluprecnik - (_krug._centar.y()-pravougaonikDole()));
            QPoint centar(_krug._centar.x()+dx, pravougaonikDole()+krug->_poluprecnik);
            potencijalniKrug._centar = centar;
            if (legalanKrug(potencijalniKrug, postavljeniKrugovi)) {
                qDebug("DODAT izmedju donje stranice i kruga 1");
                potencijalniUglovi.push_back(
                    UgaonaPozicija(
                        centar,
                        krug,
                        MLDP(potencijalniKrug, postavljeniKrugovi, &_krug, nullptr, StranicaPravougaounika::Dole)
                    )
                );
            }
            centar.setX(_krug._centar.x()-dx);
            potencijalniKrug._centar = centar;
            if (legalanKrug(potencijalniKrug, postavljeniKrugovi)) {
                qDebug("DODAT izmedju donje stranice i kruga 2");
                potencijalniUglovi.push_back(
                    UgaonaPozicija(
                        centar,
                        krug,
                        MLDP(potencijalniKrug, postavljeniKrugovi, &_krug, nullptr, StranicaPravougaounika::Dole)
                    )
                );
            }
        }
        if (_krug.levo() - pravougaonikLevo() <= 2*krug->_poluprecnik) {
            int dy = izracunajKatetu(krug->_poluprecnik + _krug._poluprecnik, krug->_poluprecnik - (_krug._centar.x()-pravougaonikLevo()));
            QPoint centar(pravougaonikLevo()+krug->_poluprecnik, _krug._centar.y()+dy);
            potencijalniKrug._centar = centar;
            if (legalanKrug(potencijalniKrug, postavljeniKrugovi)) {
                qDebug("DODAT izmedju leve stranice i kruga");
                potencijalniUglovi.push_back(
                    UgaonaPozicija(
                        centar,
                        krug,
                        MLDP(potencijalniKrug, postavljeniKrugovi, &_krug, nullptr, StranicaPravougaounika::Levo)
                    )
                );
            }
            centar.setY(_krug._centar.y()-dy);
            potencijalniKrug._centar = centar;
            if (legalanKrug(potencijalniKrug, postavljeniKrugovi)) {
                qDebug("DODAT izmedju leve stranice i kruga");
                potencijalniUglovi.push_back(
                    UgaonaPozicija(
                        centar,
                        krug,
                        MLDP(potencijalniKrug, postavljeniKrugovi, &_krug, nullptr, StranicaPravougaounika::Levo)
                    )
                );
            }
        }
    }
    // Uglovi izmedju dva kruga
    qDebug() << "Uglovi izmedju dva kruga";
    for (auto &krug1 : postavljeniKrugovi) {
        for (auto &krug2 : postavljeniKrugovi) {
            std::vector<QPoint> ugloviIzmedjuDvaKruga= krug->ugaoIzmedjuDvaKruga(krug1, krug2);
            for (const auto &ugao : ugloviIzmedjuDvaKruga) {
                potencijalniKrug._centar = ugao;
                qDebug("DODAT izmedju dva kruga");
                if (legalanKrug(potencijalniKrug, postavljeniKrugovi)) {
                    potencijalniUglovi.push_back(UgaonaPozicija(ugao, krug, MLDP(potencijalniKrug, postavljeniKrugovi, &krug1, &krug2)));
                }
            }
        }
    }
    return potencijalniUglovi;
}

std::vector<Cvor> CircularStripPacking::granaj(std::vector<Cvor>& cvorovi, int brojNajboljih) {
    qDebug() << "granaj";
    std::vector<UgaonaPozicija> sveUgaonePozicije;

    for (size_t i = 0; i < cvorovi.size(); i++) {
        Cvor* cvorRef = &cvorovi[i];
        for (Krug krug : cvorovi[i]._preostaliKrugovi) {
            std::vector<UgaonaPozicija> ugaonePozicijeKruga = moguciUglovi(&krug, cvorovi[i]._postavljeniKrugovi);
            for (UgaonaPozicija& ugaonaPozicija : ugaonePozicijeKruga) {
                ugaonaPozicija._cvor = cvorRef;
                sveUgaonePozicije.push_back(ugaonaPozicija);
            }
        }
    }

    std::sort(sveUgaonePozicije.begin(), sveUgaonePozicije.end(), [](const UgaonaPozicija &a, const UgaonaPozicija &b) {
        return a._mldp < b._mldp;
    });
    int uzmiNajboljih = std::min(brojNajboljih, int(sveUgaonePozicije.size()));
    sveUgaonePozicije = std::vector<UgaonaPozicija>(sveUgaonePozicije.begin(), sveUgaonePozicije.begin() + uzmiNajboljih);

    std::vector<Cvor> decaCvorovi;
    for (UgaonaPozicija ugaonaPozicija : sveUgaonePozicije) {
        ugaonaPozicija.postaviKrug();
        Cvor deteCvor(*ugaonaPozicija._krug, ugaonaPozicija._cvor->_postavljeniKrugovi,  ugaonaPozicija._cvor->_preostaliKrugovi);
        decaCvorovi.push_back(deteCvor);
    }

    qDebug() << "uzeto najboljih cvorova: " << decaCvorovi.size();
    return decaCvorovi;
}

void CircularStripPacking::PohlepnaMLDPProcedura(Cvor& cvor, double& gustina, bool& nadjenoResenje) {
    qDebug() << "PohlepnaMLDPProcedura";
    _postavljeniKrugovi = cvor._postavljeniKrugovi;
    _preostaliKrugovi = cvor._preostaliKrugovi;
    AlgoritamBaza_updateCanvasAndBlock();

    double povrsinaPostavljenihKrugova = 0.0;
    for (auto it = _preostaliKrugovi.begin(); it != _preostaliKrugovi.end();) {
        Krug krug = *it;
        std::vector<UgaonaPozicija> ugaonePozicije = moguciUglovi(&krug, _postavljeniKrugovi);
        auto najboljaPozicijaIt = std::min_element(ugaonePozicije.begin(), ugaonePozicije.end(),
                                                    [](const UgaonaPozicija& a, const UgaonaPozicija& b) {
                                                        return a._mldp < b._mldp;
                                                    }
        );
        if (najboljaPozicijaIt == ugaonePozicije.end()) {
            nadjenoResenje = false;
            gustina = povrsinaPostavljenihKrugova/(_pravougaonik.height()*_pravougaonik.width());
            return;
        }
        UgaonaPozicija najboljaPozicija = *najboljaPozicijaIt;
        najboljaPozicija.postaviKrug();
        _preostaliKrugovi.erase(it++);
        _postavljeniKrugovi.push_back(krug);
        AlgoritamBaza_updateCanvasAndBlock();
    }
    gustina = povrsinaPostavljenihKrugova/(_pravougaonik.height()*_pravougaonik.width());
    nadjenoResenje = true;
    _postavljeniKrugovi.clear();
    return;
}

std::vector<Cvor> CircularStripPacking::LABP(std::vector<Cvor> B, int w, bool& zadovoljivo) {
    std::vector<Cvor> Bw = granaj(B);

    for (Cvor cvor : Bw) {
        double gustina;
        bool nadjenoResenje;
        PohlepnaMLDPProcedura(cvor, gustina, nadjenoResenje);
        cvor._gustina = gustina;
        Bw.push_back(cvor);
        if (nadjenoResenje) {
            // TODO - Sacuvaj najbolje resenje
            zadovoljivo = true;
            return Bw;
        } 
    }

    std::sort(Bw.begin(), Bw.end(), [](const Cvor &a, const Cvor &b) {
        return a._gustina > b._gustina;
    });

    w = std::min(w, int(Bw.size()));
    Bw = std::vector<Cvor>(Bw.begin(), Bw.begin() + w);

    return Bw;

}

int CircularStripPacking::BSLA(Cvor cvor, int w, int L1, int L2, bool& zadovoljivo, int tolerancija) {
    qDebug() << "BSLA";
    int najboljeL = 99999;
    std::vector<Cvor> B;
    std::vector<Cvor> Bw;
    B.push_back(cvor);
    int l = 2;
    while (L2 - L1 > tolerancija) {
        int L = (L2-L1)/2;
        _pravougaonik.setWidth(L);
        while (!B.empty() && zadovoljivo == false) {
            qDebug() << "l: " << l;
            Bw = LABP(B, w, zadovoljivo);
            if (zadovoljivo) {
                qDebug() << "Zadovoljivo resenje";
                najboljeL = L;
                L2 = L;
                _pravougaonik.setWidth(L2);
            } else {
                l++;
                B = Bw;
                Bw.clear();
            }
        }
        if (zadovoljivo == false) {
            L1 = L;
        }
    }
    return najboljeL;
}

void CircularStripPacking::pokreniAlgoritam()
{
    size_t index = 0;
    size_t index2 = 3;
    Krug krug = _krugovi[index];
    Krug krug2 = _krugovi[index2];
    krug.pomeri(QPoint(pravougaonikLevo() + krug._poluprecnik, pravougaonikDole() + krug._poluprecnik));
    krug2.pomeri(QPoint(pravougaonikLevo() + krug2._poluprecnik, pravougaonikGore() - krug2._poluprecnik));

    std::vector<Krug> postavljeniKrugovi = {krug};
    std::vector<Krug> postavljeniKrugovi2 = {krug2};
    std::set<Krug> preostaliKrugovi;
    std::set<Krug> preostaliKrugovi2;
    for (size_t i = 0; i < _krugovi.size(); i++) {
        if (i == index) {
            continue;
        }
        preostaliKrugovi.insert(_krugovi[i]);
    }
    for (size_t i = 0; i < _krugovi.size(); i++) {
        if (i == index2) {
            continue;
        }
        preostaliKrugovi2.insert(_krugovi[i]);
    }

    std::vector<Cvor> B = {Cvor(krug, postavljeniKrugovi, preostaliKrugovi), Cvor(krug2, postavljeniKrugovi2, preostaliKrugovi2)};

    qDebug() << "Broj postavljenih krugova prvog cvora: " << B[0]._postavljeniKrugovi.size();
    qDebug() << "Broj preostalih krugova prvog cvora: " << B[0]._preostaliKrugovi.size();

    qDebug() << "Broj postavljenih krugova prvog cvora: " << B[1]._postavljeniKrugovi.size();
    qDebug() << "Broj preostalih krugova prvog cvora: " << B[1]._preostaliKrugovi.size();
    bool zadovoljivo = false;
    LABP(B, 10, zadovoljivo);

    // bool zadovoljivo = false;
    // auto it = _nepostavljeniKrugovi.begin();
    // Krug* krug = *it;
    // krug->pomeri(QPoint(pravougaonikLevo() + krug->_poluprecnik, pravougaonikDole() + krug->_poluprecnik));
    // krug->_boja = Qt::yellow;
    // _postavljeniKrugovi.insert(krug);
    // _nepostavljeniKrugovi.erase(krug);
    // AlgoritamBaza_updateCanvasAndBlock()
    // it++;
    // Krug* krug2 = *it;
    // std::vector<UgaonaPozicija>ugaonePozicije = moguciUglovi(krug2);
    // std::sort(ugaonePozicije.begin(), ugaonePozicije.end(), [](const UgaonaPozicija &a, const UgaonaPozicija &b) {
    //     return a._mldp > b._mldp;
    // });
    // krug2->pomeri(ugaonePozicije[0]._pozicija);
    // _postavljeniKrugovi.insert(krug2);
    // _nepostavljeniKrugovi.erase(krug2);
    // AlgoritamBaza_updateCanvasAndBlock()
    // Cvor cvor(krug2);
    // BSLA(cvor, 10, 500, 2000, zadovoljivo);


    // ugaonePozicije[0].postaviKrug();
    // _postavljeniKrugovi.insert(ugaonePozicije[0]._krug);
    // _nepostavljeniKrugovi.erase(ugaonePozicije[0]._krug);
    // Cvor cvor(ugaonePozicije[0]._krug);


    // AlgoritamBaza_updateCanvasAndBlock();

    // Cvor cvor2(*(_nepostavljeniKrugovi.begin()));
    // int najboljeL = BSLA(cvor2, 100, 100, 1400, zadovoljivo);
    // if (zadovoljivo) {
    //     if (najboljeL > _najboljeL) {
    //         _najboljeL = najboljeL;
    //         L2 = najboljeL;
    //     }
    // }

    // int w = 1;
    // int L1 = int(_ukupnaPovrsinaKrugova) / _pravougaonik.width();
    // int L2 = 1400;
    // while (w < 10) {
    //     qDebug() << "w: " << w;
    //     //TODO urediti ih opadajuce
    //     for (const auto& krug : _opadajuceUrdedjeniKrugovi) {
    //         krug->pomeri(QPoint(pravougaonikLevo() + krug->_poluprecnik, pravougaonikDole() + krug->_poluprecnik));
    //         _postavljeniKrugovi.insert(krug);
    //         _nepostavljeniKrugovi.erase(krug);
    //         AlgoritamBaza_updateCanvasAndBlock();

    //         std::vector<UgaonaPozicija>ugaonePozicije = moguciUglovi(krug);
    //         std::sort(ugaonePozicije.begin(), ugaonePozicije.end(), [](const UgaonaPozicija &a, const UgaonaPozicija &b) {
    //             return a._mldp > b._mldp;
    //         });
    //         int _w = std::min(w, int(ugaonePozicije.size()));
    //         std::vector<UgaonaPozicija> wNajboljihPozicija = std::vector<UgaonaPozicija>(ugaonePozicije.begin(), ugaonePozicije.begin() + _w);
    //         Cvor cvor2(wNajboljihPozicija[_w-1]._krug);
    //         wNajboljihPozicija[_w-1].postaviKrug();
    //         _postavljeniKrugovi.insert(wNajboljihPozicija[_w-1]._krug);
    //         _nepostavljeniKrugovi.erase(wNajboljihPozicija[_w-1]._krug);
    //         AlgoritamBaza_updateCanvasAndBlock();
    //         bool zadovoljivo;
    //         int najboljeL = BSLA(cvor2, w, L1, L2, zadovoljivo);
    //         if (zadovoljivo) {
    //             if (najboljeL > _najboljeL) {
    //                 _najboljeL = najboljeL;
    //                 L2 = najboljeL;
    //             }
    //         }
    //         wNajboljihPozicija[_w-1]._krug->vrati();
    //         _postavljeniKrugovi.erase(wNajboljihPozicija[_w-1]._krug);
    //         _nepostavljeniKrugovi.insert(wNajboljihPozicija[_w-1]._krug);
    //         AlgoritamBaza_updateCanvasAndBlock();
    //         krug->vrati();
    //         _postavljeniKrugovi.erase(krug);
    //         _nepostavljeniKrugovi.insert(krug);
    //         AlgoritamBaza_updateCanvasAndBlock();
    //     }
    // }
    emit animacijaZavrsila();
}

void CircularStripPacking::crtajAlgoritam(QPainter *painter) const
{
    if (!painter) return;

    painter->drawRect(_pravougaonik);

    for (const auto &krug : _postavljeniKrugovi) {
        krug.crtaj(painter);
    }

    for (const auto &krug : _krugovi) {
        krug.crtaj(painter);
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
