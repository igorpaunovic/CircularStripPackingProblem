#ifndef KRUG_H
#define KRUG_H

#include <QPoint>
#include <QColor>
#include <QPaintEvent>
#include <QWidget>
#include <QPainter>
#include <QPropertyAnimation>
#include <QObject>

class Krug: public QObject
{
    Q_OBJECT
public:
    explicit Krug(QObject *parent = nullptr);
    Krug(const QPoint& centar = QPoint(0,0), const int poluprecnik = 0, const QColor& boja = Qt::black, QWidget *pCrtanja = nullptr, QObject *parent = nullptr);
    void crtaj(QPainter *painter) const;
    void pomeri(QPoint noviCentar);

    QPoint _centar;
    int _poluprecnik;
    QColor _boja;
    QWidget* _pCrtanja;
};

#endif // KRUG_H
