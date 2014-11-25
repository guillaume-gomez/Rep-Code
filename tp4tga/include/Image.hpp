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
#include <iostream>
#include <jpeglib.h>
#include <setjmp.h>
#include <ctime>
#include <cstring>
#include "Palette.h"


/**
* @note : j'ai spécialisé certaines méthodes dans le template image ( c'est un peu facheux pour un template )
**/


//classe pour FloydSteinberg
//voir TD 3
class Weighting
{
  public:
   int x,y,w;
};

// construction d'une instance de la classe Weighting
const static Weighting FS [] =
{
    {+1,0,7},{-1,+1,3},{0,+1,5} ,{+1,+1,+1 } , {0,0,0}
};


/**
template qui permet de traiter différents type d'image
**/
template<typename T >
class Image
{
    /**
    @brief : "Image" laisse a "Histogram" la possibilité de
    voir ses attributs telle width , height et array
    **/
    friend class Histogram;

    private :
    /**
    @brief : largeur de l'image
    **/
	ushort width;
	/**
	@brief : hauteur de l'image
	**/
	ushort height;
	/**
	@brief : tableau de pixel de l'image
	**/
	T *array;

	public :
	/**
	@brief : le constructeur
	**/
    Image(ushort w, ushort h );
    /**
    @brief : le constructeur de copie
    **/
	Image(const Image<T>& original);
	/**
	@brief : vide les pixels de l'image
	**/
    void clear(T color=0);
    /**
    @brief : les accesseurs
    **/
	const T& pixel(ushort x, ushort y) const;
	T& pixel(ushort x, ushort y);
	/**
	@brief : les méthodes qui traitent les images
	**/
	Image<T>* simpleScale (ushort w , ushort h ) const;
	Image<T>* BilinearScale(ushort w , ushort h ) const;
	Image<T>* randomDirther() const;
	Image<T>* Threshold(ubyte threshold = 128) const;
    Image<T>* FloydSteinberg() const;
	/**
	@brief : méthodes qui crée des rectangle dans l'image
	**/
	void rectangle(ushort x,ushort y,ushort w,ushort h, T degre);
	void fillRectangle(ushort x,ushort y,ushort w,ushort h,T degre);
	/**
	@brief : méthodes qui écrit des images en différents formats
	**/
    void writePGM(std::ostream& f  , std::string& commentaire) const;
    void writePPM( std::ostream & f ,std::string& commentaire ) const;
    void writeJPEG(const char *fname , unsigned int quality) const ;
    //on enleve le const a cause de la méthode inverserTavCouleurs()
    void writeTGA(std::ostream& f  , std::string commentaire ="" , bool rle = true);
    void ArrayToRLE();
    void writeTGAten(std::ostream& f , std::string commentaire="" );

    /**
    @brief  : méthodes qui lis des images en différents formats
    **/
    static Image<T>* readPGM(std::istream& os);
    static Image<T>* readPPM(std::istream& os);
    static Image<Color> * readTGA ( std::istream& f);
    static Image<T>* readJpeg(char *filename);

    /**
    @brief : inversion du type de codage de couleurs pour le format TGA
    **/
    void inverserTabCouleurs();
    void inverserLigneTab();
    void convertirPaletteToArray( ubyte * listePixels , Color* palette_coul);
    void convertirPaletteToArray( ushort * listePixels , Color* palette_coul);


    Color* arrayInverse();

	~Image();
};

/**
*
* @brief : Constructeur du template Image
* @param : w largeur de l'image
* @param : h hauteur de l'image
*
**/
template<typename T >
 Image<T>::Image(ushort w, ushort h ) : width(w), height(h), array(0)
	{
        if ( width> 0 && height > 0)
	    {
            array = new T[width*height];
	    }
		else
		{
            throw std::runtime_error("Image::Image(ushort,ushort) : erreur dans les dimensions de l'image");
		}
    std::cout << "construction du template "<< std::endl;
	}

