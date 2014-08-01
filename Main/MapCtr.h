/*===============================
//Author:	carmazhao
//Data:		2012/1/28
//Functoin:	map to deal with info
//			and construct the map
//			
================================*/
#ifndef MAP_CTR_HEAD_
#define	MAP_CTR_HEAD_
#include "sysDef.h"
#include "../GameEngine/Camera.h"
#include"../GameEngine/OptEvent.h"
#include "../GameEngine/Scene.h"
#include "../GameEngine/EventListener.h"
#include "../Resource/Config.h"

//============M A P===========
class MapBlock:public EventListener
{
public:
	MapBlock();
	~MapBlock();

	int_32					get_event_id();
	int_32					get_param(int_32 _id);

	void					set_event_id(int_32	_id);
	void					set_param_arr(std::vector<int_32> _arr);
	void					initial_animation(const int_8*  _name);
protected:
	int_32					m_event_id;
	std::vector<int_32>		m_param_arr;
};
#define ERROR_SPACE		5
class GameMap
{
public:
	GameMap();
	~GameMap();

	uint_32						get_width();
	uint_32						get_height();
	SceneTree*					get_scene_tree();
	int_32						get_map_id();
    std::vector<EventListener*> get_rend_collection(const RECT & _rect);

	void						set_map_width(int_32	_width);
	void						set_map_height(int_32	_height);
	void						set_map_id(int_32	_id);
	void						build_scene(MapConfigInfo* _map_config);
private:
	//about map info
	SceneTree*				m_scene;
	int_32					m_id;
	int_32					m_width;
	int_32					m_height;
};

//============M A P C T R===========
class MapCtr
{
	DEFINE_SINGLE_MODEL(MapCtr)
public:
	~MapCtr();
	//the state
	enum {
		STAY_STATIC = 0,
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT
	};
	enum {
		TEST_MAP = 26
	};
//I N I T I A L     F U N C
	void		initial_role_rect(int_32 _x , int_32 _y);
	void		initial_map(const int_32&	_scene_id ,
							const int_32&	_x ,
							const int_32&	_y);
				
	void		set_camera(int_32 _x , int_32 _y , int_32 _width , int_32 _height);

//E V E N T     D E A L
	bool		deal_event(OptEvent*);
	void		execute_change();
	void		create_map_table();
	
	//get funcs

	Camera		get_camera();
	int_32		get_scene_id();
	std::vector<EventListener*> get_rend_collection();
	RECT		get_role_rect();

	//boundary check
	bool		check_move_2_up();
	bool		check_move_2_down();
	bool		check_move_2_left();
	bool		check_move_2_right();
private:
	MapCtr();

	//about role move
	RECT							m_role_rect;

	Camera							m_camera;
	int_32							m_state;
	//about scene
	GameMap*						m_cur_map;
	std::map<int_32 , GameMap*>		m_map_table;
};
#endif