/*==========================================
/!Author:	carmazhao
/!Date:		2012/2/15
/!Function:	meediator of role module
===========================================*/
#ifndef ROLE_MEDIATOR_HEAD_
#define ROLE_MEDIATOR_HEAD_
#include "sysDef.h"
#include "../Msg/Imediator.h"
#include "msgIdCtr.h"
#include "role.h"

class roleMediator:public Imediator
{
public:
	roleMediator();
	~roleMediator();
	void dispatchMsg(command *_cmd);
private:
	void initial_role_by_net(int_32 _id , 
							int_8* _name , 
							int_32 _hp);
};
#endif