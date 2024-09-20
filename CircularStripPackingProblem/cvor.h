#ifndef CVOR_H
#define CVOR_H

#include "krug.h"

class Cvor
{
public:
    Cvor(Krug* krug, double gustina = 99999);

    Krug* _krug;
    double _gustina;
};

#endif // CVOR_H
