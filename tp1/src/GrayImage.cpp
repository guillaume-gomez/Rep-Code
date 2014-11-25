#include <iostream>
#include <stdexcept>
#include "../include/GrayImage.h"


	 GrayImage::GrayImage(ushort w, ushort h) : width(w), height(h), array(NULL)
	{
	    if ( width> 0 && height > 0)
            array = new ubyte[width*height];
		else
            throw std::runtime_error("GrayImage::GrayImage(ushort,ushort) : erreur dans les dimensions de l'image");
       std::cout << "construction de GrayImage "<<std::endl;

	}

	 GrayImage::GrayImage(const GrayImage& original) : width(original.width), height(original.height), array(NULL)
	{
		array = new ubyte[width*height];
		for(uint i = 0; i<uint(width*height); i++)
		{
			array[i] = original.array[i];
		}
	}

	 void GrayImage::clear()
	{
		for(uint i = 0; i<uint(width*height); i++)
		{
			array[i] = 0;
		}
	}

	 ubyte GrayImage::pixel(ushort x, ushort y) const
	{
		if(y*width + x < width * height)
			return array[y*width + x ];
		else
            std::cout << width * height -  y*width + x <<std::endl;
			throw std::runtime_error("GrayImage::pixel(ushort,ushort)const : coordonnées supérieures à la taille de l'image");
	}

	 ubyte& GrayImage::pixel(ushort x, ushort y)
	{
		 if(y*width + x < width * height)
		 {
		     std::cout << "   "<<y*width + x << std::endl;
			return array[y*width + x ];
		 }
		 else
            std::cout <<" coordonnée erreur  "<< x <<" " << y  <<std::endl;
			throw std::runtime_error("ubyte & GrayImage::pixel(ushort,ushort) : coordonnées supérieures à la taille de l'image");


	}

	  GrayImage::~GrayImage()
	{
		delete[] array;
		array = NULL;
		std::cout << " destruction de GrayImage" << std::endl;
	}

	void GrayImage::rectangle(ushort x,ushort y,ushort w,ushort h,ubyte degre)
	{
	    //on crée la ligne superieur et inférieur
	    for(ushort i = x ; i < x + w - 1 ;i++)
	    {
	        std::cout << "lignes "<<std::endl;
	        pixel(i,y)   = degre;
	        pixel(i,y+h) = degre;
	    }

	    //on crée les cotés
	    for(ushort j = y ; j < y + h - 1  ; j++)
	    {
	        std::cout << "test fionctipn"<<std::endl;
	        pixel(x,j)   = degre;
            pixel(x+w,j) = degre;
	    }

	}

	void GrayImage::fillRectangle(ushort x,ushort y,ushort w,ushort h,ubyte degre)
	{
	    std::cout << x << " " << y << std::endl;
	       for(ushort j = y ; j <= y + h - 1 ; j++)
            {
               for(ushort i = x ; i <= x + w - 1 ; i++)
                {
                    pixel(i,j) = degre;
                }
            }
	}


	void GrayImage::writePGM( std::ostream & f ) const
	{
	    //ecriture
	    f << "P5\n"; //magic number pour PGM ASCII+Binaire
	    f << "# CREATOR: The GIMP's PNM Filter Version 1.0\n";
	    f << width <<' '<< height<<std::endl;
	    f << "255\n";
	    ubyte tmp[4];
	    //poids faibles | poids forts
	    tmp[0] = width%256;  tmp[1] = width >> 8;
	    tmp[2] = height%256; tmp[3] = height >> 8;
	    f.write((const char*) tmp, 4);
	    f.write((const char*)array,width*height);
	}

//Fonction pour les lectures de fichiers

    static void skip_line(std::istream& is)
    {
     char c;
     do {
      is.get(c);  // Lire un caractère
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


    GrayImage* GrayImage::readFormat(std::istream& is)
	{
        unsigned int _width =0 , _height=0 , nbGris= 255;
        GrayImage * temp ;

        if ( is)
        {
            skip_line(is);
            skip_comments(is);
            is >> _width >> _height >> nbGris ;
              const unsigned int MAX = _width*_height ;

            //on lit ensuite les caracteres par blocs
            //on crée l'insance de classe
            temp = new GrayImage (_width,_height);
            temp->clear();
            is.read((char*) temp->array, MAX);


        }
        else
            throw std::runtime_error(" GrayImage::readFormat(std::istream& is): impossible d'ouvrir le fichier");

	    return temp;

	}


    void GrayImage::readFormats(std::istream& is)
    {
        unsigned int _width =0 , _height=0 , nbGris= 255;
         if ( is)
        {
            skip_line(is);
            skip_comments(is);
            is >> _width >> _height >> nbGris ;
            const unsigned int MAX = _width*_height ;

            //on remplace les valeurs
            width = _width ;
            height = _height;
            //on lit ensuite les caracteres par blocs
            is.read((char*) array, MAX);
        }
        else
            throw std::runtime_error(" GrayImage::readFormat(std::istream& is): impossible d'ouvrir le fichier");


    }
