#include "roleUtil.h"

IMPLEMENT_SINGLE_MODEL(roleUtil)
roleUtil::roleUtil(){
	
}

roleUtil::~roleUtil() {
	
}

RECT	roleUtil::get_role_rect() {
	RECT			_rect;

	_rect.left = role::get_instance()->get_x();
	_rect.right = role::get_instance()->get_x() + role::get_instance()->get_width();
	_rect.top = role::get_instance()->get_y();
	_rect.bottom = role::get_instance()->get_y() + role::get_instance()->get_height();

	return _rect;
}