/*==========================================
/!Author:	carmazhao
/!Date:		2012/2/15
/!Function:	proxy of role module
===========================================*/
#ifndef ROLE_PROXY_HEAD_
#define	ROLE_PROXY_HEAD_
#include "sysDef.h"
#include "../Msg/Iproxy.h"

class roleProxy:public Iproxy
{
public:
	enum {
		R_ROLE_INITIAL = 100010,
		S_ROLE_MOVE_STATE_CHANGE = 500010
	};

	enum {
		MOVE_UP = 0,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		NO_MOVE
	};
	roleProxy();
	~roleProxy();

	void dispatchMsg(proxyMsg * msg);
	void send_mov_state(const int_32 & _state);
	
private:
	void initial_role();
};
#endif