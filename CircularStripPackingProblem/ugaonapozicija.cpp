#include "ugaonapozicija.h"

UgaonaPozicija::UgaonaPozicija(
    const Krug& krug,
    Krug* krug1,
    Krug* krug2,
    StranicaPravougaounika stranica1,
    StranicaPravougaounika stranica2
) : _krug1(krug1), _krug2(krug2), _stranica1(stranica1), _stranica2(stranica2)
{
    _krug = Krug(krug._centar, krug._poluprecnik);
}
