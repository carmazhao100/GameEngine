#include "DisplayObject.h"

DisplayObject::DisplayObject(int_32  _x,		\
							 int_32  _y,		\
							 int_32  _depth ,	\
							 int_32  _width ,	\
							 int_32  _height	\
							 ):Object(_x ,_y ,_depth , _width , _height)
{
	m_an_state = 0;
}

DisplayObject::DisplayObject(const DisplayObject & _dis_obj):Object(_dis_obj){
	std::map<int_32 , Animation *>					_an_table = _dis_obj.get_an_table();
	std::map<int_32 , Animation *>::iterator		_it ;
	Animation*										_animation = NULL;
//copy the animation information
	for (_it = _an_table.begin();
		_it != _an_table.end();
		_it++)
	{
		_animation = new Animation();
		*(_animation) = *(_it->second);
		m_animation_table[_it->first] = _animation;
		_animation = NULL;
	}
//copy state
	m_an_state = _dis_obj.get_an_state();
}

DisplayObject::~DisplayObject() {
	std::map<int_32 , Animation *>::iterator		_it ;

	for (_it = m_animation_table.begin();
		_it != m_animation_table.end();
		_it++)
	{
		delete (_it->second);
	}
}

void	DisplayObject::draw(const int_32 & _std_x , const int_32 & _std_y) {
	int_32				_x = m_x - _std_x;
	int_32				_y = m_y - _std_y;

	if(m_animation_table.size() == 0) {
		return;
	}

	glEnable(GL_BLEND);	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, get_animation()->get_frame());

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 1.0f);glVertex2d(_x,				_y);
	glTexCoord2f(1.0f, 1.0f);glVertex2d(_x + m_width,	_y);
	glTexCoord2f(1.0f, 0.0f);glVertex2d(_x + m_width,	_y + m_height);
	glTexCoord2f(0.0f, 0.0f);glVertex2d(_x,				_y + m_height);
	glEnd();

	glDisable(GL_BLEND);
}

Animation*	DisplayObject::get_animation() {
	if (m_animation_table.find(m_an_state) == m_animation_table.end())
	{
		return NULL;
	}
	return m_animation_table[m_an_state];
}

void DisplayObject::stop_animation() {
	if (m_animation_table.find(m_an_state) == m_animation_table.end())
	{
		return ;
	}
	m_animation_table[m_an_state]->stop();
}

void DisplayObject::play_animation() {
	if (m_animation_table.find(m_an_state) == m_animation_table.end())
	{
		return ;
	}
	m_animation_table[m_an_state]->play();
}

void DisplayObject::set_an_state(const uint_32 & _state) {
	m_an_state = _state;
}

void DisplayObject::add_animation(int_32 _id , Animation * _animation) {
	m_animation_table[_id] = _animation;
}

uint_32	DisplayObject::get_an_state() const {
	return m_an_state;
}

std::map<int_32 , Animation *> DisplayObject::get_an_table()const{
	return m_animation_table;
}