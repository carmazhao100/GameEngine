#include "Object.h"

Object::Object(int_32   _x, 
			   int_32   _y, 
			   int_32  _depth ,
			   int_32  _width ,
			   int_32  _height){
   m_x = _x;
   m_y = _y;
   m_depth = _depth;
   m_width = _width;
   m_height = _height;
}
Object::Object(const Object & _obj) {
	m_x = _obj.get_x();
	m_y = _obj.get_y();
	m_width = _obj.get_width();
	m_height = _obj.get_height();
	m_depth = _obj.get_depth();
}
Object::~Object(){

}

//==============get functions===========
int_32	Object::get_x() const{
	return m_x;
}

int_32	Object::get_y() const{
	return m_y;
}

int_32	Object::get_width() const{
	return m_width;
}

int_32	Object::get_height() const{
	return m_height;
}

int_32	Object::get_depth() const{
	return m_depth;
}

std::string	Object::get_name() const{
	return m_name;
}

RECT	Object::get_rect(){
	RECT		_rect;

	_rect.left = m_x;
	_rect.top = m_y;
	_rect.right = m_x + m_width;
	_rect.bottom = m_y + m_height;

	return _rect;
}
//==============set functions===========

void	Object::set_x(const int_32 & _x) {
	m_x = _x;
}

void	Object::set_y(const int_32 & _y) {
	m_y = _y;
}

void	Object::set_depth(const int_32& _depth) {
	m_depth = _depth;
}
void	Object::set_width(const int_32 & _width) {
	m_width = _width;
}

void	Object::set_height(const int_32 & _height) {
	m_height = _height;
}

void	Object::set_name(int_8 *_name) {
	m_name = _name;	
}