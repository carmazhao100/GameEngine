/*==========================================
/!Author:	carmazhao
/!Date:		2012/2/26
/!Function:	meediator of role module
===========================================*/
#ifndef PLAYERS_CTR_MEDIATOR_HEAD_
#define	PLAYERS_CTR_MEDIATOR_HEAD_
#include "snapShotCtr.h"
#include "../Msg/Imediator.h"
#include "../Msg/command.h"
#include "sysDef.h"

class PlayersCtrMediator:public Imediator
{
public:
	~PlayersCtrMediator();
	PlayersCtrMediator();
	void dispatchMsg(command *_cmd);
private:
};
#endif