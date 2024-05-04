#ifndef __GAMEBOARD_H
#define __GAMEBOARD_H
#include "blocks.h"
class gameboard
{
protected:
	static const int C30 = 30;//for gotoxy function

	static const int BOMB = 7;

	static const int GAME_WIDTH = 12;//game board width
	static const int GAME_HEIGHT = 18;//game board height
	
	static const int BLOCK_ARR_LEN = 4;//length of block array

	static const int RADIUS = 4;
	
	char board[GAME_HEIGHT][GAME_WIDTH];//the board matrix

public:
	char get_board_value(int i, int j) const;//returns specific cell value of the board 
	char(*get_board())[GAME_WIDTH];//returns pointer to the board
	
	void clr_active_block();//clear active block from the board.
	void detonate(const blocks* figure);
	void clrblock_fromboard(const blocks* figure);//erasing given block from the board
	void initializeboard();//initializng the board (creating empty board)
	void printboard1();//printing the board to the console in left side of the screen
	void printboard2();//printing the boardto the console in the right side of ther screen
	void printblock(const blocks* block);//printing given block on the board
	void move2(char ch, blocks* figure);//moves using wasdx buttons
	void move1(char ch, blocks* figure);//moves using ijklm buttins
	bool touchground(const blocks* block);//checking if the got to the ground
	int clear_full_rows();//function is deleting full rows and moving the rows down
};
#endif
