#ifndef CIRCULARSTRIPPACKING_H
#define CIRCULARSTRIPPACKING_H

#include "algoritambaza.h"

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

private:
    std::vector<QPoint> _krugovi;
    int _yPoz;
};

#endif // CIRCULARSTRIPPACKING_H
