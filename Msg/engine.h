/*-------------------------------
Author: carmazhao

Date:   2011/12/20

Function:The mediator class is used
to deal with the passed in
message of a module
-------------------------------*/
#ifndef MSG_ENGINE_HEAD_
#define MSG_ENGINE_HEAD_
#include "../Main/sysDef.h"
class engine
{
	DEFINE_SINGLE_MODEL(engine)
public:
	~engine();
	void		dispatcher();
private:
	engine();
};
#endif