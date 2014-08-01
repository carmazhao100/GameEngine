#include "GWindow.h"
#include "TimerManager.h"
#include "../Msg/engine.h"
#include "../Resource/Config.h"
#include "OptEvent.h"
#include "OptEventCtr.h"
#include "Render.h"



IMPLEMENT_SINGLE_MODEL(GWindow)

GWindow::GWindow() {

}

GWindow::~GWindow(){

}


LRESULT CALLBACK WndProc( HWND hWnd, 
						 UINT uMsg, 
						 WPARAM wParam, 
						 LPARAM lParam) {
		OptEvent*				_opt_event = NULL;

		switch (uMsg) {
		case GAME_MSG_LEFT_MOUSE_DOWN:
			_opt_event = new OptEvent(OptEvent::LEFT_MOUSE_DOWN , hWnd , wParam , lParam);
			break;
		case GAME_MSG_LEFT_MOUSE_UP:
			_opt_event = new OptEvent(OptEvent::LEFT_MOUSE_UP , hWnd , wParam , lParam);
			break;
		case GAME_MSG_RIGHT_MOUSE_DOWN:
			_opt_event = new OptEvent(OptEvent::RIGHT_MOUSE_DOWN , hWnd , wParam , lParam);
			break;
		case GAME_MSG_RIGHT_MOUSE_UP:
			_opt_event = new OptEvent(OptEvent::RIGHT_MOUSE_UP , hWnd , wParam , lParam);
			break;
		case GAME_MSG_KEY_DOWN:
			_opt_event = new OptEvent(OptEvent::KEY_DOWN , hWnd , wParam , lParam);
			break;
		case GAME_MSG_KEY_UP:
			_opt_event = new OptEvent(OptEvent::KEY_UP , hWnd , wParam , lParam);
			break;
		case GAME_MSG_MOUSE_MOVE:
			_opt_event = new OptEvent(OptEvent::MOUSE_MOVE , hWnd , wParam , lParam);
			break;
		case WM_SIZE:
			GWindow::get_instance()->resize_window(LOWORD(lParam),HIWORD(lParam)); 
			break;
		case WM_CLOSE:{
			DestroyWindow(GWindow::get_instance()->get_hwnd());		
			break;
					  }
		case WM_DESTROY:{
			PostQuitMessage(0);
			break;;
						}					
		default:
			return DefWindowProc(hWnd,uMsg,wParam,lParam);
		}
		if (_opt_event == NULL)
		{
			return 0;
		}
		OptEventCtr::get_instance()->dispatch_event(_opt_event);
		if(_opt_event != NULL) {
			delete _opt_event;
		}
		return 0;
}



