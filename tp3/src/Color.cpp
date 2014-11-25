#include <iostream>
#include <stdexcept>
#include "../include/Color.h"

Color::Color(ubyte _r, ubyte _g, ubyte _b) : r(_r), g(_g), b(_b)
{}

Color::Color(const Color& original):r(original.r),g(original.g),b(original.b)
{}

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

 ubyte& Color::setColor(const int type , ubyte value)
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
