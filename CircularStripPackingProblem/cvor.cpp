#include "cvor.h"

Cvor::Cvor(Krug krug, std::vector<Krug> postavljeniKrugovi, std::set<Krug> preostaliKrugovi, double gustina)
    : _krug(krug), _postavljeniKrugovi(postavljeniKrugovi), _preostaliKrugovi(preostaliKrugovi), _gustina(gustina)
{}
