/*===============================
//Author:	carmazhao
//Data:		2011/2/7
//Functoin:	base component ui to 
//			deal event 
//
================================*/
#ifndef BASE_UI_HEAD_
#define BASE_UI_HEAD_
#include "../Main/sysDef.h"
#include "EventListener.h"

class BaseUi:public EventListener
{
public:
	BaseUi(int_32   _x , 
		int_32 			_y  , 
		int_32 			_depth  ,
		int_32 			_width ,
		int_32 			_height);
	~BaseUi();
private:
};
#endif