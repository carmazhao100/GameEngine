#include "PlayersCtr.h"

IMPLEMENT_SINGLE_MODEL(PlayersCtr)

PlayersCtr::PlayersCtr() {

}

PlayersCtr::~PlayersCtr() {

}

void PlayersCtr::clear_player() {
	uint_32					_i = 0;
	for (;_i < m_player_arr.size();_i++)
	{
		m_player_arr[_i].stop_animation();
	}
	m_player_arr.clear();
}
void PlayersCtr::add_player(Player  _player)
{
	m_player_arr.push_back(_player);
	(m_player_arr.back()).play_animation();
}

void PlayersCtr::remove_player(const int_32 &_id) {
	uint_32					_i = 0;
	
	for (;_i < m_player_arr.size();_i++)
	{
		if (m_player_arr[_i].get_id() == _id)
		{
			m_player_arr.erase(m_player_arr.begin() + _i);
		}
	}
}

void PlayersCtr::draw() {
	uint_32					_i = 0;

	for (;_i < m_player_arr.size();_i++)
	{
		m_player_arr[_i].draw();
	}
}

void PlayersCtr::execute_change() {
	uint_32					_i = 0;

	for (;_i < m_player_arr.size();_i++)
	{
		m_player_arr[_i].execute_change();
	}
}