#include "MapUtil.h"

IMPLEMENT_SINGLE_MODEL(MapUtil)

MapUtil::MapUtil() {

}

MapUtil::~MapUtil() {

}

int_32	MapUtil::get_cur_map_id() {
	return MapCtr::get_instance()->get_scene_id();
}

RECT	MapUtil::get_role_limit_rect() {
	return  MapCtr::get_instance()->get_role_rect();
}

bool	MapUtil::check_movable(int_32 _flag) {
	switch (_flag)
	{
	case CHECK_MOVE_UP:
		return MapCtr::get_instance()->check_move_2_up();
	case CHECK_MOVE_DOWN:
		return MapCtr::get_instance()->check_move_2_down();
	case CHECK_MOVE_LEFT:
		return MapCtr::get_instance()->check_move_2_left();
	case CHECK_MOVE_RIGHT:
		return MapCtr::get_instance()->check_move_2_right();
	default:
		return true;
	}
}