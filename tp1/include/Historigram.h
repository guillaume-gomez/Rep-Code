#ifndef HISTORIGRAM_H
#define HISTORIGRAM_H

#include "Image.hpp"

typedef unsigned short int ushort;
typedef unsigned char ubyte;
typedef unsigned int uint;

class Historigram
{
    public:
        Historigram(const Image<ubyte> & img);
        ~Historigram();
       Historigram(const Historigram& original);
        Image<ubyte> * draw() const ;
    private:
      uint * tabValeur;
      ushort gMax;


};

#endif // HISTORIGRAM_H
