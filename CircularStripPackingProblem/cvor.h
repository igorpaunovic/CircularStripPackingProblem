#ifndef CVOR_H
#define CVOR_H

#include "krug.h"
#include "ugaonapozicija.h"

class CirclularStripPacking;

class Cvor
{
public:
    Cvor(Krug krug, std::vector<Krug> postavljeniKrugovi = {}, std::set<Krug> preostaliKrugovi = {}, double gustina = 99999);
    // std::vector<Cvor> granaj() { // TODO - ipak ovo u circular
    //     // pazi da li krug ima vec postavljenu lokaciju
    //     _krug->pomeri(_krug->_centar);

    //     std::vector<UgaonaPozicija> ugaonePozicijeDece = sve;

    // }

    Krug _krug;
    std::vector<Krug> _postavljeniKrugovi;
    std::set<Krug> _preostaliKrugovi;
    double _gustina;
};

#endif // CVOR_H
