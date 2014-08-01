#include "HeartBeatProxy.h"
#include "../NetWorker/NetWorker.h"
#include "../Msg/command.h"
#include "msgConst.h"
#include "Facade.h"

HeartBeatProxy::HeartBeatProxy() {
	m_msg_arr.push_back(HeartBeatProxy::HEART_BEAT_MESSAGE_IN);
}

HeartBeatProxy::~HeartBeatProxy() {

}

void	HeartBeatProxy::dispatchMsg(proxyMsg *msg) {
	if(msg == NULL) {
		return;
	}
	uint_32					_msg_id = msg->get_proxy_msg_id();
	command*				_cmd  = NULL;

	switch (_msg_id)
	{
	case HEART_BEAT_MESSAGE_IN:
		_cmd = new command(msgConst::HEART_BEAT_FROM_SERVER);
		Facade::get_instance()->send_command(_cmd);
		break;
	}
}

void	HeartBeatProxy::send_beat_to_server() {
	NetMsg*				_net_msg = new NetMsg();
	int_32				_msg_id = HeartBeatProxy::SEND_HEART_BEAT_TO_SERVER;
	int_32				_size = 0;

	_size = (int_32)sizeof(_msg_id);

	_net_msg->write_int_32(_size);		//write in info size
	_net_msg->write_int_32(_msg_id);	//write in info

	Facade::get_instance()->send_net_msg(_net_msg);

	if(_net_msg != NULL) {	
		delete	_net_msg;
	}
}