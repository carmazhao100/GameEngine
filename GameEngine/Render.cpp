#include "Render.h"
#include "../Main/MapCtr.h"
#include "../Main/PlayersCtr.h"
#include "GWindow.h"
//main
#include "../Main/MapCtr.h"
#include "../Main/role.h"
#include "../Main/PlayersCtr.h"
IMPLEMENT_SINGLE_MODEL(Render)

Render::Render(){
	m_role_p = NULL;
	//m_cur_time = 0;
	m_tot_time = 0;
	m_old_time = 0;
}

Render::~Render(){

}

void	Render::rend() {
//set opengl================================================
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glOrtho(0,GWindow::get_instance()->get_window_width(),
		GWindow::get_instance()->get_window_height(),
		0,-0.1,0.1);

	glEnable(GL_TEXTURE_2D);
//do the change==============================================
	MapCtr::get_instance()->execute_change();
	role::get_instance()->execute_change();
	PlayersCtr::get_instance()->execute_change();

//do rend=================================================
	uint_32			i = 0;
	uint_32			j = 0;
	//rend map
	std::vector<EventListener*>		_collection;
	_collection = MapCtr::get_instance()->get_rend_collection();
	for (uint_32 i = 0;i < _collection.size();i++)
	{
		_collection[i]->draw(MapCtr::get_instance()->get_camera().get_camera_x(),
		MapCtr::get_instance()->get_camera().get_camera_y());
	}
	
	//rend npcs 
	//rend role
	if(m_role_p != NULL) {
		m_role_p->draw();
	}

	//rend other players
	PlayersCtr::get_instance()->draw();
	//rend ui
	for (;i < m_ui_arr.size();i++)
	{
		if(m_ui_arr[i] != NULL) {
			m_ui_arr[i]->draw(MapCtr::get_instance()->get_camera().get_camera_x(),
								MapCtr::get_instance()->get_camera().get_camera_y());
		}
	}
	SwapBuffers(GWindow::get_instance()->get_dc());
}

void	Render::set_role(EventListener *_p) {
	m_role_p = _p;
}

void	Render::set_fps(const uint_32 & _fps) {
	m_tot_time = 1000 / _fps;
}

void	Render::check_rend() {
	uint_32			_cur_time = 0;

	_cur_time = GetTickCount();
	if(_cur_time - m_old_time >= m_tot_time) {
		m_old_time = _cur_time;
		rend();
	}
	/*if(m_cur_time >= m_tot_time) {	
		rend();
		m_cur_time = 0;
	}else{
		m_cur_time++;
	}*/
}