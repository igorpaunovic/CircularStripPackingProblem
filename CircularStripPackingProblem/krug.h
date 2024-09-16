#ifndef KRUG_H
#define KRUG_H

#include <QPoint>
#include <QColor>
#include <QPaintEvent>
#include <QWidget>
#include <QPainter>

class Krug
{
public:
    Krug(const QPoint& centar = QPoint(0,0), const int poluprecnik = 0, const QColor& boja = Qt::black, QWidget *pCrtanja = nullptr);
    void draw(QPainter *painter) const;

    QPoint _centar;
    int _poluprecnik;
    QColor _boja;
    QWidget* _pCrtanja;
private:
    std::vector<Krug> generisiNasumicneKrugove(int brojKrugova = 20);
};

#endif // KRUG_H
