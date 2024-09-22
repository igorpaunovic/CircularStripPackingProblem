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
    std::vector<Krug> generisiNasumicneKrugove(int brojKrugova);
    bool pripadaPravougaoniku(Krug krug) const;
    int pravougaonikLevo() const;
    int pravougaonikDesno() const;
    int pravougaonikGore() const;
    int pravougaonikDole() const;
    QPoint ugaoIzmedjuDvaKruga(const Krug& krug1, const Krug& krug2) const;
    std::vector<UgaonaPozicija> moguciUglovi(Krug* krug, std::vector<Krug>& postavljeniKrugovi) const;
    bool legalanKrug(const Krug& krug, std::vector<Krug>& postavljeniKrugovi) const;
    bool krugDodirujePravougaonik(const Krug& krug) const;
    bool krugDodirujePravougaonikGore(const Krug& krug) const;
    bool krugDodirujePravougaonikDole(const Krug& krug) const;
    bool krugDodirujePravougaonikLevo(const Krug& krug) const;
    int MLDP(Krug& krug, std::vector<Krug>& postavljeniKrugovi, Krug* krug1 = nullptr, Krug* krug2 = nullptr, StranicaPravougaounika stranica1 = StranicaPravougaounika::Nijedna, StranicaPravougaounika stranica2 = StranicaPravougaounika::Nijedna) const;
    std::vector<Cvor> LABP(std::vector<Cvor> B, int w, bool& zadovoljivo);
    void PohlepnaMLDPProcedura(Cvor& cvor, double& gustina, bool& nadjenoResenje);
    int BSLA(Cvor cvor, int w, int L1, int L2, bool& zadovoljivo, int tolerancija = 30);
    std::vector<Cvor> granaj(std::vector<Cvor>& cvorovi, int brojNajboljih = 10);

private:
    std::vector<Krug> _krugovi;
    std::set<Krug> _preostaliKrugovi;
    std::vector<Krug> _postavljeniKrugovi;
    int _yPoz;
    QRect _pravougaonik;
    int _najboljeL = 99999;
    double _ukupnaPovrsinaKrugova = 0.0;
    std::vector<Krug*> _opadajuceUrdedjeniKrugovi;

};

#endif // CIRCULARSTRIPPACKING_H
