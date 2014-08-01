#include "HeartBeater.h"
#include "HeartBeatProxy.h"

IMPLEMENT_SINGLE_MODEL(HeartBeater)

HeartBeater::HeartBeater() {
	m_count = 0;
}

HeartBeater::~HeartBeater(){

}

//helper function
void help_beat(void * _p) {
	(static_cast<HeartBeater*>(_p))->beat();
}
void help_count_time_out(void * _p) {
	(static_cast<HeartBeater*>(_p))->check_time_out();
}

void HeartBeater::start_heart_beat(){
	TimerManager::get_instance()->add_timer_event(1000 , help_beat , this);
	TimerManager::get_instance()->add_timer_event(1000 , help_count_time_out , this);
}

// send beat msg to the server
void HeartBeater::beat(){
DEBUG_SHOW("BEAT");
	HeartBeatProxy				_proxy;

	_proxy.send_beat_to_server();
}

//get beat from server to keep connection
void HeartBeater::get_beat_frome_server(){
	m_count = 0;
}

//check if the connection is on
void HeartBeater::check_time_out() {
	if(m_count >= HEART_BEAT_TIME_OUT_S) {
		printf("time out\n");
	}else {
		m_count++;
	}
}