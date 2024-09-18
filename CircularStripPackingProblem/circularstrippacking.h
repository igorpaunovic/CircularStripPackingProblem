#ifndef CIRCULARSTRIPPACKING_H
#define CIRCULARSTRIPPACKING_H

#include <set>
#include <QRandomGenerator>
#include <Eigen/Dense>

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
    std::vector<Krug*> generisiNasumicneKrugove(int brojKrugova);
    bool pripadaPravougaoniku(Krug krug) const;
    int pravougaonikLevo() const;
    int pravougaonikGore() const;
    int pravougaonikDole() const;
    QPoint ugaoIzmedjuDvaKruga(const Krug& krug1, const Krug& krug2) const;
    std::set<QPoint> moguciUglovi(const Krug& krug) const;

private:
    std::vector<Krug*> _krugovi;
    std::set<Krug*> _nepostavljeniKrugovi;
    std::set<Krug*> _postavljeniKrugovi;
    int _yPoz;
    QRect _pravougaonik;
};

#endif // CIRCULARSTRIPPACKING_H
