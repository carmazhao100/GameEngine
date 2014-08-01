#include "OptEventCtr.h"
#include "../Main/MapCtr.h"

IMPLEMENT_SINGLE_MODEL(OptEventCtr)

OptEventCtr::OptEventCtr(){
	m_role_p = NULL;
}

OptEventCtr::~OptEventCtr(){

}

void OptEventCtr::add_ui_listener(BaseUi *_listener) {
	if(_listener == NULL) {
		return ;
	}
	m_arr.push_back(_listener);
}

void OptEventCtr::remove_ui_listener(BaseUi *_listener) {
	if(_listener == NULL) {
		return ;
	}
	uint_32				i = 0;

	for (;i < m_arr.size();i++)
	{
		if(m_arr[i] == _listener) {
			m_arr.erase(m_arr.begin() + i);
			return ;
		}
	}
}

void OptEventCtr::set_role(EventListener* _role) {
	if(_role == NULL) {
		return ;
	}
	m_role_p = _role;
}

void OptEventCtr::dispatch_event(OptEvent *_event) {
	if(_event == NULL) {
		return ;
	}
	uint_32				i = 0;

	//check ui
	for (;i < m_arr.size();i++)
	{
		if(m_arr[m_arr.size() - i - 1] != NULL) {
			m_arr[m_arr.size() - i - 1]->deal_event(_event);
		}
	}

	//check map
	MapCtr::get_instance()->deal_event(_event);
	//check role
	if(m_role_p != NULL) {
		m_role_p->deal_event(_event);
	}
}