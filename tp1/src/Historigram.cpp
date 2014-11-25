#include <iostream>
#include <stdexcept>
#include "../include/Image.hpp"
//mettre en suite le template

#include "../include/Historigram.h"


const ushort rajout = 20 ;
const ushort _width = 256 ;
const ushort _height = 200;
const uint lgTab = 256;

Historigram::Historigram(const Image<ubyte> & img):tabValeur(NULL),gMax(0)
{

 tabValeur = new uint [ lgTab ];
 for( ushort i = 0 ; i <= lgTab ; i++)
 {
    tabValeur[i] = 0 ;
 }

 for ( uint t = 0 ; t < uint (img.width * img.height) ; t++)
 {
     tabValeur [ img.array [t] ]++ ;

 }

 //on cherche la plus grande fréquence
 for( ushort g = 1 ; g <= lgTab ; g++)
 {
     if (tabValeur[g] > tabValeur[gMax])
     {
         gMax =  (ubyte) g;
     }
 }
    std::cout << "Construction de historigram " << std::endl;
}

Historigram::~Historigram()
{
    delete [] tabValeur;
    tabValeur = NULL ;
    std::cout << "Destruction  de historigram "<< std::endl;
}

Historigram::Historigram(const Historigram& original):tabValeur(NULL),gMax(original.gMax)
{
  for( uint i = 0 ; i <= lgTab ; i++)
  {
      tabValeur[i] = original.tabValeur[i] ;
  }
}

Image<ubyte> * Historigram::draw() const
{
     Image<ubyte> *imgTemp = new Image<ubyte> ( _width, _height + rajout );
     imgTemp->clear();

     for ( uint i = 0 ; i <= lgTab ; i++)
     {
         ushort hx =_height * (float(tabValeur[i]) / float (tabValeur[gMax]) );

       for( uint j = _height - 1  ; j > _height - hx ; j-- )
       {
         imgTemp->pixel(i,j) = 255 ;
       }

       for ( uint k = _height + rajout - 1   ; k > _height ; k--)
       {
           imgTemp->pixel(i,k) = i ;
       }
       //  imgTemp->fillRectangle(i, _height , 1 , rajout , i) ;

     }

    return imgTemp;
}
