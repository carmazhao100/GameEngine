/*==========================================
/!Author:	carmazhao
/!Date:		2012/1/9
/!Function:	control the heart beat and keep
		    the connection
===========================================*/
#ifndef HEART_BEATER_HEAD_
#define HEART_BEATER_HEAD_
#include "sysDef.h"
#include "../GameEngine/TimerManager.h"

#define  HEART_BEAT_TIME_OUT_S	2
class HeartBeater
{
	DEFINE_SINGLE_MODEL(HeartBeater)
public:
	HeartBeater();
	~HeartBeater();
		
	void		start_heart_beat();				//add the timer
	void		beat();							//beat to give server info
	void		get_beat_frome_server();		//get the beat info from server
	void		check_time_out();				//check the time out 
private:
	uint_32				m_count;				//count the seconds before the next beat
};
#endif