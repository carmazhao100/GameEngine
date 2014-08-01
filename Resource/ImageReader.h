/*===============================
//Author:	carmazhao
//Data:		2011/17
//Functoin:	read the pics and save
//			it
//			
================================*/
#ifndef IMAGE_READER_HEAD_
#define IMAGE_READER_HEAD_
#include "../Main/sysDef.h"
#include "FreeImage.h"
	
class ImageReader;
class FMbitmap 
{
public:
	uint_8*		m_bits;
	int_32		m_width;
	int_32		m_height;
	int_32		m_format;
};
 
class ImageReader
{
	DEFINE_SINGLE_MODEL(ImageReader)
public:
	enum color_format{
		RGB_IMG = GL_RGB,
		RGBA_IMG = GL_RGBA
	};
	~ImageReader();

	FMbitmap	read_image(int_8 * _file_name = NULL , color_format _format = RGBA_IMG);
	void		release_image();

private:
	FIBITMAP * m_dib;
	ImageReader();
};
#endif