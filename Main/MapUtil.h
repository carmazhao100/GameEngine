/*==========================================
/!Author:	carmazhao
/!Date:		2012/2/16
/!Function:	you can get everything about map
===========================================*/
#ifndef MAP_UTIL_HEAD_
#define MAP_UTIL_HEAD_
#include "sysDef.h"
#include "MapCtr.h"


class MapUtil
{
	DEFINE_SINGLE_MODEL(MapUtil)
public:
	~MapUtil();
	enum {
		CHECK_MOVE_UP,
		CHECK_MOVE_DOWN,
		CHECK_MOVE_LEFT,
		CHECK_MOVE_RIGHT
	};

	int_32		get_cur_map_id();
	RECT		get_role_limit_rect();

	bool		check_movable(int_32	_flag);		//check the map can move or not
private:
	MapUtil();
};
#endif