#ifndef IMAGE_H
#define IMAGE_H

typedef unsigned short int ushort;
typedef unsigned char ubyte;
typedef unsigned int uint;

#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Color.h"

//class pour FloydSteinberg
class Weighting
{
  public:
   int x,y,w;
};

const static Weighting FS [] =
{
    {+1,0,7},{-1,+1,3},{0,+1,5} ,{+1,+1,+1 } , {0,0,0}
};



template<typename T >
class Image
{
    friend class Histogram;

    private :
	ushort width;
	ushort height;
	T *array;

	public :
    Image(ushort w, ushort h );
	Image(const Image<T>& original);
    void clear(T color=0);
	const T& pixel(ushort x, ushort y) const;
	T& pixel(ushort x, ushort y);
	Image<T>* simpleScale (ushort w , ushort h ) const;
	Image<T>* BilinearScale(ushort w , ushort h ) const;
	Image<T>* randomDirther() const;
	Image<T>* Threshold(ubyte threshold = 128) const;
	void rectangle(ushort x,ushort y,ushort w,ushort h, T degre);
	void fillRectangle(ushort x,ushort y,ushort w,ushort h,T degre);
    void writePGM(std::ostream& f ) const;
    void writePPM( std::ostream & f ) const;
    void writePPMAscii( std::ostream &f) const;
    static Image<T>* readPGM(std::istream& os);
    static Image<T>* readPPM(std::istream& os);
    Image<T>* FloydSteinberg() const;
	~Image();
};

template<typename T >
 Image<T>::Image(ushort w, ushort h ) : width(w), height(h), array(0)
	{
            std::cout << "Image.cpp : " << __LINE__ << std::endl;
	    if ( width> 0 && height > 0)
	    {
            std::cout << "Image.cpp : " << __LINE__ << std::endl;
            array = new T[width*height];
            std::cout << "Image.cpp : " << __LINE__ << std::endl;
	    }
		else
		{
            std::cout << "Image.cpp : " << __LINE__ << std::endl;
            throw std::runtime_error("Image::Image(ushort,ushort) : erreur dans les dimensions de l'image");
            std::cout << "Image.cpp : " << __LINE__ << std::endl;
		}
    std::cout << "construction du template "<< std::endl;

	}

template<typename T >
	 Image<T>::Image(const Image& original) : width(original.width), height(original.height), array(NULL)
	{
		array = new T[width*height];
		for(uint i = 0; i<uint(width*height); i++)
		{
			array[i] = original.array[i];
		}
		std::cout << "constructeur de copie de template "<<std::endl;
	}

template<typename T >
	 void Image<T>::clear(T color)
	{
		for(uint i = 0; i<uint(width*height); i++)
		{
			array[i] = color;
		}
	}

template<typename T >
	 const T& Image<T>::pixel(ushort x, ushort y) const
	{
		if(y*width + x < width * height)
			return array[y*width + x];
		else
			throw std::runtime_error("Image::pixel(ushort,ushort)const : coordonnées supérieures à la taille de l'image");
	}

template<typename T >
	 T& Image<T>::pixel(ushort x, ushort y)
	{
	    if(y*width + x < width * height)
            return array[y*width + x];
        else
            throw std::runtime_error("&Image::pixel(ushort,ushort)const : coordonnées supérieures à la taille de l'image");
	}

template<typename T >
	 Image<T>::~Image()
	{
		delete[] array;
		array = NULL;
		std::cout << "destruction de template" << std::endl;
	}

template<typename T >
	void Image<T>::rectangle(ushort x,ushort y,ushort w,ushort h,T degre)
	{

	    //on crée la ligne superieur et inférieur
	    for(ushort i = x ; i <= x + w  ;i++)
	    {
	        pixel(i,y)   = degre;
	        pixel(i,y+h) = degre;
	    }

	    //on crée les cotés
	    for(ushort j = y ; j < y + h   ; j++)
	    {
	        pixel(x,j)   = degre;
            pixel(x+w,j) = degre;
	    }

	}

template<typename T >
	void Image<T>::fillRectangle(ushort x,ushort y,ushort w,ushort h,T degre)
	{
	       for(ushort j = y ; j < y + h  ; j++)
            {
               for(ushort i = x ; i < x + w  ; i++)
                {
                    pixel(i,j) = degre;
                }
            }
	}

