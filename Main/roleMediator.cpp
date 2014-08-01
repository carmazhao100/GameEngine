#include "roleMediator.h"
#include "msgConst.h"
#include "role.h"

roleMediator::roleMediator() {
	m_msgArr.push_back(msgConst::ROLE_INITIAL_FROM_NET_MSG);
}

roleMediator::~roleMediator() {

}

void roleMediator::dispatchMsg(command *_cmd) {
	uint_32			_msg = _cmd->get_msg_name();

	switch (_msg)
	{
	case msgConst::ROLE_INITIAL_FROM_NET_MSG:
		initial_role_by_net(_cmd->read_int_32(),
							_cmd->read_str(),
							_cmd->read_int_32());
		break;
	}
}

void roleMediator::initial_role_by_net(int_32 _id, 
									   int_8 *_name, 
									   int_32 _hp) 
{
	role::get_instance()->set_id(_id);
	role::get_instance()->set_name(_name);
	role::get_instance()->set_id(_hp);
}
