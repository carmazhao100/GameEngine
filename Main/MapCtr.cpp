#include "MapCtr.h"
#include "MapConst.h"
#include "../GameEngine/EventListener.h"
#include "../GameEngine/OptEvent.h"
#include "roleUtil.h"

//============M A P===========
MapBlock::MapBlock():EventListener(0,0,0,0,0){
	m_event_id = 0;
}

MapBlock::~MapBlock(){

}

void MapBlock::set_event_id(int_32 _id) {
	m_event_id = _id;
}

void MapBlock::set_param_arr(std::vector<int_32> _arr) {
	m_param_arr = _arr;
}

int_32 MapBlock::get_event_id() {
	return m_event_id;
}

int_32	MapBlock::get_param(int_32 _id) {
	return m_param_arr[_id];
}

void	MapBlock::initial_animation(const int_8 *_name) {
	Animation* _animation= new Animation();
	_animation->add_frame(Config::get_instance()->get_texture(_name));
	m_animation_table[0] = _animation;
	_animation = NULL;
}




GameMap::GameMap(){
	m_scene = new SceneTree();
	m_id = 0;
	m_width = 0;
	m_height = 0;
}

GameMap::~GameMap(){

}

uint_32	GameMap::get_height() {
	return m_height;
}

uint_32	GameMap::get_width() {
	return m_width;
}

int_32	GameMap::get_map_id() {
	return m_id;
}

void	GameMap::set_map_width(int_32 _width) {
	m_width = _width;
}

void	GameMap::set_map_height(int_32	_height){
	m_height = _height;
}

void	GameMap::set_map_id(int_32 _id) {
	m_id = _id;
}
std::vector<EventListener*> GameMap::get_rend_collection(const RECT & _rect) {
	return m_scene->get_rend_collection(_rect);
}

void	GameMap::build_scene(MapConfigInfo* _map_config) {
	RECT					_rect;
	uint_32					_i;
	MapGrid*				_m_grid = NULL;
	MapBlock*				_block = NULL;

	if (m_scene == NULL)
	{
		return ;
	}
	//set the rect
	_rect.left = 0;
	_rect.top = 0;
	_rect.right = _map_config->get_width();
	_rect.bottom = _map_config->get_height();
	//build the tree
	m_scene->build_tree(_rect);
	//initial tree
	_i = 0;
	while (true)
	{
		_m_grid = _map_config->get_map_grid_by_order(_i);
		if(_m_grid == NULL) {
			break;
		}
		//make block
		_block = new MapBlock();
		//set size
		_block->set_x(_m_grid->get_x());
		_block->set_y(_m_grid->get_y());
		_block->set_width(_m_grid->get_width());
		_block->set_height(_m_grid->get_height());
		 
		//set event
		_block->set_event_id(_m_grid->get_event_id());
		_block->set_param_arr(_m_grid->get_param_arr());
		// animation
		_block->initial_animation(_m_grid->get_block_resource_name());

		m_scene->add_block(_block);
		_i++;
	}
}


//============M A P C T R===========
IMPLEMENT_SINGLE_MODEL(MapCtr)

MapCtr::MapCtr() {
	m_state = MapCtr::STAY_STATIC;
	m_cur_map = NULL;
}

