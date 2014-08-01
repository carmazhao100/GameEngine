#include "Config.h"
#include <fstream>
#include <string.h>

/***************G R A D E ***************/
BaseGrid::BaseGrid(const int_32 & _x , 
					const int_32 & _y, 
					const int_32 & _width , 
					const int_32 & _height,
					int_8*		   _name) 
{
	m_x = _x;
	m_y = _y;
	m_width = _width;
	m_height = _height;
	strcpy_s(m_name , _name);
}

BaseGrid::~BaseGrid() {

}

int_32	BaseGrid::get_x() {
	return m_x;
}

int_32	BaseGrid::get_y() {
	return m_y;
}

int_32	BaseGrid::get_width() {
	return	m_width;
}

int_32	BaseGrid::get_height() {
	return m_height;
}

int_8*	BaseGrid::get_name() {
	return m_name;
}

void	BaseGrid::set_x(const int_32 & _x) {
	m_x = _x;
}

void BaseGrid::set_y(const int_32 & _y) {
	m_y = _y;
}

void BaseGrid::set_width(const int_32 & _width) {
	m_width = _width;
}

void BaseGrid::set_height(const int_32 & _height) {
	m_height = _height;
}

void BaseGrid::set_name(int_8* _name) {
	strcpy_s(m_name , _name);
}

//----------------------M A P -------------------------

void MapGrid::set_event_id(int_32 _id) {
	m_event_id = _id;
}

void MapGrid::add_event_param(int_32 _param) {
	m_event_param_arr.push_back(_param);
}

void MapGrid::set_block_resource_name(int_8* _name) {
	m_resource_name = _name;
}

const int_8*	MapGrid::get_block_resource_name() {
	return m_resource_name.c_str();
}

int_32	MapGrid::get_event_id() {
	return m_event_id;
}


std::vector<int_32>  MapGrid::get_param_arr() {
	return m_event_param_arr;
}

//-------------
MapConfigInfo::MapConfigInfo(){
	m_id = 0;
}

MapConfigInfo::~MapConfigInfo(){

}

void MapConfigInfo::add_grid(MapGrid _grid) {
	m_grid_arr.push_back(_grid);
}

MapGrid* MapConfigInfo::get_map_grid_by_order(uint_32 _order) {
	if (m_grid_arr.size() <= _order)
	{
		return NULL;
	}
	return &(m_grid_arr[_order]);
}

void MapConfigInfo::set_name(int_8 * _name) {
	m_name = _name;
}

void MapConfigInfo::set_map_id(int_32 _id) {
	m_id = _id;
}

void MapConfigInfo::set_map_width(int_32	_width){
	m_width = _width;
}

void MapConfigInfo::set_map_height(int_32 _height) {
	m_height = _height;
}

int_32 MapConfigInfo::get_map_id() {
	return m_id;
}

std::string MapConfigInfo::get_map_name() {
	return m_name;
}

int_32		MapConfigInfo::get_width() {
	return m_width;
}

int_32		MapConfigInfo::get_height() {
	return m_height;
}

/***************GRAPH  CONFIG ***************/
IMPLEMENT_SINGLE_MODEL(Config)
//-----------R O L E
int_8*  Config::ROLE_MOVE_UP_1 = "role_move_up_1";
int_8*  Config::ROLE_MOVE_UP_2 = "role_move_up_2";
int_8*  Config::ROLE_MOVE_LEFT_1 = "role_move_left_1";
int_8*  Config::ROLE_MOVE_LEFT_2 = "role_move_left_2";
int_8*  Config::ROLE_MOVE_RIGHT_1 = "role_move_right_1";
int_8*  Config::ROLE_MOVE_RIGHT_2 = "role_move_right_2";
int_8*  Config::ROLE_MOVE_DOWN_1 = "role_move_down_1";
int_8*  Config::ROLE_MOVE_DOWN_2 = "role_move_down_2";

int_8*  Config::ROLE_STATIC_UP = "role_static_up";
int_8*  Config::ROLE_STATIC_DOWN = "role_static_down";
int_8*  Config::ROLE_STATIC_LEFT = "role_static_left";
int_8*  Config::ROLE_STATIC_RIGHT = "role_static_right";

//-----------M A P
int_8*	Config::TEST_MAP_BLOCK_NAME = "block_32";

Config::Config(){

}
Config::~Config(){

}

void	Config::read_image_config(int_8 * _fileName) {
	std::fstream			 _file;
	int_32					 _data;
	PicGrid					 _grade;
	int_8					 _grade_name[MAX_GRADE_NAME];
	FMbitmap				 _fmbmp;

	_file.open(_fileName , std::ios::binary | std::ios::in);
	//clear the array to put in new grade
	m_grad_array.clear();

	//first read the graph file name
	_file.read((int_8 *)(&_data) , sizeof(_data));
	_data = ntohl(_data);
	_file.read(m_graph_file_name , _data);
	m_graph_file_name[_data] = '\0';
	
	//read all the grade information
	while (!_file.eof())
	{
		//read grade name
		if(!_file.read((int_8 *)(&_data) , sizeof(_data))) {
			break;
		}

		_data = ntohl(_data);
		_file.read(_grade_name , _data);
		_grade_name[_data] = '\0';
		_grade.set_name(_grade_name);

		//read x
		_file.read((int_8 *)(&_data) , sizeof(_data));
		_data = ntohl(_data);
		_grade.set_x(_data);

		//read y
		_file.read((int_8 *)(&_data) , sizeof(_data));
		_data = ntohl(_data);
		_grade.set_y(_data);

		//read width
		_file.read((int_8 *)(&_data) , sizeof(_data));
		_data = ntohl(_data);
		_grade.set_width(_data);

		//read height
		_file.read((int_8 *)(&_data) , sizeof(_data));
		_data = ntohl(_data);
		_grade.set_height(_data);

		m_grad_array.push_back(_grade);
	}
	_file.close();
	//read the pic
	_fmbmp = ImageReader::get_instance()->read_image(m_graph_file_name , ImageReader::RGBA_IMG);
	make_textures(_fmbmp);
	ImageReader::get_instance()->release_image();
	DEBUG_SHOW("Config is ready=========");
}

