/*===============================
//Author:	carmazhao
//Data:		2011/2/26
//Functoin: control other players
================================*/
#ifndef PLAYERS_CTR_HEAD_
#define	PLAYERS_CTR_HEAD_
#include "sysDef.h"
#include "Player.h"
#include <vector>

class PlayersCtr
{
	DEFINE_SINGLE_MODEL(PlayersCtr)
public:
	~PlayersCtr();

	void	clear_player();							//clear the arr when snapshot comes
	void	add_player(Player  _player);
	void	remove_player(const int_32	& _id);

	void	draw();
	void	execute_change();
private:
	PlayersCtr();
	std::vector<Player>		m_player_arr;
};
#endif