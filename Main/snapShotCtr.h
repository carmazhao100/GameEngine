/*===============================
//Author:	carmazhao
//Data:		2011/2/26
//Functoin: control the snapshot
//
================================*/
#ifndef SNAP_SHOT_CTR_HEAD_
#define SNAP_SHOT_CTR_HEAD_
#include "sysDef.h"
#include "Player.h"
#include <vector>

class snapShotCtr
{
	DEFINE_SINGLE_MODEL(snapShotCtr)
public:
	~snapShotCtr();

	void		deal_player_snap_shot(const std::vector<Player> &  _player_arr);
private:
	snapShotCtr();
};
#endif