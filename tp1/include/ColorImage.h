#ifndef COLORIMAGE_H_INCLUDED
#define COLORIMAGE_H_INCLUDED

typedef unsigned short int ushort;
typedef unsigned char ubyte;
typedef unsigned int uint;

#include "Color.h"

class ColorImage
{
    private :
       ushort width;
       ushort height;
       Color * array;


    public :
    ColorImage(ushort w, ushort h);
    ColorImage(const ColorImage& original);
    void clear();
    Color pixel(ushort x, ushort y) const;
    Color& pixel(ushort x, ushort y);
    ~ColorImage();


};


#endif // COLORIMAGE_H_INCLUDED
