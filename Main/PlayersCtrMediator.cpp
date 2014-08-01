#include "PlayersCtrMediator.h"
#include "msgConst.h"
#include "PlayersCtr.h"
#include "Player.h"


PlayersCtrMediator::~PlayersCtrMediator(){

}

PlayersCtrMediator::PlayersCtrMediator() {
	m_msgArr.push_back(msgConst::ROLE_SNAP_SHOT_SET);
}

void PlayersCtrMediator::dispatchMsg(command *_cmd) {
	uint_32				_msg = _cmd->get_msg_name();

	uint_32				_num = 0;
	uint_32				_i = 0;
	Player				_player;

	switch (_msg)
	{
	case msgConst::ROLE_SNAP_SHOT_SET:
		//get the num of players
		_num = _cmd->read_int_32();
		PlayersCtr::get_instance()->clear_player();
		for (;_i < _num;_i++)
		{
			_player = *((Player*)(_cmd->read_int_32()));
			PlayersCtr::get_instance()->add_player(_player);
		}
		break;
	}
DEBUG_SHOW("END OF MEDIATOR");
}