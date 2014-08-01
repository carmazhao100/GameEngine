#include "snapShotProxy.h"
#include "snapShotCtr.h"
#include "Player.h"
#include <vector>
//players
#include "PlayersCtr.h"

snapShotProxy::snapShotProxy() {
	m_msg_arr.push_back(R_ROLE_SNAP_SHOT);
}

snapShotProxy::~snapShotProxy() {

}

void	snapShotProxy::dispatchMsg(proxyMsg * msg) {
	if(msg == NULL) {
		return;
	}
	uint_32					_msg_id = msg->get_proxy_msg_id();

	switch (_msg_id)
	{
	case R_ROLE_SNAP_SHOT:
		deal_role_snap_shot(msg);
		break;
	}
}


//===============DEAL  FUNCTIONS
void	snapShotProxy::deal_role_snap_shot(proxyMsg* _msg) {
	std::vector<Player>				_player_arr;
	Player							_player;
	uint_32							_num = 0;
	uint_32							_i = 0;		

	//read the sum num
	_num = _msg->get_int_32();

	PlayersCtr::get_instance()->clear_player();
	for (;_i < _num;_i++)
	{
		_player.set_id(_msg->get_int_32());
		_player.initial_player(_msg->get_int_32());
		_player.set_x(_msg->get_int_32());
		_player.set_y(_msg->get_int_32());
		_player.set_an_state(_msg->get_int_32());
		PlayersCtr::get_instance()->add_player(_player);
	}
}