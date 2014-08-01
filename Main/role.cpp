#include "role.h"
#include "../GameEngine/OptEvent.h"
#include "../GameEngine/OptEventCtr.h"
#include "../Resource/Config.h"
#include "../GameEngine/GWindow.h"
#include "roleUtil.h"
#include "MapUtil.h"
#include "MapConst.h"
#include "roleProxy.h"

#include <string.h>

IMPLEMENT_SINGLE_MODEL(role)

role::role():EventListener(0,0,0,32,32){
	m_an_state = ROLE_ANIMATION_UP;
	initial_role();
	initial_ui();
}

role::~role() {

}
void on_key_down_helper(OptEvent* _event , void *_p) {
	if (_event == NULL)
	{
		return ;
	}
//the net proxy
	roleProxy							_proxy;

	//if the state exists
	if ((static_cast<role*>(_p))->get_key_state(_event->get_key()))
	{
		return ;
	}
	(static_cast<role*>(_p))->set_key_true(_event->get_key());
	//stop the animation
	(static_cast<role*>(_p))->stop_animation();
	
	//if the command is to down a key
	switch (_event->get_key())
	{
	case UP_KEY_MSG:
		(static_cast<role*>(_p))->set_an_state(role::ROLE_ANIMATION_UP);
		_proxy.send_mov_state(roleProxy::MOVE_UP);
		break;
	case DOWN_KEY_MSG:
		(static_cast<role*>(_p))->set_an_state(role::ROLE_ANIMATION_DOWN);
		_proxy.send_mov_state(roleProxy::MOVE_DOWN);
		break;
	case LEFT_KEY_MSG:
		(static_cast<role*>(_p))->set_an_state(role::ROLE_ANIMATION_LEFT);
		_proxy.send_mov_state(roleProxy::MOVE_LEFT);
		break;
	case RIGHT_KEY_MSG:
		(static_cast<role*>(_p))->set_an_state(role::ROLE_ANIMATION_RIGHT);
		_proxy.send_mov_state(roleProxy::MOVE_RIGHT);
		break;
	}
	(static_cast<role*>(_p))->play_animation();
}

void on_key_up_helper(OptEvent* _event , void *_p) {
	int_32					_an_state = 0;


	if (_event == NULL)
	{
		return ;
	}
	(static_cast<role*>(_p))->set_key_false(_event->get_key());

//get the state
	switch (_event->get_key())
	{
	case UP_KEY_MSG:
		_an_state = role::ROLE_ANIMATION_UP;
		break;
	case DOWN_KEY_MSG:
		_an_state = role::ROLE_ANIMATION_DOWN;
		break;
	case LEFT_KEY_MSG:
		_an_state = role::ROLE_ANIMATION_LEFT;
		break;
	case RIGHT_KEY_MSG:
		_an_state = role::ROLE_ANIMATION_RIGHT;
		break;
	}
	if ((static_cast<role*>(_p))->get_an_state() != _an_state)
	{
		return;
	}
	//stop the animation
	
	(static_cast<role*>(_p))->stop_animation();
}
void role::initial_role() {
	//initial the event listening
	OptEventCtr::get_instance()->set_role(this);
	this->add_listener(OptEvent::KEY_DOWN , on_key_down_helper); 
	this->add_listener(OptEvent::KEY_UP , on_key_up_helper); 
}

void role::initial_ui(){
	Animation* _animation = new Animation();
	//the first
	_animation->add_frame(Config::get_instance()->get_texture(Config::ROLE_MOVE_UP_1));
	_animation->add_frame(Config::get_instance()->get_texture(Config::ROLE_MOVE_UP_2));
	_animation->set_fps(5);
	add_animation(ROLE_ANIMATION_UP , _animation);
	_animation = NULL;

	_animation = new Animation();
	_animation->add_frame(Config::get_instance()->get_texture(Config::ROLE_MOVE_DOWN_1));
	_animation->add_frame(Config::get_instance()->get_texture(Config::ROLE_MOVE_DOWN_2));
	_animation->set_fps(5);
	add_animation(ROLE_ANIMATION_DOWN , _animation);
	_animation = NULL;

	_animation = new Animation();
	_animation->add_frame(Config::get_instance()->get_texture(Config::ROLE_MOVE_LEFT_1));
	_animation->add_frame(Config::get_instance()->get_texture(Config::ROLE_MOVE_LEFT_2));
	_animation->set_fps(5);
	add_animation(ROLE_ANIMATION_LEFT , _animation);
	_animation = NULL;

	_animation = new Animation();
	_animation->add_frame(Config::get_instance()->get_texture(Config::ROLE_MOVE_RIGHT_1));
	_animation->add_frame(Config::get_instance()->get_texture(Config::ROLE_MOVE_RIGHT_2));
	_animation->set_fps(5);
	add_animation(ROLE_ANIMATION_RIGHT , _animation);
	_animation = NULL;

	_animation = new Animation();
	_animation->add_frame(Config::get_instance()->get_texture(Config::ROLE_STATIC_UP));
	add_animation(ROLE_ANIMATION_UP_STATIC , _animation);
	_animation = NULL;

	_animation = new Animation();
	_animation->add_frame(Config::get_instance()->get_texture(Config::ROLE_STATIC_DOWN));
	add_animation(ROLE_ANIMATION_DOWN_STATIC , _animation);
	_animation = NULL;

	_animation = new Animation();
	_animation->add_frame(Config::get_instance()->get_texture(Config::ROLE_STATIC_LEFT));
	add_animation(ROLE_ANIMATION_LEFT_STATIC , _animation);
	_animation = NULL;

	_animation = new Animation();
	_animation->add_frame(Config::get_instance()->get_texture(Config::ROLE_STATIC_RIGHT));
	add_animation(ROLE_ANIMATION_RIGHT_STATIC , _animation);
	_animation = NULL;

	//initial the state
	m_an_state = ROLE_ANIMATION_UP_STATIC;
}

