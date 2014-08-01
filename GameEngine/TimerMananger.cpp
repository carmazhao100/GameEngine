#include "TimerManager.h"
#include "../Msg/engine.h"

IMPLEMENT_SINGLE_MODEL(TimerManager)

TimerManager::TimerManager(){
	m_time_note = 0;
}

TimerManager::~TimerManager() {

}

DWORD WINAPI helper_count_time(LPVOID _lpParameter) {
	(static_cast<TimerManager*>(_lpParameter))->count_time();
	return 0;
}
//
void TimerManager::initial_timer() {
	m_thread = CreateThread(NULL , 0 , helper_count_time , (LPVOID)this , 0 , NULL);
	if ( m_thread == NULL ){
		std::cout<<"Create Thread Failed!"<<std::endl;
	}
}
void TimerManager::count_time() {
	uint_32			_cur_time = 0;

	while (true)
	{
		_cur_time = GetTickCount();
		if(_cur_time - m_time_note >= 10) {
			m_time_note = _cur_time;
			check_funcs();
		}
		engine::get_instance()->dispatcher();
	}
}

void TimerManager::check_funcs(){
	//execute the functions
	uint_32		i = 0;
	for(;i < m_handle_unit_arr.size();i++) {	
		m_handle_unit_arr[i].check();
	} 
}

bool TimerManager::add_timer_event(uint_32		_inter,
								   handle_func  _handler , 
								   void *		_param) 
{
	embed_handleUnit 	_unit;
	uint_32				i = 0;

	_unit.m_cur_time = 0;
	_unit.m_tot_time = _inter /10;
	_unit.m_handler = _handler;
	_unit.m_param = _param;


	m_handle_unit_arr.push_back(_unit);
	return true;
}

void TimerManager::remove_timer_event(handle_func _handler) {
	uint_32		i = 0;

	for(;i < m_handle_unit_arr.size();i++) {
		if(m_handle_unit_arr[i].m_handler == _handler) {
			m_handle_unit_arr.erase(m_handle_unit_arr.begin() + i);	
		}
	}
}

void TimerManager::remove_timer_unit(embed_handleUnit _unit) {
	uint_32		i = 0;

	for(;i < m_handle_unit_arr.size();i++) {
		if(m_handle_unit_arr[i] == _unit) {
			m_handle_unit_arr.erase(m_handle_unit_arr.begin() + i);	
		}
	}
}
/********************EMBED_HANDLEUNIT****************************/
void embed_handleUnit::check(){
	if(m_cur_time >= m_tot_time) {	
		if(m_handler != NULL) {
			(*m_handler)(m_param);
		}
		m_cur_time = 0;
	}else{
		m_cur_time++;
	}
}
