
#include "gameboard.h"
#include <iostream>
#include <windows.h>
#include "general.h"
#include "blocks.h"

char (*gameboard::get_board())[GAME_WIDTH]
{
	return board;
}
char gameboard::get_board_value(int i, int j) const
{
	return board[i][j];
}
void gameboard::clr_active_block()
{
	for (int i = 0; i < GAME_HEIGHT; i++) {
		for (int j = 0; j < GAME_WIDTH; j++) {
			if(board[i][j]=='O')
			    board[i][j] = '.';
		}
	}
}
void gameboard::initializeboard()
{
	for (int i = 0; i < GAME_HEIGHT; i++) {
		for (int j = 0; j < GAME_WIDTH; j++) {
			board[i][j] = '.';
		}
	}
}
void gameboard::printboard1()
{
	std::cout << "|";
	for (int j = 0; j < GAME_WIDTH; j++)
		std::cout << "--";
	std::cout << "|";
	std::cout << std::endl;
	for (int i = 0; i < GAME_HEIGHT; i++) {
		std::cout << "|";
		for (int j = 0; j < GAME_WIDTH; j++) {
			std::cout << board[i][j] << " ";
		}
		std::cout << "|";
		std::cout << std::endl;
	}
	std::cout << "|";
	for (int j = 0; j < GAME_WIDTH; j++)
		std::cout << "--";
	std::cout << "|";

}

void gameboard::printboard2()
{
	gotoxy(C30,0);
	std::cout << "|";
	for (int j = 0; j < GAME_WIDTH; j++)
		std::cout << "--";
	std::cout << "|";
	std::cout << std::endl;
	gotoxy(C30, 1);
	for (int i = 0; i < GAME_HEIGHT; i++) {
		std::cout << "|";
		for (int j = 0; j < GAME_WIDTH; j++) {
			std::cout << board[i][j] << " ";
		}
		std::cout << "|";
		std::cout << std::endl;
		gotoxy(C30, i+2);
	}
	std::cout << "|";
	for (int j = 0; j < GAME_WIDTH; j++)
		std::cout << "--";
	std::cout << "|";

}

void gameboard::printblock(const blocks* figure)
{
	int bx, by;
	if (figure->get_bshape() != BOMB)
	{
		for (int i = 0; i < BLOCK_ARR_LEN; i++)
		{
			bx = figure->get_blockarr(i).getx();
			by = figure->get_blockarr(i).gety();
			board[bx][by] = 'O';
		}
	}
	else
	{
		bx = figure->get_blockarr(0).getx();
		by = figure->get_blockarr(0).gety();
		board[bx][by] = 'B';
	}
}
void gameboard::clrblock_fromboard(const blocks* figure)
{
	int dx, dy;
	for (int i = 0; i < BLOCK_ARR_LEN; i++)
	{
		dx = figure->get_blockarr(i).getx();
		dy = figure->get_blockarr(i).gety();
		board[dx][dy] = '.';
	}
}
bool gameboard::touchground(const blocks* figure)
{
	bool flag = false;
	for (int i = 0; i < BLOCK_ARR_LEN; i++)
	{
		if (figure->get_blockarr(i).getx() == GAME_HEIGHT - 1 || board[figure->get_blockarr(i).getx() + 1][figure->get_blockarr(i).gety()] == '0')
			flag= true;
	}
	if(flag)
	{
	     for (int i = 0; i < BLOCK_ARR_LEN; i++)
	     {
		      board[figure->get_blockarr(i).getx()][figure->get_blockarr(i).gety()] = '0';
	     }
	}
	return flag;
}

void gameboard::move1(char ch,blocks *figure)
{
	clrblock_fromboard(figure);
	switch (ch) {
	case 's'://rotate left
		figure->rotate_clock();
		break;
	case 'w'://rotate right

		figure->rotate_anticlock();
		break;
	case 'a'://move left

		figure->moveleft(board);
		break;
	case 'd'://move right

		figure->moveright(board);
		break;
	case 'x':
		figure->drop(board);
	default:
		break;
	}
}
void gameboard::move2(char ch, blocks* figure)
{
	clrblock_fromboard(figure);
	switch (ch) {
	case 'k'://rotate left
		figure->rotate_clock();
		break;
	case 'i'://rotate right

		figure->rotate_anticlock();
		break;
	case 'j'://move left

		figure->moveleft(board);
		break;
	case 'l'://move right

		figure->moveright(board);
		break;
	case 'm':
		figure->drop(board);	
	default:
		break;
	}
}

int gameboard::clear_full_rows()
{
	int j = 0;
	int cheker_for_point = 0;
	int score = 0;//each cleared row is adding 1 to the score
	for (int i = 0; i < GAME_HEIGHT; i++)
	{
		for (j = 0; j < GAME_WIDTH; j++)//check if row is full
		{
			if (board[i][j] == '0')
				cheker_for_point++;
		}
		if (cheker_for_point == GAME_WIDTH)//clear row
		{
			score++;
			for (j = 0; j < GAME_WIDTH; j++)
			{
				board[i][j] = '.';		
			}
			for (int y = i - 1; y >= 0; y--)
			{
				for (j = 0; j < GAME_WIDTH; j++)
				{
					if (board[y][j] == '0')
					{
						board[y][j] = '.';
						board[y + 1][j] = '0';
					}
				}
			}
		}
		cheker_for_point = 0;	
	}
	return score;
}

void gameboard::detonate(const blocks* figure)
{

	int x;
	int y;

	for (x = figure->get_blockarr(0).getx() - RADIUS; x <= figure->get_blockarr(0).getx() + RADIUS; x++)
	{
		for (y = figure->get_blockarr(0).gety() - RADIUS; y <= figure->get_blockarr(0).gety() + RADIUS; y++)
		{
			if ((x >= 0 && x < GAME_HEIGHT) && (y >= 0 && y < GAME_WIDTH))
			{
				board[x][y] = '.';
			}
		}
	}
	
}