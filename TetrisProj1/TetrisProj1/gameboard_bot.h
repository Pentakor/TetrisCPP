#ifndef __GAMEBOARD_BOT_H
#define __GAMEBOARD_BOT_H

#include "blocks.h"
#include "combination.h"
#include "gameboard.h"
class gameboard_bot : public gameboard
{
	//block shapes values
	static const int L = 0;
	static const int LREV = 1;
	static const int Z = 2;
	static const int ZREV = 3;
	static const int T = 4;
	static const int SQRT= 5;
	static const int I = 6;
	static const int BOMB = 7;

	static const int NOVICE = 20;//if novice mistake one in 20 moves
	static const int GOOD = 40;//if good mistake one in 40 moves

	int lvl = 3;//computer lvl

	int countmoves = 0;//amount of moves in this circle of mistakes

	int countrows(const blocks* virtualblcok);//count amount of cells covered in the lowest row the block got to
	void setcombo(combination* combo, gameboard* virboard, int rotation, const blocks* virblock);//set the values of the current route/combination
	bool isbetter(const combination* first,const combination* sec);//check wich route/combination is better
	void copyboard(char(*boarddest)[GAME_WIDTH], const char(*boardsrc)[GAME_WIDTH]);//copy src board to dest board
	combination calculatebestbomb(const blocks* block);//calculate besr route for bomb

public:
	bool shouldbe_rand();//check if the route should be random
	combination calculaterandomrute();//randomize route/combination
	void setlvl(int slvl);//set computer lvl
	combination calculatebestroute(const blocks* block);//calculate best route for the computer
	void move(blocks* figure,combination* bestcombo);	//make a move to get to the bestcombo-best position to get to
};
#endif
