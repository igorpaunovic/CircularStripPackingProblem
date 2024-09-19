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

class ugaonaPozicija
{
public:
    ugaonaPozicija(QPoint pozicija);

    QPoint _pozicija;
    Krug* _krug1;
    Krug* _krug2;
    StranicaPravougaounika _stranica1;
    StranicaPravougaounika _stranica2;
};

#endif // UGAONAPOZICIJA_H
