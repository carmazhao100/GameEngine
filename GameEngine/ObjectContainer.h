/*===============================
//Author:	carmazhao
//Data:		2011/1/3
//Functoin:	display
//			contain other objects
//
================================*/
#ifndef GRAPH_OBJECT_CONTAINER_HEAD_
#define GRAPH_OBJECT_CONTAINER_HEAD_
#include "../Main/sysDef.h"
#include "DisplayObject.h"
#include <vector>

class ObjectContainer:public DisplayObject
{
public:
	ObjectContainer(int_32   _x , 
		int_32 			_y , 
		int_32 			_depth,
		int_32 			_width,
		int_32 			_height);

	ObjectContainer(const ObjectContainer & _obj_container);
	virtual	~ObjectContainer();

	void			add_child(DisplayObject *);
	void			remove_child(DisplayObject *);
	virtual	void	draw(const int_32 & _std_x = 0 ,//begin pos_x
						 const int_32 & _std_y = 0); //begin pos_y
protected:
	std::vector<DisplayObject *>		m_display_queue;
};
#endif