void	Config::make_textures(FMbitmap _fmbmp){
	uint_32					_texId;
	FMbitmap				_cut_fmbmp;

	for (uint_32 i = 0;i < m_grad_array.size() ; i++)
	{
		_cut_fmbmp = get_cut_image(_fmbmp , m_grad_array[i]);
		//generate an OpenGL texture ID for this texture
		glGenTextures(1, &_texId);
		//bind to the new texture ID
		glBindTexture(GL_TEXTURE_2D, _texId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

			//store the texture data for OpenGL use
		glTexImage2D(GL_TEXTURE_2D, 0, _cut_fmbmp.m_format, _cut_fmbmp.m_width, _cut_fmbmp.m_height,
			0, _cut_fmbmp.m_format, GL_UNSIGNED_BYTE, _cut_fmbmp.m_bits);
		
		//store into array
		m_texture_table[m_grad_array[i].get_name()] = _texId;
	}
}

FMbitmap Config::get_cut_image(const FMbitmap & _fmbmp,
								PicGrid  _grade) 
{
	FMbitmap				_res_bmp;
	int_32					_pixel_size = 0;
	uint_8*					_bits (0);
	memset(&_res_bmp , 0 , sizeof(_res_bmp));
	
	// get the pixel size
	if (_fmbmp.m_format == ImageReader::RGBA_IMG)
	{
		_pixel_size = 4;
	}else if(_fmbmp.m_format == ImageReader::RGB_IMG){
		_pixel_size = 3;
	}else{
		return _res_bmp;
	}

	//get the bits
	_bits = new uint_8[ _grade.get_width()* _grade.get_height()* _pixel_size];

	for(int i = 0 ; i <_grade.get_height() ; i++)
		for (int j = 0; j < _grade.get_width() * _pixel_size ; j += _pixel_size)
			for (int m = 0;m < _pixel_size;m++)
			{
				_bits[j + m + i * _grade.get_width() * _pixel_size] = \
					\
				_fmbmp.m_bits[(i + _grade.get_y())*_fmbmp.m_width* _pixel_size + _grade.get_x() * _pixel_size + j + m];
			}
	_res_bmp.m_bits		= _bits;
	_res_bmp.m_format	= _fmbmp.m_format;
	_res_bmp.m_height	= _grade.get_height();
	_res_bmp.m_width	= _grade.get_width();

	return _res_bmp;
}

textureId  Config::get_texture(const int_8 * _name) {
	int a = 0;
	return m_texture_table[_name];
}


/*=========================ABOUT MAP CONFIG========================*/
void Config::read_map_config(int_8 *_fileName) {
	std::fstream			 _file;
	int_32					 _data;
	MapConfigInfo			 _map_info;
	MapGrid					 _grid;
	int_8					 _grid_name[MAX_GRADE_NAME];
	int_8					 _map_name[20];

	_file.open(_fileName , std::ios::binary | std::ios::in);
//first read the name of the map
	_file.read((int_8 *)(&_data) , sizeof(_data));
	_data = ntohl(_data);
	_file.read(_map_name , _data);
	_map_name[_data] = '\0';
	_map_info.set_name(_map_name);
	
//read the map id
	_file.read((int_8 *)(&_data) , sizeof(_data));
	_data = ntohl(_data);
	_map_info.set_map_id(_data);

//read the map width
	_file.read((int_8 *)(&_data) , sizeof(_data));
	_data = ntohl(_data);
	_map_info.set_map_width(_data);

//read the map height 
	_file.read((int_8 *)(&_data) , sizeof(_data));
	_data = ntohl(_data);
	_map_info.set_map_height(_data);

//begin to read map blocks
	while (!_file.eof())
	{
	//read grade name
		if(!_file.read((int_8 *)(&_data) , sizeof(_data))) {
			break;
		}

		_data = ntohl(_data);
		_file.read(_grid_name , _data);
		_grid_name[_data] = '\0';
		_grid.set_block_resource_name(_grid_name);
	//read the grid size
		//read x
		_file.read((int_8 *)(&_data) , sizeof(_data));
		_data = ntohl(_data);
		_grid.set_x(_data);

		//read y
		_file.read((int_8 *)(&_data) , sizeof(_data));
		_data = ntohl(_data);
		_grid.set_y(_data);

		//read width
		_file.read((int_8 *)(&_data) , sizeof(_data));
		_data = ntohl(_data);
		_grid.set_width(_data);

		//read height
		_file.read((int_8 *)(&_data) , sizeof(_data));
		_data = ntohl(_data);
		_grid.set_height(_data);
	//read event id
		_file.read((int_8 *)(&_data) , sizeof(_data));
		_data = htonl(_data);
		_grid.set_event_id(_data);
	//read param
		_data = 0;
		while (true)
		{
			_file.read((int_8 *)(&_data) , sizeof(_data));
			_data = ntohl(_data);

			if(_data == -1){
				break;
			}
			_grid.add_event_param(_data);
		}	
		_map_info.add_grid(_grid);
	}
	_file.close();
	m_map_table.push_back( _map_info);
}



MapConfigInfo*	Config::get_map_info_by_order(uint_32 _order) {
	if (_order >= m_map_table.size())
	{
		return NULL;
	}
	return &(m_map_table[_order]);
}

