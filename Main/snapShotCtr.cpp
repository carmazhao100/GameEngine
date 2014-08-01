#include "snapShotCtr.h"
#include "../Msg/command.h"
#include "msgConst.h"
#include "Facade.h"


IMPLEMENT_SINGLE_MODEL(snapShotCtr)

snapShotCtr::snapShotCtr(){

}

snapShotCtr::~snapShotCtr() {

}

void snapShotCtr::deal_player_snap_shot(const std::vector<Player> & _player_arr) {
	uint_32							_i = 0;
	command*						_cmd = new command(msgConst::ROLE_SNAP_SHOT_SET);

	_cmd->write_int_32(_player_arr.size());
	
	//write in the player information
	for (;_i < _player_arr.size();_i++)
	{
		_cmd->write_int_32((int_32)(&_player_arr[_i]));
	}
	Facade::get_instance()->send_command(_cmd);
	if (_cmd != NULL)
	{
		delete _cmd;
	}
}