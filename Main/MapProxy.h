/*===============================
//Author:	carmazhao
//Data:		2012/1/28
//Functoin:	The proxy of the map
//			
//			
================================*/
#ifndef MAP_PROXY_HEAD_
#define MAP_PROXY_HEAD_
#include "sysDef.h"
#include "../Msg/Iproxy.h"

class MapProxy:public Iproxy
{
public:
	enum {
		R_MAP_INFO_IN = 100002
	};
	MapProxy();
	~MapProxy();

	void	dispatchMsg(proxyMsg *msg);
private:
};
#endif