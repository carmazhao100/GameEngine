#include "engine.h"
#include "../NetWorker/NetWorker.h"
#include "proxyCenter.h"

IMPLEMENT_SINGLE_MODEL(engine)

engine::engine() {
}

engine::~engine() {

}

void engine::dispatcher() {
	proxyMsg *		_p_msg;


		_p_msg = MsgQueue::get_instance()->pop_out();
		if(_p_msg == NULL) {
			return;
		}
		proxyCenter::getInstance()->send_proxy_msg(_p_msg);
		if (_p_msg != NULL)
		{
			delete _p_msg;
		}
}