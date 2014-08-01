/*===============================
//Author:	carmazhao
//Data:		2011/1/3
//Functoin:	the basic objs
//			
//
================================*/
#ifndef GRAPH_OBJECT_HEAD_
#define GRAPH_OBJECT_HEAD_
#include "../Main/sysDef.h"
#include <string>

#define	MAX_NAME	256
class Object
{
public:
	Object(int_32   _x, 
			int_32  _y, 
			int_32  _depth ,
			int_32  _width ,
			int_32  _height);
	Object(const Object & _obj);
	virtual ~Object();

//==============get functions===========
	int_32			get_x()const;
	int_32			get_y()const;
	int_32			get_depth()const;
	int_32			get_width()const;
	int_32			get_height()const;
	std::string		get_name()const;
	RECT			get_rect();

//==============set functions===========
	void			set_x(const int_32 &);
	void			set_y(const int_32 &);
	void			set_depth(const int_32&);
	void			set_width(const int_32 &);
	void			set_height(const int_32 &);
	void			set_name(int_8*	_name);
protected:
//==============about the position===========
	int_32			m_x;		//x coordinate
	int_32			m_y;		//y coordinate
	int_32			m_depth;	//layer

	int_32			m_width;	//width of the object
	int_32			m_height;
	std::string		m_name;		//the name of object[default length is the max]
};
#endif