/**
*
* @brief : Constructeur de copie du template Image
* @param : Image que l'on souhaite copié
*
**/

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

/**
*
* @brief : Méthode qui applique à tout les pixels la couleurs donnée en paramètre
* @brief : color est la couleur unie de l'image
*
**/

    template<typename T >
	 void Image<T>::clear(T color)
	{
		for(uint i = 0; i<uint(width*height); i++)
		{
			array[i] = color;
		}
	}

/**
*
* @brief : Méthode accesseur du template image
* @param : Coordonnée X de l'image
* @param : Coordonnée Y de l'image
* @return : Un type de couleurs ( RGB ,RGBA , GRIS )
*
**/
    template<typename T >
	 const T& Image<T>::pixel(ushort x, ushort y) const
	{
		if(y*width + x < width * height)
			return array[y*width + x];
		else
			throw std::runtime_error("Image::pixel(ushort,ushort)const : coordonnées supérieures à la taille de l'image");
	}

/**
*
* @brief : Second accesseur du template image
* @param : Coordonnée X de l'image
* @param : Coordonnée Y de l'image
* @return : Un type de couleurs ( RGB ,RGBA , GRIS )
*
**/
    template<typename T >
	 T& Image<T>::pixel(ushort x, ushort y)
	{
        return array[y*width + x];
	}

/**
* @brief : Destructeur du template Image
**/
    template<typename T >
	 Image<T>::~Image()
	{
		delete[] array;
		array = NULL;
		std::cout << "destruction de template" << std::endl;
	}

/**
* @brief : Méthodes qui permet de crée un rectangle sur une image
* @param : position X du rectangle sur l'image
* @param : position Y du rectangle sur l'image
* @param : largeur Y du rectangle
* @param : hauteur H du rectangle
* @param : type de couleurs du rectangle
**/
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

/**
* @brief : Méthodes qui permet de crée un rectangle REMPLIS sur une image
* @param : position X du rectangle sur l'image
* @param : position Y du rectangle sur l'image
* @param : largeur Y du rectangle
* @param : hauteur H du rectangle
* @param : type de couleurs du rectangle
**/
    template<typename T >
	void Image<T>::fillRectangle(ushort x,ushort y,ushort w,ushort h,T degre)
	{
	    /**
	    on parcours l'image et on l'a remplie
	    **/
	       for(ushort j = y ; j < y + h  ; j++)
            {
               for(ushort i = x ; i < x + w  ; i++)
                {
                    pixel(i,j) = degre;
                }
            }
	}

/**
*
* @brief : Methodes données
*
**/
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

/**
*
* @brief : Méthodes pour le lecture d'une image sous format tga type 2
* @param : Liste de pixels de la palette (indice de la palette)
* @param : Liste de couleurs présent dans la palette
*
*/

    template<>
    void Image<Color>::convertirPaletteToArray( ushort * listePixels , Color* palette_coul)
    {
            for (unsigned int i= 0 ; i < (uint) width * height ; i++)
            {
                array[i] = palette_coul [ listePixels[ i ] ] ;
            }
    }

/**
*
* @brief : Surcharge de la méthode principale
* @param : Liste de pixels de la palette (indice de la palette)
* @param : Liste de couleurs présent dans la palette
* @note : j'ai essayé de mettre le premier parametre en template mais sans resultat , je me suis contenté de
* @see : void Image<Color>::convertirPaletteToArray( ushort * listePixels , Color* palette_coul)
*
*/
    template<>
    void Image<Color>::convertirPaletteToArray( ubyte * listePixels , Color* palette_coul)
    {
            for (unsigned int i= 0 ; i < (uint) width * height ; i++)
            {
                array[i] = palette_coul [ listePixels[ i ] ] ;
            }
    }


