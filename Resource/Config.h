/*===============================
//Author:	carmazhao
//Data:		2011/17
//Functoin:	read the config file
//			of the pictures
//			
================================*/
#ifndef GRAPH_CONFIG_HEAD_
#define GRAPH_CONFIG_HEAD_
#include "../Main/sysDef.h"
#include "ImageReader.h"
#include "../Main/sysDef.h"
#include <vector>
#include <map>
#include <string>

#ifndef MAX_GRADE_NAME  
	#define	MAX_GRADE_NAME	50
#endif
class BaseGrid
{
public:
	BaseGrid(const int_32 & _x = 0,
			 const int_32 & _y = 0,
			 const int_32 & _width = 0,
			 const int_32 & _height = 0,
			 int_8 *		_name = "");
	~BaseGrid();

	int_32		get_x();
	int_32		get_y();
	int_32		get_width();
	int_32		get_height();
	int_8*		get_name();

	void		set_x(const int_32 & _x);
	void		set_y(const int_32 & _y);
	void		set_width(const int_32 & _width);
	void		set_height(const int_32 & _height);
	void		set_name(int_8* _name);
protected:
	int_32		m_x;	
	int_32		m_y;		
	int_32		m_width;
	int_32		m_height;
	int_8		m_name[MAX_GRADE_NAME];
};
//----------------------P I C G R A D E-------------------------
class PicGrid:public BaseGrid
{
public:
protected:
};
//----------------------M A P -------------------------
class MapGrid:public BaseGrid
{
public:	
	void				set_event_id(int_32  _id);
	void				add_event_param(int_32 _param);
	void				set_block_resource_name(int_8* _name);

	int_32				get_event_id();
	std::vector<int_32>	get_param_arr();
	const int_8*		get_block_resource_name();
protected:
	std::string						m_resource_name;
	int_32						m_event_id;				//event id
	std::vector<int_32>			m_event_param_arr;		//arr of event param 
};

class MapConfigInfo
{
public:
	void		add_grid(MapGrid _grid);
	void		set_name(int_8 * _name);
	void		set_map_id(int_32	_id);
	void		set_map_width(int_32	_width);
	void		set_map_height(int_32	_height);

	int_32		get_map_id();
	std::string	get_map_name();	
	int_32		get_width();
	int_32		get_height();
	MapGrid*	get_map_grid_by_order(uint_32 _order);

	MapConfigInfo();
	~MapConfigInfo();

protected:
	std::string					m_name;					//name of map
	int_32						m_id;					//id of map
	int_32						m_width;				//width of map
	int_32						m_height;				//height of map
	std::vector<MapGrid>		m_grid_arr;				//arr of grids of the map
};


#ifndef MAX_GRAPH_FILE_NAME
#define	MAX_GRAPH_FILE_NAME	100
#endif
typedef	uint_32		textureId;


class Config
{
	DEFINE_SINGLE_MODEL(Config)
public:
	~Config();
//-------------about R O L E
	static int_8* ROLE_MOVE_UP_1 ;
	static int_8* ROLE_MOVE_UP_2 ;
	static int_8* ROLE_MOVE_LEFT_1 ;
	static int_8* ROLE_MOVE_LEFT_2 ;
	static int_8* ROLE_MOVE_RIGHT_1 ;
	static int_8* ROLE_MOVE_RIGHT_2;
	static int_8* ROLE_MOVE_DOWN_1 ;
	static int_8* ROLE_MOVE_DOWN_2;

	static int_8* ROLE_STATIC_UP ;
	static int_8* ROLE_STATIC_DOWN;
	static int_8* ROLE_STATIC_LEFT ;
	static int_8* ROLE_STATIC_RIGHT;
//-------------about  M A P
	static int_8* TEST_MAP_BLOCK_NAME;
private:
	Config();
/*=========================ABOUT IMAGE CONFIG========================*/
public:
	void		read_image_config(int_8 * _fileName);
	textureId	get_texture(const int_8 * _name);
private:
	std::vector<PicGrid>						m_grad_array;
	int_8										m_graph_file_name[MAX_GRAPH_FILE_NAME];
	std::map<std::string ,textureId>			m_texture_table;
			
	
	FMbitmap		get_cut_image(const FMbitmap & _fmbmp , PicGrid  _grade);
	void			make_textures(FMbitmap _fmbmp);
/*=========================ABOUT MAP CONFIG========================*/
private:
	std::vector<MapConfigInfo>	m_map_table;
public:
	void					read_map_config(int_8* _fileName);
	MapConfigInfo*			get_map_info_by_order(uint_32 _order);
};
#endif