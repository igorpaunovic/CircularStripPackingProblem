#ifndef KRUG_H
#define KRUG_H

#include <QPoint>
#include <QColor>
#include <QPaintEvent>
#include <QWidget>
#include <QPainter>
#include <vector>
#include <QtMath>
#include <set>
#include <Eigen/Dense>

class Krug
{
public:
    Krug(const QPoint& centar = QPoint(0,0), const int poluprecnik = 0, const QColor& boja = Qt::black, QWidget *pCrtanja = nullptr);
    void crtaj(QPainter *painter) const;
    void pomeri(QPoint noviCentar);
    int gore() const;
    int dole() const;
    int levo() const;
    int desno() const;
    bool neSeceKrug(Krug& krug) const;
    bool neSeceKrugove(std::set<Krug*>& krugovi) const;
    std::vector<QPoint*> ugaoIzmedjuDvaKruga(const Krug &krug1, const Krug &krug2) const;

    QPoint _centar;
    int _poluprecnik;
    QColor _boja;
    QWidget* _pCrtanja;
private:
    std::vector<Krug> generisiNasumicneKrugove(int brojKrugova = 20);
};

#endif // KRUG_H
