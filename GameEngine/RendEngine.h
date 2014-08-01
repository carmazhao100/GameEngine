/*===============================
//Author:	carmazhao
//Data:		2011/1/4
//Functoin:	create rending thread
//			
//			
================================*/
#ifndef GRAPH_REND_ENGINE_HEAD_
#define	GRAPH_REND_ENGINE_HEAD_
#include "../Main/sysDef.h"

class RendEngine
{
	DEFINE_SINGLE_MODEL(RendEngine)
public:
	~RendEngine();
	void create_rend_thread();
	friend DWORD WINAPI rev_thread(LPVOID);
private:
	RendEngine();
	void deal_rend();

	HANDLE			m_thread;
};
#endif