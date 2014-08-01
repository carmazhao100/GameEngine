#include "MapProxy.h"
#include "Facade.h"
#include "../NetWorker/NetWorker.h"
#include "MapCtr.h"

MapProxy::MapProxy() {

}

MapProxy::~MapProxy() {

}

void	MapProxy::dispatchMsg(proxyMsg *msg) {
	if(msg == NULL) {
		return;
	}
	uint_32					_msg_id = msg->get_proxy_msg_id();
	int_32					_scene_id = 0;
	int_32					_x = 0;
	int_32					_y = 0;

	switch (_msg_id)
	{
	case R_MAP_INFO_IN:
		_scene_id = msg->get_int_32();
		_x		  = msg->get_int_32();
		_y		  = msg->get_int_32();
		MapCtr::get_instance()->initial_map(_scene_id , _x , _y);
		break;
	default:
		return;
	}
}