/**
*
* @brief : Ecrit une image du type PGM
* @param : flux d'ecriture
* @param : commentaire qui sera integré dans l'image
*
**/

    template<typename T >
	void Image<T>::writePGM( std::ostream & f  , std::string &commentaire ) const
	{
	    //ecriture
	    f << "P5\n"; //magic number pour PGM ASCII+Binaire
        f << "#" <<commentaire.c_str() <<"\n";
	    f << width << " " << height<<std::endl;
	    f << "255\n";
	    f.write((const char*)array, width * height);

	}


/**
*
* @brief : Ecrit une image du type PPM
* @param : flux d'ecriture
* @param : commentaire qui sera integré dans l'image
*
**/
	template<typename T >
	void Image<T>::writePPM( std::ostream & f , std::string &commentaire ) const
	{
	    //ecriture
        f << "P6\n"; //magic number pour PPM ASCII+Binaire
	    f << "#" <<commentaire.c_str() <<"\n";
	    f << width << " " << height<<std::endl;
	    f << "255\n";
	    f.write((const char*)array, width * height * sizeof(T));
	}

/**
*
* @param : Inverse la composante Rouge et Bleu pour l'ecriture d'un TGA
* @return : renvoit une copie de "array" mais inversé
*
**/
    template<typename T>
    Color* Image<T>::arrayInverse()
    {
        //on crée un tableau temporaire inversé
        Color *temp = new  Color [ width * height ];

        for ( ushort i = 0 ; i < ( width * height ) ; i++ )
        {
           temp[i].setColor(0,array[i].getColor(2));
           temp[i].setColor(1,array[i].getColor(1));
           temp[i].setColor(2,array[i].getColor(0));
        }
        return temp;
    }

/**
*
* @param : Inverse la composante Rouge et Bleu pour l'ecriture d'un TGA
*
**/
    template<>
    void Image<Color>::inverserTabCouleurs()
    {
        for ( uint i = 0 ; i < (uint) width * height ; i++)
        {
                uint temp ;
                //on recupere la composante rouge
                temp = array[ i ].getColor( 0 );
                // on place le bleu dans la composante dans le rouge
                uint bleu = array[ i ].getColor ( 2 );
                array[ i ].setColor ( 0 , bleu );

                array[ i ].setColor ( 2 , temp );
        }

    }

/**
*
* @brief : Inverse les lignes du tableau "array" dans le cas ou l'image TGA serais "à l'envers"
*
**/
    template<>
    void Image<Color>::inverserLigneTab()
    {

        for ( unsigned int i = 0 ; i < height / 2 ; i++)
        {

            for ( unsigned int j=0 ; j < width ; j++)
            {
                Color temp = pixel( j , i  );
                pixel( j , i ) = pixel( j ,  height - i - 1 );
                pixel ( j , height - i - 1 ) = temp ;
            }
        }
    }


/**
*
* Lecture de fichiers
*
**/


