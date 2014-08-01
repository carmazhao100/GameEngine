#include "Player.h"
#include "../Resource/Config.h"
#include "MapConst.h"

Player::Player():EventListener(0,0,0,32,32){
	m_an_state = Player::ROLE_ANIMATION_UP_STATIC;
}

Player::~Player(){
}

Player::Player(const Player& _player):EventListener(_player){
	m_id = _player.get_id();
}

void Player::initial_player(int_32 _type) {
	make_test_type_player();
}

//<!!!THE  CODE  HERE MUST BE CHANGED INTO INI MODEL
void Player::make_test_type_player() {
	Animation* _animation = new Animation();
	//the first
	_animation->add_frame(Config::get_instance()->get_texture(Config::ROLE_MOVE_UP_1));
	_animation->add_frame(Config::get_instance()->get_texture(Config::ROLE_MOVE_UP_2));
	_animation->set_fps(20);
	add_animation(ROLE_ANIMATION_UP , _animation);
	_animation = NULL;

	_animation = new Animation();
	_animation->add_frame(Config::get_instance()->get_texture(Config::ROLE_MOVE_DOWN_1));
	_animation->add_frame(Config::get_instance()->get_texture(Config::ROLE_MOVE_DOWN_2));
	_animation->set_fps(20);
	add_animation(ROLE_ANIMATION_DOWN , _animation);
	_animation = NULL;

	_animation = new Animation();
	_animation->add_frame(Config::get_instance()->get_texture(Config::ROLE_MOVE_LEFT_1));
	_animation->add_frame(Config::get_instance()->get_texture(Config::ROLE_MOVE_LEFT_2));
	_animation->set_fps(20);
	add_animation(ROLE_ANIMATION_LEFT , _animation);
	_animation = NULL;

	_animation = new Animation();
	_animation->add_frame(Config::get_instance()->get_texture(Config::ROLE_MOVE_RIGHT_1));
	_animation->add_frame(Config::get_instance()->get_texture(Config::ROLE_MOVE_RIGHT_2));
	_animation->set_fps(20);
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

int_32 Player::get_id() const{
	return m_id;
}



void Player::set_id(const int_32 &_id) {
	m_id = _id;
}


void	Player::play_animation() {
	if(m_animation_table.find(m_an_state) == m_animation_table.end()){
		return ;
	}
	m_animation_table[m_an_state]->play();
}

void	Player::stop_animation() {
	if(m_animation_table.find(m_an_state) == m_animation_table.end()){
		return ;
	}
	m_animation_table[m_an_state]->stop();
}

void	Player::execute_change() {
	switch (m_an_state)
	{
	case ROLE_ANIMATION_UP:
		m_y -= MapConst::MAP_SPEED;
		break;
	case ROLE_ANIMATION_DOWN:
		m_y += MapConst::MAP_SPEED;
		break;
	case ROLE_ANIMATION_LEFT:
		m_x -= MapConst::MAP_SPEED;
		break;
	case ROLE_ANIMATION_RIGHT:
		m_x += MapConst::MAP_SPEED;
		break;
	}
}