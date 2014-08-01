/*===============================
//Author:	carmazhao
//Data:		2012/1/4
//Functoin:	display obj
//			contain objs
//			listen to the operation
================================*/
#ifndef GRAPH_EVENT_LISTENER_HEAD_
#define GRAPH_EVENT_LISTENER_HEAD_
#include "../Main/sysDef.h"
#include "ObjectContainer.h"
#include "OptEvent.h"
#include <map>

typedef	void (*handler)(OptEvent * , void *);

class EventListener:public ObjectContainer
{
public:
	enum {
		PASSABLE = true,
		IMPASSABLE = false
	};
	EventListener(int_32   _x , 
		int_32 			_y  , 
		int_32 			_depth  ,
		int_32 			_width ,
		int_32 			_height);

	EventListener(const EventListener & _event_listener);
	virtual ~EventListener();

	bool				deal_event(OptEvent * _event);	//<deal with event
	void				add_listener(int_32 , handler);	//<add event listener
	void				remove_listener(int_32);		//<remove event listener
	virtual bool		get_pass_right();				//<return passable or not
	void				set_key_true(int_32	 _key);
	void				set_key_false(int_32  _key);
	bool				get_key_state(int_32 _key);
protected:
	int_32						m_cur_msg;
	std::map<int_32 , handler>	m_func_table;
	bool						m_key_table[256];
};
#endif