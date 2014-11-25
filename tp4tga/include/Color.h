#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

#include <iostream>

typedef unsigned short int ushort;
typedef unsigned char ubyte;
typedef unsigned int uint;

const int RED = 0 ;
const int GREEN = 1 ;
const int BLUE = 2 ;

class Color
{
    private :
    /**
    * les composantes des couleurs
    **/
	ubyte  r, g, b;

	public :
	/**
	* @brief : Constructeur de la classe Color
	**/
	Color(ubyte _r = 0, ubyte _g = 0, ubyte _b = 0);
	/**
	* @brief : Accesseur de la classe Color
	**/
	ubyte getColor(const int Type ) const;
    void setColor( int type , ubyte value);

    /**
	* @brief : Constructeur de copie de la classe Color
	**/
    Color(const Color& original);
    /**
	* @brief : Operateur d'affectation de la classe Color
	**/
    Color& operator=(const Color& source);

    /**
	* @brief : urcharge des operateurs  Color
	**/
    friend Color operator* ( double multiplicateur , const Color& r2);
    friend Color operator+ ( const Color& r1 , const Color& r2);
    friend Color operator- ( const Color& r1 , const Color& r2);
    friend std::ostream& operator<<(std::ostream& os ,const Color& r);
    friend bool operator==( const Color& c1 , const Color& c2);
    friend bool operator!=( const Color& c1 , const Color& c2);

    /**
	* @brief : Destructeur de la classe Color
	**/
    ~Color();

};
#endif // COLOR_H_INCLUDED


