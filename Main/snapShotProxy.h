/*===============================
//Author:	carmazhao
//Data:		2012/2/25
//Functoin:	snap shot proxy
//			
//			
================================*/
#ifndef SNAP_SHOT_PROXY_HEAD_
#define	SNAP_SHOT_PROXY_HEAD_
#include "sysDef.h"
#include "../Msg/Iproxy.h"

class snapShotProxy:public Iproxy
{
public:
	enum {
			R_ROLE_SNAP_SHOT = 100020
	};
	snapShotProxy();
	~snapShotProxy();

	void	dispatchMsg(proxyMsg * msg);
private:
	void	deal_role_snap_shot(proxyMsg* _msg);
};
#endif