#include "ObjectContainer.h"

ObjectContainer::ObjectContainer(int_32  _x,		\
								int_32  _y,		\
								int_32  _depth ,	\
								int_32  _width ,	\
								int_32  _height	\
								):DisplayObject(_x ,_y ,_depth , _width , _height)
{
}

ObjectContainer::ObjectContainer(const ObjectContainer & _obj_container):DisplayObject(_obj_container){

}

ObjectContainer::~ObjectContainer() {
	
}

void ObjectContainer::add_child(DisplayObject * _dobj) {
	m_display_queue.push_back(_dobj);
}

void ObjectContainer::remove_child(DisplayObject * _dobj) {
	uint_32			i = 0;

	for (;i < m_display_queue.size();i++)
	{
		if(m_display_queue[i] == _dobj) {
			m_display_queue.erase(m_display_queue.begin() + i);
		}
	}
}

void ObjectContainer::draw(const int_32 & _std_x , const int_32 & _std_y) {
	uint_32				i = 0;
	int_32				_x = m_x - _std_x;
	int_32				_y = m_y - _std_y;
	
	//first draw the object itself by the standard coordinate
	DisplayObject::draw(_std_x , _std_y);

	//draw the contains 
	for (;i < m_display_queue.size();i++)
	{
		m_display_queue[i]->draw(_x , _y);
	}
}