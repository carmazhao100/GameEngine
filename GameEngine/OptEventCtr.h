#ifndef OPT_EVENT_LISTENER_HEAD
#define OPT_EVENT_LISTENER_HEAD
#include "../Main/sysDef.h"
#include "BaseUi.h"
#include "OptEvent.h"


class OptEventCtr
{
	DEFINE_SINGLE_MODEL(OptEventCtr)
public:
	~OptEventCtr();

	void		add_ui_listener(BaseUi* _listener);
	void		remove_ui_listener(BaseUi* _listener);
	void		set_role(EventListener* _role);
	
	void		dispatch_event(OptEvent * _event);
private:
	std::vector<BaseUi*>			m_arr;			//when should check from back to front 
	EventListener*					m_role_p;

	OptEventCtr();
};
#endif