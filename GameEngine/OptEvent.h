/*===============================
//Author:	carmazhao
//Data:		2011/1/4
//Functoin:	pass the operation of
//			these key or mouse opt
//			
================================*/
#ifndef GRAPH_OPT_EVENT_HEAD_
#define GRAPH_OPT_EVENT_HEAD_
#include "../Main/sysDef.h"
//#include "BaseUi.h"
#include <vector>

class OptEvent
{
	DEFINE_OBJ_POOL(OptEvent)
public:
	enum {
		LEFT_MOUSE_DOWN = 0,
		LEFT_MOUSE_UP,
		RIGHT_MOUSE_DOWN,
		RIGHT_MOUSE_UP,
		MOUSE_MOVE,
		KEY_DOWN,
		KEY_UP
	};

	OptEvent(const int_32 & _name ,\
			 HWND			_hwnd ,\
			 WPARAM			_wparam , \
			 LPARAM			_lparam);
	~OptEvent();

	int_32			get_name();
	int_32			get_mouse_x();
	int_32			get_mouse_y();

	int_32			get_key();
private:
	int_32			m_name;
	HWND			m_hwnd;
	WPARAM			m_wParam;
	LPARAM			m_lParam;
};


#endif