#ifndef GRAYIMAGE_H_INCLUDED
#define GRAYIMAGE_H_INCLUDED


typedef unsigned short int ushort;
typedef unsigned char ubyte;
typedef unsigned int uint;

class GrayImage
{
    friend class Historigram;

	private :
	ushort width;
	ushort height;
	ubyte *array;

	public :
    GrayImage(ushort w, ushort h);
	GrayImage(const GrayImage& original);
    void clear();
	ubyte pixel(ushort x, ushort y) const;
	ubyte& pixel(ushort x, ushort y);
	void rectangle(ushort x,ushort y,ushort w,ushort h,ubyte degre);
	void fillRectangle(ushort x,ushort y,ushort w,ushort h,ubyte degre);
    void writePGM(std::ostream& f ) const;
    static GrayImage* readFormat(std::istream& is);
    void readFormats(std::istream& is);
	virtual ~GrayImage();

};

#endif // GRAYIMAGE_H_INCLUDED
