#include "EventListener.h"

EventListener::EventListener(int_32  _x,		\
							 int_32  _y,		\
							 int_32  _depth ,	\
							 int_32  _width ,	\
							 int_32  _height	\
							 ):ObjectContainer(_x ,_y ,_depth , _width , _height)
{
	m_cur_msg = 0;
	for(uint_32 i = 0;i < 256;i++) {
		m_key_table[i] = false;
	}
}
EventListener::EventListener(const EventListener & _event_listener):ObjectContainer(_event_listener) {
	
}

EventListener::~EventListener(){
}

void EventListener::add_listener(int_32 _msg , handler _handler) {
	if(_handler == NULL) {
		return ;
	}
	m_func_table.insert(std::pair<int_32 , handler>(_msg , _handler));
}

void EventListener::remove_listener(int_32 _name) {
	std::map<int_32 , handler>::iterator		_it;

	if((_it = m_func_table.find(_name)) == m_func_table.end()) {	
		return;
	}

	m_func_table.erase(_it);
}
//
bool EventListener::get_pass_right() {
	return EventListener::PASSABLE;
}
bool EventListener::deal_event(OptEvent * _event) {
	int_32			_name = _event->get_name();
	uint_32			i = 0;
	std::map<int_32 , handler>::iterator		_it;

	m_cur_msg = _name;

	if((_it = m_func_table.find(_name)) == m_func_table.end()) {	
		return EventListener::PASSABLE;
	}

	(*_it->second)(_event , this);
	return get_pass_right();
}

void EventListener::set_key_true(int_32 _key) {
	m_key_table[_key] = true;
}

void EventListener::set_key_false(int_32 _key) {
	m_key_table[_key] = false;
}

bool EventListener::get_key_state(int_32 _key) {
	return m_key_table[_key];
}