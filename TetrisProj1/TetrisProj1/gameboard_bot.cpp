
#include "gameboard_bot.h"
#include "gameboard.h"
#include <iostream>
#include <windows.h>
#include "general.h"
#include "blocks.h"
#include "combination.h"

void gameboard_bot::setlvl(int slvl)
{
	lvl = slvl;
}
bool gameboard_bot::shouldbe_rand()
{
	if (lvl == 1)//if level is one-novice
	{
		countmoves++;
		if (countmoves == NOVICE)//one in 20 moves
		{
			countmoves = 0;
			return true;
		}
	}
	else if (lvl == 2)//if lvl is 2-  good
	{
		countmoves++;
		if (countmoves == GOOD)//one in 40 moves
		{
			countmoves = 0;
			return true;
		}
	}
	return false;
}
combination gameboard_bot::calculaterandomrute()
{
	int y= rand() % GAME_WIDTH;
	int x = 0;//this value is irelevant
	combination ret;
	ret.set_coordinate(x, y);
	return ret;
}
combination gameboard_bot::calculatebestroute(const blocks* block)
{
	combination best;
	if (block->get_bshape() != BOMB) {//for bomb the algorithm is different

	combination current;
	
	gameboard virtualboard;
	virtualboard.initializeboard();
	int t = 0;
	blocks virtualblock = *block;
	int rotation = 0;
	
		for (int r = 0; r < 4; r++)//go threww all rotatoins 
		{

			for (int i = 0; i < 12; i++)//go threw all places
			{
				copyboard(virtualboard.get_board(), board);
				virtualblock = *block;
				rotation = 0;
				for (int j = 0; j < r; j++)
				{
					virtualblock.rotate_clock();
					virtualboard.printblock(&virtualblock);
					rotation++;
				}
				for (int j = 0; j < 12; j++)
				{

					virtualboard.move1('a', &virtualblock);
					virtualboard.printblock(&virtualblock);
				}
				for (int j = 0; j < i; j++)
				{
					virtualboard.move1('d', &virtualblock);
				}
				virtualboard.move1('x', &virtualblock);
				virtualboard.printblock(&virtualblock);

				if (r == 0 && i == 0)//if its first - it is the besst
				{
					setcombo(&best, &virtualboard, rotation, &virtualblock);
				}
				else
				{
					setcombo(&current, &virtualboard, rotation, &virtualblock);
					if (isbetter(&current, &best))//compare between current and best route
					{
						best = current;
					}
				}
			}

		}
	}
	else
	{
		best = calculatebestbomb(block);
	}
	return best;
}
		
combination gameboard_bot::calculatebestbomb(const blocks* block)
{
	//the function is similar for the standard calculatebest route but we should not check the rotations
	//and the  best route depends only on the height. as higher - so better.
	combination current;
	combination best;
	gameboard virtualboard;
	virtualboard.initializeboard();
	int t = 0;
	blocks virtualblock = *block;
	for (int i = 0; i < 12; i++)
	{
		copyboard(virtualboard.get_board(), board);
		virtualblock = *block;
		for (int j = 0; j < 12; j++)
		{
			virtualboard.move1('a', &virtualblock);
			virtualboard.printblock(&virtualblock);
		}
		for (int j = 0; j < i; j++)
		{
			virtualboard.move1('d', &virtualblock);
		}
		virtualboard.move1('x', &virtualblock);
		virtualboard.printblock(&virtualblock);

		if (i == 0)
		{
			best.set_highrow(virtualblock.get_blockarr(0).getx());
			best.set_coordinate(virtualblock.get_blockarr(0).getx(), virtualblock.get_blockarr(0).gety());
		}
		else
		{
			current.set_highrow(virtualblock.get_blockarr(0).getx());
			current.set_coordinate(virtualblock.get_blockarr(0).getx(), virtualblock.get_blockarr(0).gety());
			if (current.get_highrow()<best.get_highrow())
			{
				best = current;
			}
		}
	}
	return best;
}

void gameboard_bot::setcombo(combination*combo, gameboard * virboard,int rotation,const blocks* virblock)
{
	int y = 17;
	int lowestrow = -1;
	int holes = 0;
	while (y > 0 && lowestrow == -1)
	{
		for (int x = 0; x < 12; x++)
		{
			if (virboard->get_board()[y][x] == 'O')
			{
				lowestrow = y;
				if (lowestrow != 17)
				{
					for (int i = 0; i < 4; i++)//set holes (more holes-worst)
					{
						char b = virboard->get_board()[virblock->get_blockarr(i).getx() + 1][virblock->get_blockarr(i).gety()];
						if (b == '.')
							holes++;
					}
						
				}
			}
		}
		y--;
	}
	combo->set_rowdownscore(virboard->clear_full_rows());//add to score if there is cleared row
	combo->set_lowestrow(lowestrow);//set score for the lowest row the block got to
	combo->set_maxcells(countrows(virblock));//set max cells that were covered in the lowest row
	combo->set_rotation(rotation);//set amount of rotations in this route
	combo->set_coordinate(virblock->get_blockarr(4).getx(), virblock->get_blockarr(4).gety());//set the coordinate of this route
	combo->set_holes(holes);//set the holes
}
int gameboard_bot::countrows(const blocks* virtualblock)
{
	
	int count = 0;
	bool flag = false;
	if (virtualblock->get_bshape() != I && virtualblock->get_bshape() != SQRT)
	{
		for (int j = 0; j < 3; j++)
		{
			if (virtualblock->get_block_three(2, j) == 'O')
			{
				count++;
				flag = true;
			}
		}
		if (!flag)
		{
			for (int j = 0; j < 3; j++)
			{
				if (virtualblock->get_block_three(1,j) == 'O')
				{
					count++;
					flag = true;
				}
			}
		}
	}
	else if (virtualblock->get_bshape() == I)
	{	
		for (int j = 0; j < 4; j++)
		{
			if (virtualblock->get_block_four(2,j) != '.')
				count++;
		}
	}
	else
		count = 2;
	return count;
}
bool gameboard_bot::isbetter(const combination* first, const combination* sec)
{
	if (first->get_rowdownscore() > sec->get_rowdownscore())
		return true;
	else if (first->get_rowdownscore() < sec->get_rowdownscore())
		return false;
	else
	{
		if (first->get_lowestrow() > sec->get_lowestrow())
			return true;
		else if (first->get_lowestrow() < sec->get_lowestrow())
			return false;
		else
		{
			if (first->get_maxcells() > sec->get_maxcells())
				return true;
			else if (first->get_maxcells() < sec->get_maxcells())
				return false;
			else 
			{
				if (first->get_holes() < sec->get_holes())
					return true;
				else
					return false;
			}
		}
	}
}


void gameboard_bot::move(blocks* figure, combination *bestcombo)
{ 
	if (bestcombo->get_rotation() != 0)
	{
		figure->rotate_clock();
		bestcombo->set_rotation(bestcombo->get_rotation()-1);
	}
	else if (bestcombo->get_coordinate().gety() != figure->get_blockarr(4).gety())
	{


		if (bestcombo->get_coordinate().gety() < figure->get_blockarr(4).gety())
			figure->moveleft(board);
		else
			figure->moveright(board);
	}
	else
		figure->drop(board);
}
void gameboard_bot::copyboard(char(*boarddest)[GAME_WIDTH],const char(*boardsrc)[GAME_WIDTH])
{
	for (int i = 0; i < GAME_HEIGHT; i++)
	{
		for (int j = 0; j < GAME_WIDTH; j++)
		{
			boarddest[i][j] = boardsrc[i][j];
		}
	}
}
