#include "Facade.h"
#include "../NetWorker/NetWorker.h"
#include "../Msg/engine.h"
#include "../Msg/msgCenter.h"
#include "../Resource/Config.h"
#include "../GameEngine/Render.h"
#include "../GameEngine/GWindow.h"
#include "../GameEngine/TimerManager.h"
//modules
//heart beat
#include "HeartBeatMediator.h"
#include "HeartBeatProxy.h"
//role 
#include "role.h"
#include "roleProxy.h"
#include "roleMediator.h"
//map
#include "MapCtr.h"
//snap shot
#include "snapShotProxy.h"
//players
#include "PlayersCtrMediator.h"


IMPLEMENT_SINGLE_MODEL(Facade)
Facade::Facade() {

}

Facade::~Facade() {

}

void	Facade::register_mediator(Imediator * _mediator) {
	msgCenter::getInstance()->registerMediator(_mediator);
}

void	Facade::register_proxy(Iproxy *_proxy) {
	proxyCenter::getInstance()->registerProxy(_proxy);
}

void	Facade::send_command(command * _cmd) {
	msgCenter::getInstance()->sendCommand(_cmd);
}

void	Facade::send_net_msg(NetMsg * _msg) {
	NetWorker::get_instance()->send_msg(_msg);
}

void	Facade::initial_game_module() {
//initial fps
	Render::get_instance()->set_fps(24);
//initial role module
	role * _role = role::get_instance();
	Render::get_instance()->set_role(_role);
//initial map module
	MapCtr::get_instance()->create_map_table();
	MapCtr::get_instance()->set_camera(0,
									0,
									GWindow::get_instance()->get_window_width(),
									GWindow::get_instance()->get_window_height());
	MapCtr::get_instance()->initial_role_rect(GWindow::get_instance()->get_window_width()/2,
												GWindow::get_instance()->get_window_height()/2);
//initial timer
	TimerManager::get_instance()->initial_timer();



	//here create our modules
	//HEART BEAT MODULES
	HeartBeater::get_instance()->start_heart_beat();
	HeartBeatMediator*		_heart_beat_mediator = new HeartBeatMediator();
	HeartBeatProxy*			_heart_beat_proxy    = new HeartBeatProxy();
	msgCenter::getInstance()->registerMediator(_heart_beat_mediator);
	proxyCenter::getInstance()->registerProxy(_heart_beat_proxy);
	
	//ROLE MODULES
	roleProxy *				_role_proxy = new roleProxy();
	roleMediator*			_role_mediator = new roleMediator();
	proxyCenter::getInstance()->registerProxy(_role_proxy);
	msgCenter::getInstance()->registerMediator(_role_mediator);
	//SNAP SHOT
	snapShotProxy *			_snap_shot_proxy = new snapShotProxy();
	proxyCenter::getInstance()->registerProxy(_snap_shot_proxy);
	//PLAYERS
	PlayersCtrMediator *	_players_ctr_mediator = new PlayersCtrMediator();
	msgCenter::getInstance()->registerMediator(_players_ctr_mediator);
}

void	Facade::initial_game_net() {
	int_32				_res = 0;
	//initial net func
	_res = NetWorker::get_instance()->connect_server();
	//deal error 
	if(_res < 0) {
		switch (_res)
		{
		case	INITIAL_SOCKE_ERROR:
			break;
		case	SOCKET_CONNECT_ERROR:
			break;
		case	CREATE_SOCKET_ERROR:
			break;
		}
		exit(0);
	}
	//create net thread to get msg
	NetWorker::get_instance()->create_rev_thread();
}

void Facade::initial_game_ini(){
	Config::get_instance()->read_image_config("config/pic_config/landform1.fm");
	Config::get_instance()->read_image_config("config/pic_config/role.fm");

	Config::get_instance()->read_map_config("config/map_config/test.fmm");
}