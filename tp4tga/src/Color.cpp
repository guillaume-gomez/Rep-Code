#include <iostream>
#include <stdexcept>
#include "../include/Color.h"

Color::Color(ubyte _r, ubyte _g, ubyte _b) : r(_r), g(_g), b(_b)
{}

Color::Color(const Color& original):r(original.r),g(original.g),b(original.b)
{/*std::cout << " color " << std::endl;*/}

Color::~Color()
{}

ubyte Color::getColor(const int type ) const
	{
		 if(type >= 0 && type <= 2)
     {
         //on pourrait tester si value e [0;255] mais on a l'effet compteur kilometrique
         switch(type)
         {
             case RED :
                return r;
             break;
             case GREEN :
                return g;
             break;
             case BLUE :
                return b;
             break;
         }
     }
     else
        throw std::runtime_error("Color::getColor(const int type) type couleur incorrecte");
    return 0;
	}

 void Color::setColor( int type , ubyte value)
 {
     if(type >= 0 && type <= 2)
     {
         //on pourrait tester si value e [0;255] mais on a l'effet compteur kilometrique
         switch(type)
         {
             case RED :
             r = value;
             break;
             case GREEN :
             g = value;
             break;
             case BLUE :
             b = value;
             break;
         }
     }
     else
        throw std::runtime_error("Color::setColor(const int type, ubyte value) : type couleur incorrecte");

 }

Color& Color::operator=(const Color& source)
{
    r = source.r;
    g = source.g;
    b = source.b;

    return *this;
}

 Color operator* ( double multiplicateur , const Color& r2)
 {
     Color c( multiplicateur * r2.r , multiplicateur * r2.g , multiplicateur * r2.b );
     return c ;
 }

 Color operator+ ( const Color& r1 , const Color& r2)
 {
     Color c(r1.r + r2.r , r1.g + r2.g  , r1.b + r2.b );
     return c ;
 }

 Color operator- ( const Color& r1 , const Color& r2)
 {
     Color c(r1.r - r2.r , r1.g - r2.g , r1.b - r2.b );
     return c ;
 }

 std::ostream& operator<<(std::ostream& os , const  Color& col)
 {
     os << (unsigned int )col.r << " " << (unsigned int ) col.g << " " << ( unsigned int ) col.b;
     return os ;
 }

bool operator==( const Color& c1 , const Color& c2)
{
    return ( c1.r == c2.r && c1.g == c2.g && c1.b == c2.b );
}

bool operator!=( const Color& c1 , const Color& c2)
{
    return ( c1.r != c2.r || c1.g != c2.g || c1.b != c2.b );
}
