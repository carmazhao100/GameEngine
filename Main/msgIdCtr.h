#pragma once
#include "sysDef.h"
#include<vector>


class msgIdCtr {
private:
	//static msgIdCtr * 	h_inst;
	static std::vector<bool> 		m_id_arr;

	msgIdCtr();
public:
	//static msgIdCtr * getInstance();
	static uint_32 dispatch_id();
};