/**
*
* @brief : Ecrit une image TGA
* @param : un flux
* @param : un commentaire qui sera ajouté avec l'image
*
**/
	template<>
    void Image<Color>::writeTGA(std::ostream& f  , std::string commentaire , bool rle )
    {
        //longueur du commentaire
        f.put(commentaire.length()   );
        //abscence de palette
        f.put(0);
        //type de l'image
        if ( rle)
        {
            f.put(10);
        }
        else
        {
            f.put(2);
        }
        //comme nous n'avons pas de palette on met 5caracteres à 0 qui ne seront pas lues
        for(int i = 0 ; i < 5 ; i++)
            f.put(0);
        //origine X de l'image
        f.put(0);
        f.put(0);
        //origine Y de l'image
        f.put(0);
        f.put(0);
        //largeur de l'image
        f.write((const char *) &width,sizeof(width));
        //longueur de l'image
        f.write((const char *) &height,sizeof(height));
        //nombre de bits par pixel
        f.put(24);
        //
        f.put(32);
        //commentaire ...lié avec la valeur du premier bit du fichier
        if( commentaire.length() > 0 )
        {
            f.write((const char *) commentaire.c_str() , sizeof( char  ) * commentaire.length()   );
        }
        //on saute les info sur la pallette car abscente ici

        //les couleurs d'un TGA est en BGR
        //or dans Color elles sont stockées en RGB
        inverserTabCouleurs();

        //on ecrite ensuite le pixels de l'image
        if ( rle)
        {
                            //on ecrite ensuite le pixels de l'image
                    ubyte nbOccurenceEncodable = 0 ;
                    std::vector<Color> listeBitsEncodable ;
                    ubyte nbOccurenceNonEncodable = 0 ;

                    for ( unsigned int i=0; i < ( uint )width * height  ;)
                    {
                        unsigned int increment = i + 1 ;

                                //on test pour ne pas sortir du tableau
                                if ( increment > (uint) width * height )
                                {
                                    increment = i ;
                                }


                        if ( array[ i ]  == array [ increment ] )
                        {

                           nbOccurenceEncodable = 0 ;
                            while(  array [ i ] == array[ i + 1 ] && nbOccurenceEncodable < 127 )
                            {
                                nbOccurenceEncodable++;
                                i++;
                            }

                                nbOccurenceEncodable--;
                                nbOccurenceEncodable = nbOccurenceEncodable | ( 1 << 7);
                                f.put( nbOccurenceEncodable );
                                f.write((const char*) &array[ i ] , 3 ) ;
                        }
                        else
                        {

                            nbOccurenceNonEncodable = 0;
                            while( array [ i ] != array [ i + 1 ] &&  nbOccurenceNonEncodable < 127)
                            {
                                nbOccurenceNonEncodable++;
                                listeBitsEncodable.push_back( array[ i ] );
                                i++;
                            }

                            nbOccurenceNonEncodable--;
                            nbOccurenceNonEncodable = nbOccurenceNonEncodable | ( 0 << 7);

                            f.put( nbOccurenceNonEncodable );
                            for ( unsigned int w = 0 ; w < listeBitsEncodable.size() ; w++)
                            {
                               f.write((const char*) &listeBitsEncodable[w] , 3 ) ;
                            }
                            listeBitsEncodable.clear();

                        }
                    }
        }
        else
        {
             f.write((const char *) array, width * height *  3 );
        }
    }

/**
*
* @brief : Ecrit une image TGA de format 10
* @param : un flux
* @param : un commentaire qui sera ajouté avec l'image
*
*
**/
    template<>
    void Image<Color>::writeTGAten(std::ostream& f , std::string commentaire )
    {
         //longueur du commentaire
        f.put(commentaire.length()   );
        //abscence de palette
        f.put(0);
        //type de l'image
        f.put(10);
        //comme nous n'avons pas de palette on met 5caracteres à 0 qui ne seront pas lues
        for(int i = 0 ; i < 5 ; i++)
            f.put(0);
        //origine X de l'image
        f.put(0);
        f.put(0);
        //origine Y de l'image
        f.put(0);
        f.put(0);
        //largeur de l'image
        f.write((const char *) &width,sizeof(width));
        //longueur de l'image
        f.write((const char *) &height,sizeof(height));
        //nombre de bits par pixel
        f.put(24);
        //
        f.put(32);
        //commentaire ...lié avec la valeur du premier bit du fichier
        if( commentaire.length() > 0 )
        {
            f.write((const char *) commentaire.c_str() , sizeof( char  ) * commentaire.length()   );
        }
        //on saute les info sur la pallette car abscente ici

        //les couleurs d'un TGA est en BGR
        //or dans Color elles sont stockées en RGB
        inverserTabCouleurs();

        //on ecrite ensuite le pixels de l'image
        ubyte nbOccurenceEncodable = 0 ;
        std::vector<Color> listeBitsEncodable ;
        ubyte nbOccurenceNonEncodable = 0 ;

        for ( unsigned int i=0; i < ( uint )width * height  ;)
        {
            unsigned int increment = i + 1 ;

                    //on test pour ne pas sortir du tableau
                    if ( increment > (uint) width * height )
                    {
                        increment = i ;
                    }


            if ( array[ i ]  == array [ increment ] )
            {

               nbOccurenceEncodable = 0 ;
                while(  array [ i ] == array[ i + 1 ] && nbOccurenceEncodable < 127 )
                {
                    nbOccurenceEncodable++;
                    i++;
                }

                    nbOccurenceEncodable--;
                    nbOccurenceEncodable = nbOccurenceEncodable | ( 1 << 7);
                    f.put( nbOccurenceEncodable );
                    f.write((const char*) &array[ i ] , 3 ) ;
            }
            else
            {

                nbOccurenceNonEncodable = 0;
                while( array [ i ] != array [ i + 1 ] &&  nbOccurenceNonEncodable < 127)
                {
                    nbOccurenceNonEncodable++;
                    listeBitsEncodable.push_back( array[ i ] );
                    i++;
                }

                nbOccurenceNonEncodable--;
                nbOccurenceNonEncodable = nbOccurenceNonEncodable | ( 0 << 7);

                f.put( nbOccurenceNonEncodable );
                for ( unsigned int w = 0 ; w < listeBitsEncodable.size() ; w++)
                {
                   f.write((const char*) &listeBitsEncodable[w] , 3 ) ;
                }
                listeBitsEncodable.clear();

            }
        }
    }


