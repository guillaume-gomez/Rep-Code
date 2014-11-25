#include "../include/Palette.h"

Palette::Palette()
{
    //ctor
}

Palette::~Palette()
{
    //dtor
}

Palette::Palette(const Palette& original)
{
    tabCouleurs = original.tabCouleurs;
}

Palette& Palette::operator=(const Palette& source)
{
    tabCouleurs = source.tabCouleurs;

    return *this;
}
