/*===============================
//Author:	carmazhao
//Data:		2011/1/3
//Functoin:	create and divide the 
//			scene , change scene,
//			but it can only store 
//			the map information
================================*/
#ifndef GRAPH_SCENE_HEAD_
#define GRAPH_SCENE_HEAD_

#include "../Main/sysDef.h"
#include "EventListener.h"
#include <vector>

class GridNode{
public:
	GridNode(const RECT & _rect);
	GridNode();
	~GridNode();

	void			add_object(EventListener *);
	void			remove_object(EventListener *);

	RECT							m_rect;
	GridNode *						m_left;
	GridNode *						m_right;
	std::vector<EventListener*>		m_object_array;
};

class SceneTree
{ 
public:
	SceneTree();	
	~SceneTree();

	void		build_tree(const RECT & _rect );
	void		add_block(EventListener* _block);
	
	bool		check_block_pos(const RECT & _r1 , const RECT & _r2);
	bool		check_intersected(const RECT & _r1 , const RECT & _r2);

	std::vector<EventListener*>	get_rend_collection(const RECT & _rect);
private:
	GridNode *		m_root;

	void		recursion_divide(const RECT & _rect , GridNode * _grid);
};

#endif