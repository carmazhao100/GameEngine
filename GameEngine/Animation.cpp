#include "Animation.h"
#include "TimerManager.h"

//helpers
void	help_play (void * _p) {
	(static_cast<Animation*>(_p))->go_to_next_frame();
}

Animation::Animation(const Animation &_animation) {
	m_frames = _animation.get_frames();
	m_fps = _animation.get_fps();
	m_cur_pos = _animation.get_current_pos();
}

Animation::Animation(){
	m_frames.clear();
	m_cur_pos = 0;
	m_fps	  = 24;
}

Animation::~Animation() {
	embed_handleUnit			_unit;

	_unit.m_param = this;
	_unit.m_handler = help_play;
	TimerManager::get_instance()->remove_timer_unit(_unit);
	m_frames.clear();
}

void Animation::add_frame(const GLuint & _frame) {
	m_frames.push_back(_frame);
}

void Animation::play(){
	if(m_fps == 0) {
		return ;
	}
	uint_32			_inter = 1000/m_fps;
	TimerManager::get_instance()->add_timer_event(_inter , help_play , this);
}

void Animation::stop(){
	embed_handleUnit			_unit;

	_unit.m_param = this;
	_unit.m_handler = help_play;
	TimerManager::get_instance()->remove_timer_unit(_unit);
}

void Animation::go_to_next_frame(){
	if (m_frames.empty()){
		return;
	}
	m_cur_pos = (m_cur_pos + 1)%m_frames.size();
}

GLuint Animation::get_frame() {
	if(m_frames.empty()) {
		return -1;
	}
	return m_frames[m_cur_pos];
}

void  Animation::set_fps(const uint_32 & _fps){
		if (_fps == 0)
		{
			return;
		}
		m_fps = _fps;
}


std::vector<GLuint>		Animation::get_frames() const{
	return m_frames;
}

uint_32					Animation::get_current_pos()const  {
	return	m_cur_pos;
}

uint_32					Animation::get_fps() const {
	return m_fps;
}
