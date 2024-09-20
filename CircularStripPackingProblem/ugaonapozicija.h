#ifndef UGAONAPOZICIJA_H
#define UGAONAPOZICIJA_H

#include <QPoint>

#include "krug.h"

enum StranicaPravougaounika {
    Gore,
    Dole,
    Levo,
    Nijedna
};

class UgaonaPozicija
{
public:
    UgaonaPozicija(
        QPoint pozicija,
        Krug* krug,
        int mldp,
        Krug* krug1 = nullptr,
        Krug* krug2 = nullptr,
        StranicaPravougaounika stranica1 = StranicaPravougaounika::Nijedna,
        StranicaPravougaounika stranica2 = StranicaPravougaounika::Nijedna
    );
    void postaviKrug() const;
    int MLDP() const;

    QPoint _pozicija;
    Krug* _krug;
    int _mldp;
    Krug* _krug1;
    Krug* _krug2;
    StranicaPravougaounika _stranica1;
    StranicaPravougaounika _stranica2;
};

#endif // UGAONAPOZICIJA_H
