#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

typedef unsigned short int ushort;
typedef unsigned char ubyte;
typedef unsigned int uint;

const int RED = 0 ;
const int GREEN = 1 ;
const int BLUE = 2 ;

class Color
{
    private :
	ubyte  r, g, b;

	public :
	Color(ubyte _r = 0, ubyte _g = 0, ubyte _b = 0);
	ubyte getColor(const int Type ) const;
    ubyte& setColor(const int type , ubyte value);
    Color(const Color& original);
    ~Color();

};
#endif // COLOR_H_INCLUDED