bool	GWindow::initial_window(int_8 *_title, \
								int_32 _x, \
								int_32 _y, \
								int_32 _width, \
								int_32 _height, \
								bool   _flag, \
								int_32 _bits) {
									//赋值
									m_y = _y;
									m_x = _x;
									m_width = _width;
									m_height = _height;
									//像素格式！
									GLuint PixelFormat;//type GLuint = DWord;
									WNDCLASS wc;
									//窗体风格
									DWORD dwExStyle;
									DWORD dwStyle;
									//是否全屏
									m_fullscreen=_flag;
									//窗口的各种性质
									m_instance = GetModuleHandle(NULL);
									wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
									wc.lpfnWndProc = (WNDPROC) WndProc;
									wc.cbClsExtra = 0;
									wc.cbWndExtra = 0;
									wc.hInstance = m_instance;
									wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
									wc.hCursor = LoadCursor(NULL, IDC_ARROW);
									wc.hbrBackground = NULL;
									wc.lpszMenuName = NULL;
									wc.lpszClassName = TEXT("game"); 
									//注册窗口
									if(!RegisterClass(&wc)){
										MessageBox(NULL,TEXT("Failed To Register The Window Class."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
										return FALSE;  
									}
									//查看关于全屏的信息
									if(m_fullscreen){
										DEVMODE  dmScreenSettings;
										memset(&dmScreenSettings,0,sizeof(dmScreenSettings));
										dmScreenSettings.dmSize=sizeof(dmScreenSettings);
										dmScreenSettings.dmPelsWidth=_width;
										dmScreenSettings.dmPelsHeight=_height;
										dmScreenSettings.dmBitsPerPel=_bits;//每像素所选的色彩浓度
										dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
										//如果全屏转换不成功
										if(ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL){
											if (MessageBox(NULL,TEXT("The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?"),TEXT("NeHe GL"),MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
												m_fullscreen=false;
											else{
												MessageBox(NULL,TEXT("Program Will Now Close."),TEXT("ERROR"),MB_OK|MB_ICONSTOP);
												return FALSE;
											}
										}
									}
									//因为全屏可能不成功并且用户选择窗口
									if(m_fullscreen){
										dwExStyle=WS_EX_APPWINDOW;//保证窗口在前端
										dwStyle=WS_POPUP;//消掉窗口边缘
									}
									else{
										dwExStyle=WS_EX_WINDOWEDGE|WS_EX_APPWINDOW ;//后面的东西增强3d观感
										dwStyle=WS_OVERLAPPEDWINDOW;
									}
									
									if(!(m_hwnd=CreateWindowEx(dwExStyle,TEXT("game"),TEXT("fishMoon"),(dwStyle|WS_CLIPCHILDREN|WS_CLIPSIBLINGS),m_x,m_y,m_width,m_height,NULL,NULL,m_instance,NULL))){
										kill_window();
										MessageBox(NULL,TEXT("Window Creation Error."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
										return false;
									}
									//记录像素格式
									static PIXELFORMATDESCRIPTOR pfd={
										sizeof(PIXELFORMATDESCRIPTOR),
										1,
										PFD_DRAW_TO_WINDOW |
										PFD_SUPPORT_OPENGL |
										PFD_DOUBLEBUFFER,
										PFD_TYPE_RGBA,
										_bits,
										0, 0, 0, 0, 0, 0,
										0,
										0,
										0,
										0, 0, 0, 0,
										16,
										0,
										0,
										PFD_MAIN_PLANE,
										0,
										0, 0, 0
									};
									//下面获得设备描述表
									if(!(m_dc=GetDC(m_hwnd))){
										kill_window();                                                              // 重置显示区
										MessageBox(NULL,TEXT("Can't Create A GL Device Context."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
										return FALSE; 
									}
									//找到一个与设备结合的符合前述像素信息的像素
									if(!(PixelFormat=ChoosePixelFormat(m_dc,&pfd))){
										kill_window();                                                             // 重置显示区
										MessageBox(NULL,TEXT("Can't Find A Suitable PixelFormat."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
										return FALSE;
									}
									//设置像素
									if(!SetPixelFormat(m_dc,PixelFormat,&pfd)){
										kill_window();                                                             // 重置显示区
										MessageBox(NULL,TEXT("Can't Set The PixelFormat."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
										return FALSE;  
									}
									//分配色彩描述表
									if(!(m_rc=wglCreateContext(m_dc))){
										kill_window();                                                             // 重置显示区
										MessageBox(NULL,TEXT("Can't Create A GL Rendering Context."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
										return FALSE; 
									}
									//激活色彩描述表 
									if(!wglMakeCurrent(m_dc,m_rc)){
										kill_window();                                                             // 重置显示区
										MessageBox(NULL,TEXT("Can't Activate The GL Rendering Context."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
										return FALSE;  
									}
									//一切顺利~下面造窗口
									ShowWindow(m_hwnd,SW_SHOW);
									SetForegroundWindow(m_hwnd);
									SetFocus(m_hwnd);
									if(!init_gl()){
										kill_window();                                                             // 重置显示区
										MessageBox(NULL,TEXT("Initialization Failed."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
										return FALSE; 
									}
									return true;
}

void GWindow::kill_window(){
	if(m_fullscreen){
		ChangeDisplaySettings(NULL,0);//使用注册表默认值来装换到桌面
	}
	if(m_rc){
		if(!wglMakeCurrent(m_dc,m_rc)){//???????????????????????????????????????????
			MessageBox(NULL,TEXT("Release Of DC And RC Failed."),TEXT("SHUTDOWN ERROR"),MB_OK | MB_ICONINFORMATION);
		}
	}
	if(!wglDeleteContext(m_rc)){
		MessageBox(NULL,TEXT("Release Rendering Context Failed."),TEXT("SHUTDOWN ERROR"),MB_OK | MB_ICONINFORMATION);
		m_rc=NULL;
	}
	if(m_dc&&!ReleaseDC(m_hwnd,m_dc)){
		MessageBox(NULL,TEXT("Release Device Context Failed."),TEXT("SHUTDOWN ERROR"),MB_OK | MB_ICONINFORMATION);
		m_dc=NULL;
	}
	if(m_hwnd&&!DestroyWindow(m_hwnd)){
		MessageBox(NULL,TEXT("Could Not Release hWnd."),TEXT("SHUTDOWN ERROR"),MB_OK | MB_ICONINFORMATION);
		m_hwnd=NULL;
	}
	if(!UnregisterClass(TEXT("game"),m_instance)){
		MessageBox(NULL,TEXT("Could Not Unregister Class."),TEXT("SHUTDOWN ERROR"),MB_OK | MB_ICONINFORMATION);
		m_instance=NULL;
	}
}

void GWindow::resize_window(int_32 width,int_32 height){
	if(height==0){
		height=1;
	}
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);//选择投影矩阵
	glLoadIdentity();//重置投影矩阵
	
	glMatrixMode(GL_MODELVIEW);//模型矩阵
	glLoadIdentity();//重置模型矩阵
}

bool GWindow::init_gl(GLvoid){
	glEnable(GL_TEXTURE_2D); // 启用纹理映射
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClearDepth(1.0f);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);//真正精细的透视修正

	return true;
}

void GWindow::game_loop() {
	MSG msg; 
	BOOL done=FALSE;
	while(!done){
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if(msg.message==WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Render::get_instance()->check_rend();
		//rend();
		//TimerManager::get_instance()->count_time();
		//check if there is net message
		//engine::get_instance()->dispatcher();
		Sleep(5);
	}
}

void GWindow::rend(){
	
}

/*************GET FUNCTIONS**********************/
HWND GWindow::get_hwnd() {
	return m_hwnd;
}

int_32 GWindow::get_window_height() {
	return m_height;
}

int_32	GWindow::get_window_width() {
	return m_width;
}

HDC		GWindow::get_dc() {
	return m_dc;
}

/*************HELPER FUNCTIONS**********************/
void help_rend(void* _p) {
	(static_cast<GWindow*>(_p))->rend();
	return ;
}


/*************SET FUNCTIONS**********************/
void GWindow::set_fps(uint_32 _fps) {
	/*uint_32			_inter = 0;

	m_fps = _fps;
	_inter = 1000/m_fps;
	DEBUG_SHOW("fps set ok=========");
	TimerManager::get_instance()->add_timer_event(_inter , help_rend , this);*/
}

