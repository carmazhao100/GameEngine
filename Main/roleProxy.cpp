#include "roleProxy.h"
#include "../NetWorker/NetWorker.h"
#include "../Msg/command.h"
#include "msgConst.h"
#include "Facade.h"

roleProxy::roleProxy() {
	m_msg_arr.push_back(roleProxy::R_ROLE_INITIAL);
}

roleProxy::~roleProxy() {

}

void	roleProxy::dispatchMsg(proxyMsg *  _msg) {
	if(_msg == NULL) {
		return ;
	}

	uint_32				_msg_id = _msg->get_proxy_msg_id();
	command*			_cmd = NULL;

	switch (_msg_id)
	{
	case R_ROLE_INITIAL:
		_cmd = new  command(msgConst::ROLE_INITIAL_FROM_NET_MSG);
	 	_cmd->write_int_32(_msg->get_int_32());		//write the id
		_cmd->write_str(_msg->get_str());			//write the name
		_cmd->write_int_32(_msg->get_int_32());		//write the hp
		msgCenter::getInstance()->sendCommand(_cmd);
		break;
	}

	if (_cmd != NULL)
	{
		delete _cmd;
	}
}			

void roleProxy::send_mov_state(const int_32 & _state) {
	NetMsg*					_net_msg = new NetMsg();
	int_32					_msg_id = roleProxy::S_ROLE_MOVE_STATE_CHANGE;
	int_32					_size = 0;

	_size = (int_32)sizeof(int_32)*2;
	_net_msg->write_int_32(_size);
	_net_msg->write_int_32(_msg_id);
	_net_msg->write_int_32(_state);

	Facade::get_instance()->send_net_msg(_net_msg);

	if (_net_msg != NULL)
	{
		delete _net_msg;
	}
}