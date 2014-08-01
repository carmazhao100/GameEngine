/*==========================================
/!Author:	carmazhao
/!Date:		2011/12/29
/!Function:	the interface of all the functions
			of  other basic model
			1.mediator register
			2.proxy	   register
			3.game initial
===========================================*/
#ifndef MAIN_FACADE_HEAD_
#define MAIN_FACADE_HEAD_
#include "sysDef.h"
#include "../Msg/msgCenter.h"
#include "../Msg/proxyCenter.h"
#include "../NetWorker/NetWorker.h"

class Facade
{
	DEFINE_SINGLE_MODEL(Facade)
public:
	void		register_proxy(Iproxy *);		//add proxy
	void		register_mediator(Imediator *);	//add mediator


	void		send_command(command * _cmd);
	void		send_net_msg(NetMsg * _msg);

	void		initial_game_module();			//create game modules

	void		initial_game_net();				//initial game basic func

	void		initial_game_ini();				//read the ini file 

	~Facade();
private:
	Facade();
};
#endif