/**
*
* @brief : Ecrit une image en format JPEG
* @param : nom du fichier de sortie
* @param : quality de la compression
*
**/
	template<typename T>
	void Image<T>::writeJPEG(const char *fname , unsigned int quality) const
	{
	    //creation de la structure qui gère les parametres de compression
	    struct jpeg_compress_struct cinfo;
	    // creation de la structure qui gère les erreurs
	    struct jpeg_error_mgr journalErreur;

	    //on créé un fichier a partir du nomFichier
	    FILE *fichier;

	    //initialisation des possibles erreurs
        cinfo.err = jpeg_std_error(&journalErreur);
        //on initialise les compressions JPEG
        jpeg_create_compress(&cinfo);

        if( (fichier = fopen(fname,"wb")) == NULL )
        {
            throw std::runtime_error("Impossible d'ouvrir les fichiers");
        }

        jpeg_stdio_dest(&cinfo, fichier);
        //on recupere les taille de la l'image
        cinfo.image_width = width;
        cinfo.image_height = height;

        cinfo.input_components = 3 ;
        cinfo.in_color_space = JCS_RGB;

        //on prepare la compression
        jpeg_set_defaults(&cinfo);

        jpeg_set_quality(&cinfo, quality , TRUE );

        jpeg_start_compress(&cinfo , TRUE);

        //tableau qui stocke les pointeurs de la ligne
	    JSAMPROW pointeur_colonne[1];

       for( ushort y=0 ; y < height ; y++ )
         {

            pointeur_colonne[0] = (JSAMPROW) &array[ y * width  ];
            (void) jpeg_write_scanlines(&cinfo, pointeur_colonne, 1);
        }

        //fin de compression
        jpeg_finish_compress(&cinfo);

        fclose(fichier);

        jpeg_destroy_compress(&cinfo);

	}

/**
*
* Fonction pour les lectures de fichiers
*
**/

