#ifndef SYS_DEFINE_HEAD_
#define SYS_DEFINE_HEAD_


#define DEBUG_MODE_
//sys
#include <windows.h>

//std
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

//objpool
#include "objPool.h"

//opengl
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>

//needed lib
//net lib
#pragma comment(lib , "ws2_32.lib")
//opengl lib
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "GLAUX.LIB")
//free image lib
#pragma comment(lib , "FreeImage.lib")

//---ecapsulate the data kind
typedef long long               int_64;
typedef unsigned long long      uint_64;
typedef unsigned int            uint_32;
typedef int 					int_32;
typedef unsigned short			uint_16;
typedef short 					int_16;
typedef unsigned char 			uint_8;
typedef char 					int_8;

//---debug
#ifdef DEBUG_MODE_
#define DEBUG_SHOW(_STR) printf("DEBUG MODE : %s\n" , _STR);
#else
#define DEBUG_SHOW 
#endif

//---the error code
//SOCKET ERROR
#define			INITIAL_SOCKE_ERROR		10001
#define			CREATE_SOCKET_ERROR		10002
#define			SOCKET_CONNECT_ERROR	10003

#define			SOCKET_SEND_MSG_ERROR	10004
#define			SOCKET_REV_MSG_ERROR	10005

//THREAD_ERROR
#define			CREATE_THREAD_ERROR		20001


//define the message 
#define			GAME_MSG_KEY_DOWN				WM_KEYDOWN
#define			GAME_MSG_KEY_UP					WM_KEYUP
#define			GAME_MSG_LEFT_MOUSE_DOWN		WM_LBUTTONDOWN
#define			GAME_MSG_LEFT_MOUSE_UP			WM_LBUTTONUP
#define			GAME_MSG_RIGHT_MOUSE_DOWN		WM_RBUTTONDOWN
#define			GAME_MSG_RIGHT_MOUSE_UP			WM_RBUTTONUP
#define			GAME_MSG_MOUSE_MOVE				WM_MOUSEMOVE
//define the ascii
#define			UP_KEY_MSG					VK_UP
#define			DOWN_KEY_MSG				VK_DOWN
#define			LEFT_KEY_MSG				VK_LEFT
#define			RIGHT_KEY_MSG				VK_RIGHT

//define the single instance pattern
#define DEFINE_OBJ_POOL(_T) private:\
	static objPool<_T> _pool;\
				public:\
				void* operator new (size_t size) {return _pool.malloc_mem();}\
				void operator delete(void* p) {_pool.free_mem(p);}
#define IMPLEMENT_OBJ_POOL(_T) objPool<_T> _T::_pool;

#define DEFINE_SINGLE_MODEL(_T)	private:\
	static _T * h_inst;\
				public:\
				static _T * get_instance();

#define IMPLEMENT_SINGLE_MODEL(_T) 	_T * _T::h_inst(NULL);\
	_T * _T::get_instance() {\
	if(h_inst == NULL) {\
	h_inst = new _T();\
	}\
	return h_inst;\
}
//define the copy mem
#define COPY_FROM_MEM(_target,_mem)  memcpy(&_target , _mem , sizeof(_target));\
	_mem += sizeof(_target);
#endif