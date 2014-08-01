/*===============================
//Author:	carmazhao
//Data:		2011/2/7
//Functoin: to store rend obj and 
//			draw them
//
================================*/
#ifndef RENDER_HEAD_
#define RENDER_HEAD_
#include "../Main/sysDef.h"
#include "BaseUi.h"
#include "EventListener.h"
#include <vector>

class Render
{
	DEFINE_SINGLE_MODEL(Render)
public:
	~Render();
	void rend();

	void set_role(EventListener* _p);
	void set_fps(const uint_32 & _fps);

	void check_rend();
private:
	Render();

	EventListener*					m_role_p;
	std::vector<BaseUi*>			m_ui_arr;
	std::vector<EventListener*>		m_other_players; 
	//count the fps
//	uint_32 	m_cur_time;
	uint_32		m_tot_time;
	uint_32		m_old_time;
};
#endif