template<typename T >
	void Image<T>::writePGM( std::ostream & f ) const
	{
	    //ecriture
	    f << "P5\n"; //magic number pour PGM ASCII+Binaire
	    f << "#CREATOR:Guillaume Gomez \n";
	    f << width << " " << height<<std::endl;
	    f << "255\n";
	    f.write((const char*)array,width*height);

	}

	template<typename T >
	void Image<T>::writePPM( std::ostream & f ) const
	{
	    //ecriture
        f << "P6\n"; //magic number pour PPM ASCII+Binaire
	    f << "#CREATOR:Guillaume Gomez\n";
	    f << width << " " << height<<std::endl;
	    f << "255\n";
	    f.write((const char*)array,width*height*sizeof(T));

	}

	template<>
	void Image<Color>::writePPMAscii( std::ostream &f) const
	{
	    //ecriture
        f << "P3\n"; //magic number pour PGM ASCII+Binaire
	    f << "#CREATOR:Guillaume Gomez \n";
	    f << width << " " << height<<std::endl;
	    f << "255\n";
	    for( ushort i = 0 ; i < height ; i++)
	    {
            for( ushort j = 0 ; j < width ; j++ )
            {
	            Color temp;
	            temp = pixel(j,i);
	           // f << array[i*width + j].getColor(0) << " " << 0 << " " << 123 <<char(9);
	            f << temp.getColor(0) << " " << temp.getColor(1) << " " << temp.getColor(2) <<char(9);

            }
             f << "\n";
	    }

	}

//Fonction pour les lectures de fichiers

    static void skip_line(std::istream& is)
    {
     char c;
     do {
      is.get(c);      // Lire un caractère
     } while(c!='\n'); // tant qu'on n'atteint pas la fin de ligne.
    }

    // skip_comments(is) utilise la fonction précédente pour sauter zéro, une ou plusieurs lignes
    // de commentaires débutées par '#' et allant jusqu'à '\n'.
    static void skip_comments(std::istream& is)
    {
     char c;
     is.get(c);       // Lire un caractère.
     while(c=='#')    // Tant que c'est un '#'.
      {
       skip_line(is); // On élimine les caractères jusqu'à la fin de ligne,
       is.get(c);     // Et on lit un nouveau caractère.
      }
     is.putback(c);   // On remet le caractère lu puisqu'il n'est pas un '#'.
    }

template<typename T >
    Image<T>* Image<T>::readPGM(std::istream& is)
	{
	    unsigned int _width =0 , _height=0 , nbGris= 255 ;
        std::string _magicKey ;

        if ( is)
        {
            is >> _magicKey;
            skip_line(is);
            skip_comments(is);
            is >> _width >> _height;
            skip_comments(is);
            is >> nbGris ;

            if ( !_magicKey.compare("P5\n") && nbGris != 255)
            {
               throw std::runtime_error(" Image<T>::readPGM(std::istream& is):Erreur dans le fichier type ou composition incorrecte");
            }

            //on crée un variable pour attrapper le /n
            char c ;
            is.get(c);

            //on lit ensuite les caracteres par blocs
            //on crée l'instance de classe
            Image<T> * temp = new Image<T> (_width,_height);
            is.read((char*) temp->array, _width * _height );

            return temp;

        }
        else
            throw std::runtime_error(" Image<T>::readPGM(std::istream& is): impossible d'ouvrir le fichier");

        return NULL;
	}

	template <typename T >
      Image<T>* Image<T>::readPPM(std::istream& is)
     {
         unsigned int _width = 0 , _height= 0 , composition  ;
        std::string _magicKey ;

        if ( is)
        {
            is >> _magicKey;
            skip_line(is);
            skip_comments(is);
            is >> _width >> _height;
            skip_comments(is);
            is >> composition ;

            if ( !_magicKey.compare("P6\n") && composition != 255)
            {
               throw std::runtime_error(" Image<T>::readPPM(std::istream& is):Erreur dans le fichier type ou composition incorrecte");
            }

            //on crée un variable pour attrapper le /n
            char c ;
            is.get(c);

            //on lit ensuite les caracteres par blocs
            //on crée l'instance de classe
            Image<T> * temp = new Image<T> (_width,_height);
            is.read((char*) temp->array, _width * _height * sizeof(T) );

            return temp;

        }
        else
            throw std::runtime_error(" Image<T>::readPPM(std::istream& is): impossible d'ouvrir le fichier");

        return NULL;
     }



	template<typename T >
	Image<T>* Image<T>::simpleScale(ushort w , ushort h ) const
    {
        Image<T>* Derivee = new Image<T> ( w , h);

            for( ushort yprime = 0 ; yprime < h ; yprime++ )
            {
                for ( ushort xprime = 0 ; xprime < w ; xprime++)
                {
                    double x =  xprime*width/w  ;
                    double y =  yprime*height/h  ;
                    Derivee->pixel(xprime,yprime) = pixel(x,y);
                }
            }
            return Derivee;
    }


