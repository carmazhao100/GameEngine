#include "HeartBeatMediator.h"
#include "msgConst.h"


HeartBeatMediator::HeartBeatMediator(){
	m_msgArr.push_back(msgConst::HEART_BEAT_FROM_SERVER);
}

HeartBeatMediator::~HeartBeatMediator() {
}


void HeartBeatMediator::dispatchMsg(command *_cmd){
	uint_32				_msg = _cmd->get_msg_name();

	switch (_msg)
	{
	case msgConst::HEART_BEAT_FROM_SERVER:
		HeartBeater::get_instance()->get_beat_frome_server();
		break;
	default:
		break;
	}
}