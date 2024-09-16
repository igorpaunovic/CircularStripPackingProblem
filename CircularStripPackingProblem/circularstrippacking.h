#ifndef CIRCULARSTRIPPACKING_H
#define CIRCULARSTRIPPACKING_H

#include <QRandomGenerator>

#include "algoritambaza.h"
#include "krug.h"

class CircularStripPacking : public AlgoritamBaza
{
public:
    CircularStripPacking(QWidget *pCrtanje,
                 int pauzaKoraka,
                 const bool &naivni = false,
                 std::string imeDatoteke = "",
                 int brojKrugova = BROJ_SLUCAJNIH_OBJEKATA);

    void pokreniAlgoritam() final;
    void crtajAlgoritam(QPainter *painter) const final;
    void pokreniNaivniAlgoritam() final;
    void crtajNaivniAlgoritam(QPainter *painter) const final;
    std::vector<std::unique_ptr<Krug>> generisiNasumicneKrugove(int brojKrugova);

private:
    std::vector<std::unique_ptr<Krug>> _krugovi;
    int _yPoz;
    QRect _pravougaonik;
};

#endif // CIRCULARSTRIPPACKING_H
