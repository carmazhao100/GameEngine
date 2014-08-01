#include "BaseUi.h"
#include "OptEventCtr.h"

BaseUi::BaseUi(int_32   _x , 
			   int_32 			_y  , 
			   int_32 			_depth  ,
			   int_32 			_width ,
			   int_32 			_height):EventListener(_x ,_y ,_depth , _width , _height){
	OptEventCtr::get_instance()->add_ui_listener(this);
}

BaseUi::~BaseUi(){
	OptEventCtr::get_instance()->remove_ui_listener(this);
}