#include "OptEvent.h"

IMPLEMENT_OBJ_POOL(OptEvent)

OptEvent::OptEvent(const int_32 & _name ,\
						HWND			_hwnd ,\
						WPARAM			_wparam , \
						LPARAM			_lparam){
	m_name = _name;
	m_hwnd = _hwnd;
	m_wParam = _wparam;
	m_lParam = _lparam;
}

OptEvent::~OptEvent() {

}

int_32	OptEvent::get_name() {
	return m_name;
}

int_32	OptEvent::get_mouse_x() {
	return LOWORD(m_lParam);
}

int_32	OptEvent::get_mouse_y() {
	return HIWORD(m_lParam);
}

int_32 OptEvent::get_key(){
	return m_wParam;
}


/****************************OPT EVENT LISTENER*************************/
