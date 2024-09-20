#include "ugaonapozicija.h"

UgaonaPozicija::UgaonaPozicija(
    QPoint pozicija,
    Krug* krug,
    int mldp,
    Krug* krug1,
    Krug* krug2,
    StranicaPravougaounika stranica1,
    StranicaPravougaounika stranica2
    ) : _pozicija(pozicija), _krug(krug), _mldp(mldp), _krug1(krug1), _krug2(krug2), _stranica1(stranica1), _stranica2(stranica2)
{}

void UgaonaPozicija::postaviKrug() const {
    _krug->pomeri(_pozicija);
}
