#ifndef HEAD_MSG_CONST
#define HEAD_MSG_CONST
#include"msgIdCtr.h"
#include"sysDef.h"
class msgConst {
public:

//--------------heart beat info
	static const uint_32		HEART_BEAT_FROM_SERVER = 1;

//-------------role info
	static const uint_32		ROLE_INITIAL_FROM_NET_MSG = 2;

//-------------player snap shot
	static const uint_32		ROLE_SNAP_SHOT_SET = 3;
};
#endif