void role::set_an_state(int_32 _state) {
	m_an_state = _state;
}

int_32	role::get_an_state() {
	return m_an_state;
}

void role::play_animation() {
	if(m_animation_table.find(m_an_state) == m_animation_table.end()){
			return ;
	}
	m_animation_table[m_an_state]->play();
}

void role::stop_animation() {
	//the net proxy
	roleProxy							_proxy;
	if(m_animation_table.find(m_an_state) == m_animation_table.end()){
		return ;
	}
	m_animation_table[m_an_state]->stop();

	switch (m_an_state)
	{
	case ROLE_ANIMATION_UP:
		m_an_state = ROLE_ANIMATION_UP_STATIC;
		break;
	case ROLE_ANIMATION_DOWN:
		m_an_state = ROLE_ANIMATION_DOWN_STATIC;
		break;
	case ROLE_ANIMATION_LEFT:
		m_an_state = ROLE_ANIMATION_LEFT_STATIC;
		break;
	case ROLE_ANIMATION_RIGHT:
		m_an_state = ROLE_ANIMATION_RIGHT_STATIC;
		break;
	}
	_proxy.send_mov_state(m_an_state);
}


void role::execute_change() {
	RECT				_role_rect = roleUtil::get_instance()->get_role_rect();
	RECT				_role_limit_rect = MapUtil::get_instance()->get_role_limit_rect();

	switch (m_an_state)
	{
	case ROLE_ANIMATION_UP:
		if (!check_boundary(role::CHECK_MOVE_UP))
		{
			return;
		}
		if(_role_rect.top > _role_limit_rect.bottom ||   // check self  
														// check map boundary
		!(MapUtil::get_instance()->check_movable(MapUtil::CHECK_MOVE_UP))) {
			m_y -= MapConst::MAP_SPEED;
		}
		break;
	case ROLE_ANIMATION_DOWN:
		if (!check_boundary(role::CHECK_MOVE_DOWN))
		{
			return;
		}
		if(_role_rect.bottom < _role_limit_rect.top ||   // check self  
			// check map boundary
			!(MapUtil::get_instance()->check_movable(MapUtil::CHECK_MOVE_DOWN))) {
				m_y += MapConst::MAP_SPEED;
		}
		break;
	case ROLE_ANIMATION_LEFT:
		if (!check_boundary(role::CHECK_MOVE_LEFT))
		{
			return;
		}
		if(_role_rect.left > _role_limit_rect.right ||   // check self  
			// check map boundary
			!(MapUtil::get_instance()->check_movable(MapUtil::CHECK_MOVE_LEFT))) {
				m_x -= MapConst::MAP_SPEED;
		}
		break;
	case ROLE_ANIMATION_RIGHT:
		if (!check_boundary(role::CHECK_MOVE_RIGHT))
		{
			return;
		}
		if(_role_rect.right < _role_limit_rect.left ||   // check self  
			// check map boundary
			!(MapUtil::get_instance()->check_movable(MapUtil::CHECK_MOVE_RIGHT))) {
				m_x += MapConst::MAP_SPEED;
		}
		break;
	}
}

bool	role::check_boundary(int_32 _flag) {
	switch (_flag)
	{
	case CHECK_MOVE_UP:
		if (m_y < ROLE_CHECK_ERROR_SPACE)
		{
			return false;
		}
		break;
	case CHECK_MOVE_DOWN:
		if (m_y + m_height > 
			GWindow::get_instance()->get_window_height() - ROLE_CHECK_ERROR_SPACE)
		{
			return false;
		}
		break;
	case CHECK_MOVE_LEFT:
		if (m_x < ROLE_CHECK_ERROR_SPACE)
		{
			return false;
		}
		break;
	case CHECK_MOVE_RIGHT:
		if (m_x + m_width > 
			GWindow::get_instance()->get_window_width() - ROLE_CHECK_ERROR_SPACE)
		{
			return false;
		}
		break;
	}
	return true;
}


//============================GET FUNCS
void	role::set_id(int_32 _id) {
	m_id = _id;
}

void	role::set_hp(int_32 _hp) {
	m_hp = _hp;
}

void   role::set_name(int_8 *_name) {
	strcpy_s(m_name , _name);
}



//===========================SET FUNCS
int_32	role::get_id() {
	return m_id;
}

int_8*	role::get_name() {
	return m_name;
}

int_32	role::get_hp() {
	return m_hp;
}
