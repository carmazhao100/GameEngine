/*===============================
//Author:	carmazhao
//Data:		2011/1/3
//Functoin:	the basic objs to display
//			
//
================================*/
#ifndef DISPLAY_OBJECT_HEAD_
#define	DISPLAY_OBJECT_HEAD_
#include "../Main/sysDef.h"
#include "Object.h"
#include "Animation.h"
#include <map>


class DisplayObject:public Object
{
public:
	DisplayObject(int_32   _x , 
		int_32 			_y , 
		int_32 			_depth,
		int_32 			_width,
		int_32 			_height);
	DisplayObject(const DisplayObject & _dis_obj);
	virtual ~DisplayObject();
	virtual	 void	draw(const int_32 & _std_x = 0 , //begin pos_x
						 const int_32 & _std_y = 0); //begin pos_y
	virtual	 Animation*	get_animation();
	virtual	 void		stop_animation();
	virtual  void		play_animation();

	//================GET FUNCTIONS
	uint_32				get_an_state()const;

	//================SET FUNCTIONS
	void				set_an_state(const uint_32 & _state);
	void				add_animation(int_32 _id , Animation * _animation);
	std::map<int_32 , Animation *>  get_an_table()const;
protected:
	std::map<int_32 , Animation *>   m_animation_table;
	uint_32							 m_an_state;
};
#endif