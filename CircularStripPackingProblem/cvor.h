#ifndef CVOR_H
#define CVOR_H

#include "krug.h"

class Cvor
{
public:
    Cvor(Krug* krug, int mldp = 99999);

    Krug* _krug;
    int _mldp;
};

#endif // CVOR_H
