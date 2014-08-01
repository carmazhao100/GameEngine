/*===============================
//Author:	carmazhao
//Date:		2011/1/2
//Function:	counting the time	
//			and execute the funcs
//
================================*/
#ifndef GRAPH_TIMER_HEAD_
#define GRAPH_TIMER_HEAD_
#include "../Main/sysDef.h"
#include <vector>

typedef  void (*handle_func)(void *);
class embed_handleUnit{
public:
	uint_32 	m_cur_time;
	uint_32		m_tot_time;
	handle_func 	m_handler;
	void *		m_param;

	void 		check();
	bool operator == (const embed_handleUnit & _unit) {
		if(this->m_handler == _unit.m_handler&&
			this->m_param == _unit.m_param) {
				return true;
		}
		return false;
	}
};

class TimerManager
{
	DEFINE_SINGLE_MODEL(TimerManager)
public:
	~TimerManager();
		
	void			initial_timer();
	void			count_time();
	bool 			add_timer_event(uint_32 interval = 0,		\
										handle_func handle = NULL , \
										void * _param = NULL);	
	void 			remove_timer_event(handle_func);
	void			remove_timer_unit(embed_handleUnit _unit);

private:
	TimerManager();

	std::vector<embed_handleUnit> 	m_handle_unit_arr;
	void			check_funcs();
	uint_32			m_time_note;
	HANDLE			m_thread;
};
#endif