#ifndef PALETTE_H
#define PALETTE_H

#include "Color.h"

#include <iostream>
#include <vector>


/**
*@brief : Construction d'une classe palette
*@note : elle ne respecte pas l'objectif de l'encapsulation des attributs pour des raisons d'acces
*        lors de la methode writeTGA
**/
class Palette
{
    public:
    /**
	* @brief : Constructeur de la classe Palette
	**/
        Palette();
    /**
	* @brief : Destructeur de la classe Palette
	**/
        virtual ~Palette();
    /**
	* @brief : Constructeur de copie de la classe Palette
	**/
        Palette(const Palette& original);
    /**
	* @brief : Operateur egal de la classe Palette
	**/
        Palette& operator=(const Palette& source );
    /**
	* @brief : Accesseur de la classe Palette
	**/
        inline int getNbCouleurs () const { return tabCouleurs.size();};
    /**
	* @brief :  Deuxieme Accesseur de la classe Palette
	**/
        inline void ajouterCouleurs ( Color& color){tabCouleurs.push_back(color);};
    /**
	* @brief : Attributs de la classe Palette
	**/
        std::vector<Color> tabCouleurs;

};

#endif // PALETTE_H
