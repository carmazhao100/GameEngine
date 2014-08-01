#include "ImageReader.h"

IMPLEMENT_SINGLE_MODEL(ImageReader)

ImageReader::ImageReader() {
	#ifdef FREEIMAGE_LIB
		FreeImage_Initialise();
	#endif
}

ImageReader::~ImageReader(){
	#ifdef FREEIMAGE_LIB
		FreeImage_DeInitialise();
	#endif
}

FMbitmap	ImageReader::read_image(int_8 * _file_name, color_format _format){
	//image format
	FREE_IMAGE_FORMAT			fif = FIF_UNKNOWN;
	FMbitmap					_fmbmp;
	uint_8*						bits(0);
	int_32						width(0);
	int_32						height(0);
	int_32						sum(0); 

	memset(&_fmbmp , 0 , sizeof(_fmbmp));
	m_dib = 0;

	if(_file_name == NULL) {
		return _fmbmp;
	}
/************************READ DATA****************************/
	fif = FreeImage_GetFileType(_file_name, 0);
	
	if(fif == FIF_UNKNOWN) 
		fif = FreeImage_GetFIFFromFilename(_file_name);
	if(fif == FIF_UNKNOWN)
		return _fmbmp;

	if(FreeImage_FIFSupportsReading(fif))
		m_dib = FreeImage_Load(fif, _file_name);
	if(!m_dib)
		return _fmbmp;

/************************DEAL DATA****************************/
	bits = FreeImage_GetBits(m_dib);
	if(bits == NULL) {
		return _fmbmp;
	}
	width = FreeImage_GetWidth(m_dib);
	height = FreeImage_GetHeight(m_dib);

	// transform from bgr to rgb
	BYTE  tmp;
	int i = 0;
	if (_format == RGB_IMG) {
		sum = width*height*3;
		for (i = 0;i<sum;)
		{
			tmp = bits[i];
			bits[i] = bits[i+2];
			bits[i+2] = tmp;
			i += 3;
		}
	}else if (_format == GL_RGBA) {
		sum = width*height*4;
		for (i = 0;i<sum;)
		{
			tmp = bits[i];
			bits[i] = bits[i+2];
			bits[i+2] = tmp;
			i += 4;
		}
	}else{
		return _fmbmp;
	}
	//construct the bmp
	_fmbmp.m_bits = bits;
	_fmbmp.m_height = height;
	_fmbmp.m_width = width;
	_fmbmp.m_format = _format;

	return _fmbmp;
}

void	ImageReader::release_image(){
	FreeImage_Unload(m_dib);
}