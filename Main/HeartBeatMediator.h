#ifndef HEART_BEAT_MEDIATOR_HEAD_
#define HEART_BEAT_MEDIATOR_HEAD_
#include "sysDef.h"
#include "../Msg/Imediator.h"
#include "msgIdCtr.h"
#include "HeartBeater.h"

class HeartBeatMediator:public Imediator
{
public:
	HeartBeatMediator();
	~HeartBeatMediator();
	void dispatchMsg(command *_cmd);
private:
};
#endif