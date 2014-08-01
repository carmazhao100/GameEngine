/*==========================================
/!Author:	carmazhao
/!Date:		2012/2/1
/!Function:	the role of the game
===========================================*/
#ifndef ROLE_HEAD_
#define ROLE_HEAD_
#include "sysDef.h"
#include "../GameEngine/EventListener.h"

#define ROLE_CHECK_ERROR_SPACE		5
#define ROLE_NAME_MAX_LENGTH		20
class role:public EventListener
{
	DEFINE_SINGLE_MODEL(role)
public:
	~role();

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

	enum {
		CHECK_MOVE_UP,
		CHECK_MOVE_DOWN,
		CHECK_MOVE_LEFT,
		CHECK_MOVE_RIGHT
	};

	void initial_role();
	void initial_ui();

	void				set_an_state(int_32	_state);
	int_32				get_an_state();
	void				play_animation();
	void				stop_animation();
	void				execute_change();
	bool				check_boundary(int_32 _flag);


private:
	role();

	//property of role
	int_32				m_id;
	int_8				m_name[ROLE_NAME_MAX_LENGTH];
	int_32				m_hp;	
public:
	//set funcs
	void				set_id(int_32 _id);
	void				set_name(int_8* _name);
	void				set_hp(int_32 _hp);

	//get funcs
	int_32				get_id();
	int_8*				get_name();
	int_32				get_hp();
};
#endif