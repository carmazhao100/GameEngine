#include "RendEngine.h"

IMPLEMENT_SINGLE_MODEL(RendEngine)

RendEngine::RendEngine() {

}

RendEngine::~RendEngine() {

}

static DWORD WINAPI rev_thread(LPVOID _lpParameter) {
	(static_cast<RendEngine*>(_lpParameter))->deal_rend();
	return 0;
}
void RendEngine::create_rend_thread(){
	m_thread = CreateThread(NULL , 0 , rev_thread , (LPVOID)this , 0 , NULL);
}

void RendEngine::deal_rend() {
	while(true) {

	}
}