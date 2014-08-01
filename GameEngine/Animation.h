/*===============================
//Author:	carmazhao
//Data:		2011/1/3
//Functoin:	the animation unit of
//			every object
//
================================*/
#ifndef ANIMATION_HEAD_
#define	ANIMATION_HEAD_
#include "../Main/sysDef.h"
#include <vector>

class Animation
{
public:
	Animation();
	~Animation();
	Animation(const Animation & _animation);

	void		add_frame(const GLuint &);
	void		play();
	void		stop();
	GLuint		get_frame();
	void		set_fps(const uint_32 & _fps);

	//get functions 
	std::vector<GLuint>			get_frames()const;
	uint_32						get_current_pos()const;
	uint_32						get_fps()const;

	// helpers
	friend	void help_play(void *);
private:
	std::vector<GLuint>			m_frames;		//store the texture id 
	uint_32						m_cur_pos;		//store the current frame id
	uint_32						m_fps;			//frames per second

	void		go_to_next_frame();
};

#endif