#include "../NetWorker/NetWorker.h"
#include "../GameEngine/GWindow.h"
#include "../Resource/Config.h"
#include "../GameEngine/Scene.h"
#include "Facade.h"
#include <string.h>

int main() { 
	Facade::get_instance()->initial_game_net();
	DEBUG_SHOW("Net ok =========");


	NetMsg * msg = new NetMsg();
	int_32 size = 3*sizeof(int_32) + strlen("zhao") + strlen("zhao");
	int_32 id = 500000;
	msg->write_int_32(size);
	msg->write_int_32(id);
	msg->write_str("zhao", strlen("zhao"));
	msg->write_str("zhao" , strlen("zhao"));
	NetWorker::get_instance()->send_msg(msg);
	
	
	GWindow::get_instance()->initial_window("zxzgame",0,0,800,600,false);
	DEBUG_SHOW("Window ok=========");
	Facade::get_instance()->initial_game_ini();
	DEBUG_SHOW("ini ok=========");
	Facade::get_instance()->initial_game_module();
	DEBUG_SHOW("module ok=========");

	//GWindow::get_instance()->set_fps(24);
	DEBUG_SHOW("fps ok=========");
	GWindow::get_instance()->game_loop();
	return 0;
} 