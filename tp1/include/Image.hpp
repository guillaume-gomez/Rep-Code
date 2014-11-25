#ifndef IMAGE_H
#define IMAGE_H

typedef unsigned short int ushort;
typedef unsigned char ubyte;
typedef unsigned int uint;

#include <iostream>
#include <ostream>
#include <fstream>

template<typename T >
class Image
{
    friend class Historigram;

    private :
	ushort width;
	ushort height;
	T *array;

	public :
    Image(ushort w, ushort h);
	Image(const Image<T>& original);
    void clear();
	T pixel(ushort x, ushort y) const;
	T& pixel(ushort x, ushort y);
	void rectangle(ushort x,ushort y,ushort w,ushort h, T degre);
	void fillRectangle(ushort x,ushort y,ushort w,ushort h,T degre);
    void writePGM(std::ostream& f ) const;
    static Image<T>* readFormat(std::istream& os);
	~Image();
};

template<typename T >
 Image<T>::Image(ushort w, ushort h) : width(w), height(h), array(NULL)
	{
	    if ( width> 0 && height > 0)
            array = new T[width*height];
		else
            throw std::runtime_error("Image::Image(ushort,ushort) : erreur dans les dimensions de l'image");


	}

template<typename T >
	 Image<T>::Image(const Image& original) : width(original.width), height(original.height), array(NULL)
	{
		array = new T[width*height];
		for(uint i = 0; i<uint(width*height); i++)
		{
			array[i] = original.array[i];
		}
	}

template<typename T >
	 void Image<T>::clear()
	{
		for(uint i = 0; i<uint(width*height); i++)
		{
			array[i] = 0;
		}
	}

template<typename T >
	 T Image<T>::pixel(ushort x, ushort y) const
	{
		if(y*width + x < width * height)
			return array[y*width + x];
		else
			throw std::runtime_error("Image::pixel(ushort,ushort)const : coordonnées supérieures à la taille de l'image");
	}

template<typename T >
	 T& Image<T>::pixel(ushort x, ushort y)
	{
        return array[y*width + x];
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
	    f << "#CREATOR: The GIMP's PNM Filter Version 1.0\n";
	    f << width << " " << height<<std::endl;
	    f << "255\n";
	    f.write((const char*)array,width*height);

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
    Image<T>* Image<T>::readFormat(std::istream& is)
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
               throw std::runtime_error(" GrayImage::readFormat(std::istream& is):Erreur dans le fichier type ou composition incorrecte");
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
            throw std::runtime_error(" GrayImage::readFormat(std::istream& is): impossible d'ouvrir le fichier");

        return NULL;
	}


#endif // IMAGE_H
