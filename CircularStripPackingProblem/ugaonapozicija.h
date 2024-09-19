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
        const Krug& krug,
        Krug* krug1 = nullptr,
        Krug* krug2 = nullptr,
        StranicaPravougaounika stranica1 = StranicaPravougaounika::Nijedna,
        StranicaPravougaounika stranica2 = StranicaPravougaounika::Nijedna
    );

    Krug _krug;
    Krug* _krug1;
    Krug* _krug2;
    StranicaPravougaounika _stranica1;
    StranicaPravougaounika _stranica2;
};

#endif // UGAONAPOZICIJA_H
