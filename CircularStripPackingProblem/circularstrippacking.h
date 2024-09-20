#ifndef CIRCULARSTRIPPACKING_H
#define CIRCULARSTRIPPACKING_H

#include <set>
#include <QRandomGenerator>
#include <Eigen/Dense>

#include "algoritambaza.h"
#include "krug.h"
#include "ugaonapozicija.h"
#include "cvor.h"

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
    std::set<Krug*> generisiNasumicneKrugove(int brojKrugova);
    bool pripadaPravougaoniku(Krug krug) const;
    int pravougaonikLevo() const;
    int pravougaonikDesno() const;
    int pravougaonikGore() const;
    int pravougaonikDole() const;
    QPoint ugaoIzmedjuDvaKruga(const Krug& krug1, const Krug& krug2) const;
    std::vector<UgaonaPozicija> moguciUglovi(Krug* krug) const;
    bool legalanKrug(const Krug& krug) const;
    bool krugDodirujePravougaonik(const Krug& krug) const;
    bool krugDodirujePravougaonikGore(const Krug& krug) const;
    bool krugDodirujePravougaonikDole(const Krug& krug) const;
    bool krugDodirujePravougaonikLevo(const Krug& krug) const;
    int MLDP(const Krug& krug, Krug* krug1 = nullptr, Krug* krug2 = nullptr, StranicaPravougaounika stranica1 = StranicaPravougaounika::Nijedna, StranicaPravougaounika stranica2 = StranicaPravougaounika::Nijedna) const;
    std::vector<Cvor> LABP(std::vector<Cvor>& B, bool& zadovoljivo);
    void PohlepnaMLDPProcedura(double& gustina);
    int BSLA(Cvor cvor, int w, int L, int D, int tolerancija = 30);

private:
    std::set<Krug*> _krugovi;
    std::set<Krug*> _nepostavljeniKrugovi;
    std::set<Krug*> _postavljeniKrugovi;
    int _yPoz;
    QRect _pravougaonik;
};

#endif // CIRCULARSTRIPPACKING_H
