/*===============================
//Author:	carmazhao
//Data:		2011/1/2
//Functoin:	create window and render
//			objs
//
================================*/
#ifndef G_WINDOW_HEAD_
#define G_WINDOW_HEAD_
#include "../Main/sysDef.h"
#include "OptEvent.h"



class GWindow
{
	DEFINE_SINGLE_MODEL(GWindow)
public:
	~GWindow();
	
	bool		initial_window(int_8* _title , 
								int_32 _x ,
								int_32 _y ,
								int_32 _width , 
								int_32 _height , 
								bool _flag , 
								int_32 _bits = 16);
	void		game_loop();
	void		set_fps(uint_32);

	//get funcs
	HWND		get_hwnd();
	int_32		get_window_width();
	int_32		get_window_height();
	HDC			get_dc();

	//functional
	void		rend();
	void		resize_window(int_32 _width,int_32 _height);
private:
	GWindow();
	//about size
	int_32		m_width;
	int_32		m_height;
	int_32		m_x;
	int_32		m_y;
	bool		m_fullscreen;
	//about control
	HWND		m_hwnd;	
	HDC			m_dc;			//device context
	HGLRC		m_rc;			//rending context
	HINSTANCE	m_instance;
	//about rending
	uint_32		m_fps;

	//funcs
	void		kill_window();
	bool		init_gl();
};
#endif