template<typename T >
	Image<T>* Image<T>::BilinearScale(ushort w , ushort h ) const
    {
        Image<T>* Derivee = new Image<T> ( w , h );

            for( ushort yprime = 0 ; yprime < h ; yprime++ )
            {
                for ( ushort xprime = 0 ; xprime < w ; xprime++)
                {
                    double x =   double(xprime*width)/w  ;
                    double y =   double(yprime*height)/h  ;

                    ushort i = ushort (x);
                    ushort j = ushort (y);

                    //on prend les points suivants
                    ushort ip1 = (i+1 >= width ? i : i+1);
                    ushort jp1 = (j+1 >= height ? j : j+1);

                    T p1 = pixel(i,j);
                    T p2 = pixel(ip1,j);

                    T p3 = pixel(i,jp1);
                    T p4 = pixel(ip1 , jp1);

                    double lambda = x - i ;
                    double m_u = y - j ;

                    Derivee->pixel(xprime,yprime) =
                    ( 1 - lambda)*((1-m_u)*p1 + m_u*p3)
                      +    lambda*((1-m_u)*p2 + m_u*p4);

                }
            }
        return Derivee;
    }

template<typename T >
Image<T>* Image<T>::Threshold(ubyte threshold ) const
{
    Image<T>* iprime = new Image<T>(width , height);

        for(uint t=0 ; t < width*height ;t++)
        {
            iprime->array[t] = ( (ubyte) array[t] < threshold ? 0 : 1 );
        }

        return iprime;
}


template<typename T >
Image<T>* Image<T>::randomDirther() const
{
    Image<T>* iprime = new Image<T>(width , height);
    srand(time(0));
    ubyte aleatoire = rand()% 256;

        for(uint t=0 ; t < width*height ;t++)
        {
            iprime->array[t] = ( (ubyte) array[t] < aleatoire ? 0 : 1 );
        }

        return iprime;
}


template<typename T >
Image<T>* Image<T>::FloydSteinberg() const
{
    Image<T> * temp = new Image<T> ( *this);

    for( ushort y=0 ; y < height ; y++)
    {

        for(ushort x=0;x < width ; x++)
        {
            temp->pixel(x,y) = ( pixel(x,y) >  128 ? 255 : 0);
            int erreur = pixel(x,y) - temp->pixel(x,y);

            int somme = 0 ;

            for( int i = 0 ; FS[i].w != 0 ; i++)
            {
                 if ( x - FS[i].x >= 0 && x+ FS[i].x < width && y + FS[i].y < height)
                 {
                     somme += FS[i].w ;
                 }
            }

            for( int i = 0 ; FS[i].w != 0 ; i++ )
            {
                 if ( x - FS[i].x >= 0 && x+ FS[i].x < width && y + FS[i].y < height)
                 {
                     temp->pixel(FS[i].x + x , FS[i].y + y) += erreur * FS[i].w / somme;
                 }
            }
        }
    }
}

/*

pour generaliser la méthode FloydSteinberg
il faut a la construction du pointeur temp

const Weighting * mask ;
switch(param pour connaitre le type )
{

    case : FloydSteinberg :
        mask = FS ;
    break;
    case : Stuki :
        mask = AUTRE TYPE DE TAB CONST STATIC
    break;
    ...

}
*/
#endif // IMAGE_H