template<typename T >
    Image<T>* Image<T>::readJpeg(char *filename)
    {
        //structure qui permet la lecture d'un jpeg
        struct jpeg_decompress_struct cinfo;
        //structure qui contient les possibles erreurs
        struct my_error_mgr journalErreur;
       // le fichier que l'on va créer
        FILE *fichier;

        //si on ne peut ouvrir le fichier
         if ((fichier = fopen(filename, "rb")) == NULL)
         {
          fprintf(stderr, "can't open %s\n", filename);
          throw std::runtime_error("Impossible de lire ce fichier ");
        }

        cinfo.err = jpeg_std_error(&journalErreur.pub);
        //code erreur que j'ai défini
        journalErreur.pub.error_exit = 4;

        if ( setjmp(journalErreur.setjmp_buffer))
        {
            jpeg_destroy_decompress(&cinfo);
            fclose(fichier);
            throw std::runtime_error("Impossible de lire ce fichier jpeg");
        }

        jpeg_create_decompress(&cinfo);
        jpeg_stdio_src(&cinfo,fichier);

        (void) jpeg_read_header(&cinfo, TRUE);

        (void) jpeg_start_decompress(&cinfo);

         int row_stride = cinfo.output_width * cinfo.output_components;

        Image<T>* temp = new Image<T>(cinfo.output_width , cinfo.output_height );

        JSAMPARRAY temp->array = (*cinfo.mem->alloc_sarray)
		((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);


    while (cinfo.output_scanline < cinfo.output_height)
   {
    (void) jpeg_read_scanlines(&cinfo, temp->array, 1);
    put_scanline_someplace(temp->array[0], row_stride);
   }

  (void) jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
  fclose(fichier);

  return temp;
}

/**
*
* @brief : Lecture d'une image de format PGM
* @param : flux d'entrée
*
**/
template<typename T >
    Image<T>* Image<T>::readPGM(std::istream& is)
	{
	    unsigned int _width =0 , _height=0 , nbGris = 255 ;
        std::string _magicKey ;

        if ( is)
        {
            is >> _magicKey;

            if ( !_magicKey.compare("P5\n"))
            {
                throw std::runtime_error(" Image<T>::readPGM(std::istream& is):Erreur dans le fichier type");
            }
            skip_line(is);
            skip_comments(is);
            is >> _width >> _height;
            skip_comments(is);
            is >> nbGris ;

            if ( nbGris != 255)
            {
               throw std::runtime_error(" Image<T>::readPGM(std::istream& is):Erreur composition incorrecte");
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


/**
*
* @brief : Lecture d'une image de format PPM
* @param : flux d'entrée
*
**/
	template <typename T >
      Image<T>* Image<T>::readPPM(std::istream& is)
     {
         unsigned int _width = 0 , _height= 0 , composition  ;
        std::string _magicKey ;

        if ( is)
        {
            is >> _magicKey;

            if(!_magicKey.compare("P6\n"))
            {
               throw std::runtime_error(" Image<T>::readPPM(std::istream& is):Erreur dans le fichier type");
            }

            skip_line(is);
            skip_comments(is);
            is >> _width >> _height;
            skip_comments(is);
            is >> composition ;

            if (  composition != 255)
            {
               throw std::runtime_error(" Image<T>::readPPM(std::istream& is):Erreur composition incorrecte");
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


/**
*
* @brief : Lecture d'une image de format TGA
* @note : lecture du format 1 , 2 , et  10
* @param : flux d'entrée
*
**/
    template<>
    Image<Color> * Image<Color>::readTGA( std::istream& f)
    {
         ushort longueurChaine = 0 ;
         int val;
         int palette = 0 ;

         /*
         * longueur du commentaire
         */
         longueurChaine = f.get();
        /*
        * présence ou non de palette
        */
        val = f.get();
        if ( val == 1)
        {
            palette = val ;
        }

        /*
        * type de l'image
        */
        val =  f.get();
        std::cout << val << std::endl;
        if ( val == 1)
        {
                    int val ;
                    /*
                    * Si présence de palette
                    * On doit donc préciser certains parametres
                    */

                    //on prepare les variables dans le cas de la pallette
                    ushort premierIndice = 0 ;
                    ushort nombreCouleur = 0 ;
                    ubyte nombreDeBits = 0 ;


                        f.read((char *)&premierIndice , sizeof(premierIndice));
                        f.read((char *)&nombreCouleur , sizeof(nombreCouleur));
                        nombreDeBits = f.get();

                        std::cout << premierIndice << " " << nombreCouleur << " " << nombreDeBits << std::endl;


                    /*
                    * origine X de l'image
                    */
                    val = f.get();
                    val = f.get();
                    /*
                    * origine Y de l'image
                    */
                    val = f.get();
                    val = f.get();


                    ushort _width = 0  ;
                    ushort _height = 0 ;

                    //largeur de l'image
                    f.read(( char *) &_width,sizeof(_width));
                    //longueur de l'image
                    f.read(( char *) &_height,sizeof(_height));

                    int typeIndicePalette = 0 ;
                    //type de l'indice dans le cas d'une pallette
                    typeIndicePalette = f.get();


                    int estEnvers = f.get();
                    //std::cout <<  val << std::endl;
                    if ( estEnvers != 32 && estEnvers != 0 )
                    {
                        throw std::runtime_error("Image<Color> * ColorImage::readTGA(istream& f) : Erreur dans la description de l'image");
                    }

                    //commentaire ...lié avec la valeur du premier bit du fichier
                    if ( longueurChaine > 0)
                    {
                        char * tab = new char [longueurChaine];
                        f.read( tab , sizeof( char  ) * longueurChaine );
                        delete [] tab ;
                    }

                        Color *contenuPalette  = new Color  [ nombreCouleur * nombreDeBits / 8 ];

                        //on lit la palette
                        f.read((char *) contenuPalette , nombreCouleur * nombreDeBits / 8   );

                         //on saute les info sur la pallette car abscente ici
                        //on ecrite ensuite le pixels de l'image
                        Image<Color> * temp = new Image<Color> ( _width , _height );

                        if ( estEnvers == 0 )
                        {
                            temp->inverserLigneTab();
                        }


                        if ( typeIndicePalette ==  8)
                        {
                            ubyte * contenuPixels = new ubyte [ _width * _height ];

                            f.read((char *) contenuPixels , _width * _height );

                            temp->convertirPaletteToArray(contenuPixels , contenuPalette);
                        }
                        else if ( typeIndicePalette == 16 )
                        {
                            ushort * contenuPixels = new ushort [ _width * _height ];

                            f.read((char *) contenuPixels , _width * _height * sizeof(ushort) );

                            temp->convertirPaletteToArray(contenuPixels , contenuPalette);
                        }

                    /*
                    *les couleurs d'un TGA est en BGR
                    *or dans Color elles sont stockées en RGB
                    */
                    temp->inverserTabCouleurs();

                    return temp;
        }
        else if ( val == 2)
        {
                    int val;
                    //comme nous n'avons pas de palette on met 5caracteres à 0 qui ne seront pas lues
                        for(int i = 0 ; i < 5 ; i++)
                        {
                            val = f.get();
                        }

                    /*
                    * origine X de l'image
                    */
                    val = f.get();
                    val = f.get();
                    /*
                    * origine Y de l'image
                    */
                    val = f.get();
                    val = f.get();


                    ushort _width = 0  ;
                    ushort _height = 0 ;

                    //largeur de l'image
                    f.read(( char *) &_width,sizeof(_width));
                    //longueur de l'image
                    f.read(( char *) &_height,sizeof(_height));

                    //nombre de bits par pixel pour le type 2
                    //ou type de l'indice dans le cas d'un pallette
                    val = f.get();
                    if ( val != 24 )
                    {
                        throw std::runtime_error("Image<Color> * ColorImage::readTGA(istream& f) : le nombre de bits par pixel est incorrect ... différent de 24");
                    }

                    int estEnvers = f.get();
                    //std::cout <<  val << std::endl;
                    if ( estEnvers != 32 && estEnvers != 0 )
                    {
                        throw std::runtime_error("Image<Color> * ColorImage::readTGA(istream& f) : Erreur dans la description de l'image");
                    }

                    //commentaire ...lié avec la valeur du premier bit du fichier
                    if ( longueurChaine > 0)
                    {
                        char * tab = new char [longueurChaine];
                        f.read( tab , sizeof( char  ) * longueurChaine );
                        delete [] tab ;
                    }

                    //on saute les info sur la pallette car abscente ici
                    //on ecrite ensuite le pixels de l'image
                    Image<Color> * temp = new Image<Color> ( _width , _height );
                    f.read((char *) temp->array, _width * _height *  3 );

                    if ( estEnvers == 0)
                    {
                        temp->inverserLigneTab();
                    }
                    /*
                    *les couleurs d'un TGA est en BGR
                    *or dans Color elles sont stockées en RGB
                    */
                    temp->inverserTabCouleurs();

                    return temp;

        }
        else if ( val == 10)
        {
                        int val;
                    //comme nous n'avons pas de palette on met 5caracteres à 0 qui ne seront pas lus
                        for(int i = 0 ; i < 5 ; i++)
                        {
                            val = f.get();
                        }

                    /*
                    * origine X de l'image
                    */
                    val = f.get();
                    val = f.get();
                    /*
                    * origine Y de l'image
                    */
                    val = f.get();
                    val = f.get();


                    ushort _width = 0  ;
                    ushort _height = 0 ;

                    //largeur de l'image
                    f.read(( char *) &_width,sizeof(_width));
                    //longueur de l'image
                    f.read(( char *) &_height,sizeof(_height));

                    //nombre de bits par pixel pour le type 2
                    //ou type de l'indice dans le cas d'un pallette
                    val = f.get();
                    if ( val != 24 )
                    {
                        throw std::runtime_error("Image<Color> * ColorImage::readTGA(istream& f) : le nombre de bits par pixel est incorrect ... différent de 24");
                    }

                    int estEnvers = f.get();
                    //std::cout <<  val << std::endl;
                    if ( estEnvers != 32 && estEnvers != 0 )
                    {
                        throw std::runtime_error("Image<Color> * ColorImage::readTGA(istream& f) : Erreur dans la description de l'image");
                    }

                    //commentaire ...lié avec la valeur du premier bit du fichier
                    if ( longueurChaine > 0)
                    {
                        char * tab = new char [longueurChaine];
                        f.read( tab , sizeof( char  ) * longueurChaine );
                        delete [] tab ;
                    }

                    //on saute les info sur la pallette car abscente ici
                    //on ecrite ensuite le pixels de l'image
                    Image<Color> * temp = new Image<Color> ( _width , _height );

                    if ( estEnvers == 0)
                    {

                        temp->inverserLigneTab();
                    }


                   for ( unsigned int increment = 0 ; increment < (uint) _width * _height ;  )
                    {
                         ubyte taille ;
                         ubyte r , g , b ;

                         taille = f.get();

                        //si on est face a un paquet compressé
                        if ( taille & 0x80)
                        {
                            b = f.get();
                            g = f.get();
                            r = f.get();

                            Color tempC(r,g,b);

                            taille = taille & 0x7F ;
                            //on ajoute un suite a l'algorithme de RLE
                            taille++;
                            //std::cout << ""

                            for ( unsigned int repetition = 0 ; repetition < taille ; repetition++)
                            {
                                temp->array [ increment++ ] = tempC ;
                            }
                        }
                        else
                        {
                            taille = taille & 0x7F ;
                            taille++;


                            for ( unsigned int repetition = 0 ; repetition < taille ; repetition++)
                            {
                                     b = f.get();
                                     g = f.get();
                                     r = f.get();
                                     Color tempC(r,g,b);
                                    temp->array [ increment++ ] = tempC ;
                            }
                        }

                    }

                    return temp;
        }
        else
        {
            std::runtime_error(" Image<Color> * readsTGA ( std::istream& f) : Erreur type de l'image inconu ");

        }

    }

/**
*
* @brief : Liste des algorithmes vues en TD
*
**/


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
