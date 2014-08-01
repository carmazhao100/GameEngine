/*===============================
//Author:	carmazhao
//Data:		2011/1/4
//Functoin:	control the screen
//			to show the map
//			
================================*/
#ifndef GRAPH_CAMERA_HEAD_
#define	GRAPH_CAMERA_HEAD_
#include "../Main/sysDef.h"

class Camera
{
public:
	Camera();
	~Camera();

	uint_32		get_camera_x();
	uint_32		get_camera_y();
	uint_32		get_camera_width();
	uint_32		get_camera_height();
	RECT		get_camera_rect();

	void		set_camera_x(const uint_32 &);
	void		set_camera_y(const uint_32 &);
	void		set_camera_width(const uint_32 &);
	void		set_camera_height(const uint_32 &);

	void		move_camera_h(const int_32	&);
	void		move_camera_v(const int_32	&);
private:

	uint_32		m_x;		//x coordinate in map
	uint_32		m_y;		//y coordinate in map
	uint_32		m_width;	//width of the visible area
	uint_32		m_height;	//height of the visible area
};
#endif