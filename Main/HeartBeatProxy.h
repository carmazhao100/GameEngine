/*==========================================
/!Author:	carmazhao
/!Date:		2012/1/9
/!Function:	proxy of heart beat module
===========================================*/
#ifndef HEART_BEAT_PROXY_HEAD_
#define HEART_BEAT_PROXY_HEAD_
#include "sysDef.h"
#include "../Msg/Iproxy.h"

class HeartBeatProxy:public Iproxy
{
public:
	enum {
		HEART_BEAT_MESSAGE_IN = 100001 ,
//info to send to server
		SEND_HEART_BEAT_TO_SERVER = 500001
	};
	HeartBeatProxy();
	~HeartBeatProxy();

	void dispatchMsg(proxyMsg *msg);

	void send_beat_to_server();
private:
};
#endif