/*===============================
//Author:	carmazhao
//Data:		2012/2/19
//Functoin:	util of the role
//			
//			
================================*/
#ifndef ROLE_UTIL_HEAD_
#define ROLE_UTIL_HEAD_
#include "role.h"
#include "sysDef.h"

class roleUtil
{
	DEFINE_SINGLE_MODEL(roleUtil)
public:
	~roleUtil();

	RECT		get_role_rect();
private:
	roleUtil();
};
#endif