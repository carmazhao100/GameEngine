#include "Scene.h"
#include <stack>

GridNode::GridNode(){}
GridNode::GridNode(const RECT & _rect){
	m_object_array.clear();
	m_rect = _rect;
	m_left = NULL;
	m_right = NULL;
}

GridNode::~GridNode() {
}




void GridNode::add_object(EventListener * _obj) {
	//开始二分查找
	if(m_object_array.size()){
		int pre = 0;
		int end = m_object_array.size()-1;
		int mid = (pre+end)>>1;
		std::vector<EventListener*>::iterator it= m_object_array.begin()+mid;
		while(end^pre){
			mid = (pre+end)>>1;
			it= m_object_array.begin()+mid;
			if((*it)->get_depth()<_obj->get_depth()){
				end = mid;
			}else if((*it)->get_depth()>_obj->get_depth()){
				pre = mid+1;
			}else{
				break;
			}
		}
		it= m_object_array.begin()+pre;

		if((*it)->get_depth()<_obj->get_depth()){
			m_object_array.insert(it,1,_obj);
		}else {
			m_object_array.insert(it+1,1,_obj);
		}
	}else{
		m_object_array.push_back(_obj);
	}
}

void GridNode::remove_object(EventListener * _obj) {
	if(_obj == NULL) {
		return;
	}
	std::vector<EventListener *>::iterator it= m_object_array.begin();
	for(uint_32 i=0;i<m_object_array.size();i++){
		it= m_object_array.begin()+i;

		if((*it) == _obj){
			m_object_array.erase(it);
			return ;
		}
	}
}

/*****************SCENCE	TREE****************/
SceneTree::SceneTree() {
}
SceneTree::~SceneTree() {
}

void SceneTree::build_tree(const RECT & _rect) {
	//build the root
	m_root = new GridNode(_rect);
	recursion_divide(_rect , m_root);
}

void SceneTree::recursion_divide(const RECT & _rect,GridNode * _grid) {
	RECT				_tmp_rect;

	if(_grid == NULL) {
		return;
	}
	_grid->m_rect = _rect;
	// if the size is 32*32 then stop
	if(_rect.bottom - _rect.top <= 32 &&
		_rect.right - _rect.left <= 32) {
			_grid->m_left = NULL;
			_grid->m_right = NULL;
			return;
	}
	//if the size is still too big
	_grid->m_left = new GridNode();
	_grid->m_right = new GridNode();
	if(_rect.bottom - _rect.top >=
		_rect.right - _rect.left) {
			//up grid
			_tmp_rect.left = _rect.left;
			_tmp_rect.top = _rect.top;
			_tmp_rect.right =_rect.right;
			_tmp_rect.bottom = _rect.top+(_rect.bottom-_rect.top)/2;
			recursion_divide( _tmp_rect ,_grid->m_left);
			//down grid
			_tmp_rect.left = _rect.left;
			_tmp_rect.top = _rect.top+(_rect.bottom-_rect.top)/2;
			_tmp_rect.right = _rect.right;
			_tmp_rect.bottom = _rect.bottom;
			recursion_divide( _tmp_rect ,_grid->m_right);
	}else {
		//left grid
		_tmp_rect.left = _rect.left;
		_tmp_rect.top = _rect.top;
		_tmp_rect.right = _rect.left+(_rect.right-_rect.left)/2;
		_tmp_rect.bottom = _rect.bottom;
		recursion_divide( _tmp_rect ,_grid->m_left);
		//right grid
		_tmp_rect.left = _rect.left+(_rect.right-_rect.left)/2;
		_tmp_rect.top = _rect.top;
		_tmp_rect.right = _rect.right;
		_tmp_rect.bottom = _rect.bottom;
		recursion_divide( _tmp_rect ,_grid->m_right);
	}
}

void	SceneTree::add_block(EventListener *_block) {
	if(!check_block_pos(_block->get_rect(),m_root->m_rect)){
		return;
	}
	std::stack<GridNode *>  nodes;
	nodes.push(m_root);
	GridNode * tempNode = NULL;
	while(nodes.size()){
		tempNode = nodes.top();
		nodes.pop();
		if(check_block_pos(_block->get_rect(),tempNode->m_rect)){
			if(tempNode->m_left)
				nodes.push(tempNode->m_left);
			if(tempNode->m_right)
				nodes.push(tempNode->m_right);
			if(!(tempNode->m_left||tempNode->m_right)){
				tempNode->add_object(_block);
			}
		}
	}
}

std::vector<EventListener*> SceneTree::get_rend_collection(const RECT & _rect){
	std::vector<EventListener*>				_collection;
	std::stack<GridNode*>					_stack;
	GridNode*								_cur_node = m_root;
	
	_stack.push(_cur_node);
	while (_stack.size())
	{
		_cur_node = _stack.top();
		_stack.pop();
		if (_cur_node != NULL)
		{
			if (!check_intersected(_rect , _cur_node->m_rect))
			{
				continue;
			}
			//push in the children
			if (_cur_node->m_left)
			{
				_stack.push(_cur_node->m_left);
			}
			if (_cur_node->m_right)
			{
				_stack.push(_cur_node->m_right);
			}
			 //check the node
			if (!(_cur_node->m_right || _cur_node->m_left))
			{
				for (uint_32 i = 0;i < _cur_node->m_object_array.size();i++)
				{
					_collection.push_back(_cur_node->m_object_array[i]);
				}
			}
		}
	}
	return _collection;
}

bool	SceneTree::check_block_pos(const RECT & _r_small , const RECT & _r_big) {
	if(_r_small.left >=_r_big.left  &&
		_r_small.right <= _r_big.right &&
		_r_small.top >= _r_big.top &&
		_r_small.bottom <= _r_big.bottom)
		return true;
	return false;
}

bool	SceneTree::check_intersected(const RECT & _r1 , const RECT & _r2) {
	if(_r2.left<_r1.right&&
		_r2.top<_r1.bottom&&
		_r1.left<_r2.right&&
		_r1.top<_r2.bottom)
		return true;
	return false;
}