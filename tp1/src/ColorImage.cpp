#include <iostream>
#include <stdexcept>
#include "../include/ColorImage.h"

	 ColorImage::ColorImage(ushort w, ushort h) : width(w), height(h), array(NULL)
	{
		array = new Color[width*height];
	}


	 ColorImage::ColorImage(const ColorImage& original) : width(original.width), height(original.height), array(NULL)
	{
		array = new Color[width*height];
		for(uint i = 0; i<uint(width*height); i++)
		{
			array[i] = original.array[i];
		}
	}

	 void ColorImage::clear()
	{
		for(uint i = 0; i<uint(width*height); i++)
		{
			array[i] = 0;
		}
	}

	Color ColorImage::pixel(ushort x, ushort y) const
	{
		if(x<width && y<height)
			return array[y*width + x];
		else
			throw std::runtime_error("ColorImage::pixel(ushort,ushort)const : coordonnées supérieures à la taille de l'image");
	}

	 Color& ColorImage::pixel(ushort x, ushort y)
	{
		return array[y*width + x];
	}

	 ColorImage::~ColorImage()
	{
		delete[] array;
		array = NULL;
	}


