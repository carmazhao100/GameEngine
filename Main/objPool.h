/*-------------------------
Author: carmazhao

Date: 2011/12/17

Function: keep the obj alive
in order to save the 
memory
--------------------------*/
#ifndef HEAD_OBJPOOL
#define HEAD_OBJPOOL
#include"sysDef.h"
#include<list>

template <class _T>
class objPool {
private:
	std::list<void *>		_pool;
public:
	objPool() {}
	~objPool(){}
	void * malloc_mem() {
		void * p_t = NULL;

		if(_pool.empty()) {
			p_t = malloc(sizeof(_T));
			memset(p_t , 0 , sizeof(_T));
		}else {
			//lock the mem
			std::list<void *>::iterator it = _pool.begin();
			p_t = *it;
			_pool.pop_front();
		}
		return p_t;
	}	

	void free_mem(void* _p) {
		_pool.push_back(_p);
	}
};
#endif