MapCtr::~MapCtr(){

}
void	MapCtr::execute_change() {
	RECT				_rect;

	switch (m_state)
	{
	case MapCtr::MOVE_UP:
		if(m_camera.get_camera_y() <= ERROR_SPACE) {
			return ;
		}
		//check the role
		_rect = roleUtil::get_instance()->get_role_rect();
		if (_rect.top > m_role_rect.bottom)
		{
			return ;
		}
		m_camera.move_camera_h(-(MapConst::MAP_SPEED));
		break;
	case MapCtr::MOVE_DOWN:
		if((m_camera.get_camera_y() + m_camera.get_camera_height()) >=  
			(m_cur_map->get_height() - ERROR_SPACE)) {
			return ;
		}
		//check the role
		_rect = roleUtil::get_instance()->get_role_rect();
		if (_rect.bottom < m_role_rect.top)
		{
			return ;
		}
		m_camera.move_camera_h(MapConst::MAP_SPEED);
		break;
	case MapCtr::MOVE_LEFT:
		if(m_camera.get_camera_x() <= ERROR_SPACE) {
			return ;
		}
		//check the role
		_rect = roleUtil::get_instance()->get_role_rect();
		if (_rect.left > m_role_rect.right)
		{
			return ;
		}
		m_camera.move_camera_v(-(MapConst::MAP_SPEED));
		break;
	case MapCtr::MOVE_RIGHT:
		if((m_camera.get_camera_x() + m_camera.get_camera_width()) >=  
			(m_cur_map->get_width() - ERROR_SPACE)) {
			return ;
		}
		//check the role
		_rect = roleUtil::get_instance()->get_role_rect();
		if (_rect.right < m_role_rect.left)
		{
			return ;
		}
		m_camera.move_camera_v(MapConst::MAP_SPEED);
		break;
	case MapCtr::STAY_STATIC:
		break;
	default:
		return ;
	}
}
bool	MapCtr::deal_event(OptEvent * _event) {
	int_32				_state = 0;

	if(_event == NULL) {
		return EventListener::IMPASSABLE;
	}
	
	switch (_event->get_name())
	{
	case OptEvent::KEY_DOWN:   //if the key down msg
		switch (_event->get_key())
		{
		case UP_KEY_MSG:		//up pointer
			m_state	= MapCtr::MOVE_UP;
			break;
		case DOWN_KEY_MSG:		//down pointer
			m_state = MapCtr::MOVE_DOWN;
			break;
		case LEFT_KEY_MSG:		//left pointer
			m_state = MapCtr::MOVE_LEFT;
			break;
		case RIGHT_KEY_MSG:		//right pointer
			m_state = MapCtr::MOVE_RIGHT;
			break;
		default:
			return 0;			//if not care then don't give server msg
		}
		break;
	case OptEvent::KEY_UP:
		switch (_event->get_key())
		{
		case UP_KEY_MSG:		//up pointer
			_state	= MapCtr::MOVE_UP;
			break;
		case DOWN_KEY_MSG:		//down pointer
			_state = MapCtr::MOVE_DOWN;
			break;
		case LEFT_KEY_MSG:		//left pointer
			_state = MapCtr::MOVE_LEFT;
			break;
		case RIGHT_KEY_MSG:		//right pointer
			_state = MapCtr::MOVE_RIGHT;
			break;
		}
		if(_state == m_state) {
			m_state = MapCtr::STAY_STATIC;
		}
		break;
	default:				//if not care then don't give server msg
		return 0;
	}

	return EventListener::PASSABLE;
}

void	MapCtr::initial_map(const int_32&	_scene_id ,
					const int_32&	_x,
					const int_32&	_y) 
{
	//get the scene ini
	//create scene tree
	//set the camera
	m_camera.set_camera_x(_x);
	m_camera.set_camera_y(_y);
}

void	MapCtr::create_map_table() {
	uint_32					_i = 0;
	int_32					_id = 0;
	MapConfigInfo*			_map_config = NULL;
	GameMap*				_g_map = NULL;

	while (true)
	{
		//get map config info
		_map_config = Config::get_instance()->get_map_info_by_order(_i);
		if (_map_config == NULL)
		{
			break;
		}
		//get map id
		_id			= _map_config->get_map_id();

		//create map
		_g_map = new GameMap();

		_g_map->set_map_id(_id);
		_g_map->set_map_width(_map_config->get_width());
		_g_map->set_map_height(_map_config->get_width());

		_g_map->build_scene(_map_config);

		m_map_table[_id] = _g_map;
		_g_map = NULL;
		_i++;
	}
	m_cur_map = m_map_table[MapCtr::TEST_MAP];
}

void MapCtr::set_camera(int_32 _x , int_32 _y , int_32 _width , int_32 _height) {
	m_camera.set_camera_x(_x);
	m_camera.set_camera_y(_y);
	m_camera.set_camera_width(_width);
	m_camera.set_camera_height(_height);
}

std::vector<EventListener*> MapCtr::get_rend_collection() {
	std::vector<EventListener*>					_result;
	if(m_cur_map != NULL) {
		_result = m_cur_map->get_rend_collection(m_camera.get_camera_rect());
	}
	return _result;
}

Camera	MapCtr::get_camera() {
	return m_camera;
}

int_32	MapCtr::get_scene_id() {
	if(m_cur_map == NULL) {
		return -1;
	}
	return m_cur_map->get_map_id();
}

void MapCtr::initial_role_rect(int_32 _x , int_32 _y) {
	m_role_rect.left = _x;
	m_role_rect.top = _y;
	m_role_rect.right = _x + 10;
	m_role_rect.bottom = _y + 10;
}

RECT MapCtr::get_role_rect() {
	return m_role_rect;
}


//==================C H E C K    F U N C T I O N S
bool MapCtr::check_move_2_up(){
	if(m_camera.get_camera_y() <= ERROR_SPACE) {
		return false ;
	}
	return true;
}

bool MapCtr::check_move_2_down(){
	if((m_camera.get_camera_y() + m_camera.get_camera_height()) >=  
		(m_cur_map->get_height() - ERROR_SPACE)) {
			return false;
	}
	return true;
}

bool MapCtr::check_move_2_left(){
	if(m_camera.get_camera_x() <= ERROR_SPACE) {
		return false;
	}
	return true;
}

bool MapCtr::check_move_2_right(){
	if((m_camera.get_camera_x() + m_camera.get_camera_width()) >=  
		(m_cur_map->get_width() - ERROR_SPACE)) {
			return false;
	}
	return true;
}
