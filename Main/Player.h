/*===============================
//Author:	carmazhao
//Data:		2011/2/26
//Functoin: other players
================================*/
#ifndef PLAYER_HEAD_
#define PLAYER_HEAD_
#include "sysDef.h"
#include "../GameEngine/EventListener.h"

class Player:public EventListener
{
public:
	//define the animation type
	enum {
		TEST_TYPE
	};
	//animation kind
	enum {
		ROLE_ANIMATION_UP = 0,
		ROLE_ANIMATION_DOWN,
		ROLE_ANIMATION_LEFT,
		ROLE_ANIMATION_RIGHT,

		ROLE_ANIMATION_UP_STATIC,
		ROLE_ANIMATION_DOWN_STATIC,
		ROLE_ANIMATION_LEFT_STATIC,
		ROLE_ANIMATION_RIGHT_STATIC
	};
	Player();
	Player(const Player & _player);
	~Player();
	
	void	initial_player(int_32	_type);
	void	execute_change();

	void	play_animation();
	void	stop_animation();
	
	void	set_id(const int_32 & _id);

	int_32	get_id()const;
private:
	int_32				m_id;
	//<!!!THE  CODE  HERE MUST BE CHANGED INTO INI MODEL
	void	make_test_type_player();
};
#endif