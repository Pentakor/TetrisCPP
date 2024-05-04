#ifndef __BLOCKS_H
#define __BLOCKS_H
#include "point.h"
class blocks
{
	//block names 
	static const int L = 0;
	static const int LREV = 1;
	static const int Z = 2;
	static const int ZREV = 3;
	static const int T = 4;
	static const int SQRT = 5;
	static const int I = 6;
	static const int BOMB = 7;

	//bomb one in X chance to spawn
	static const int BOMB_CHANCE = 20;
	//rotation names
	static const int BLOCK_MEASURE_FOUR = 4;
	static const int BLOCK_MEASURE_THREE = 3;
	static const int ANTI = 3;

	//points array names
	static const int ARRAY_LEN = 5;
	static const int ARRAY_T_LEN = 4;


	static const int GAME_WIDTH = 12;
	static const int GAME_HEIGHT = 18;

	static const int AMOUNT_FIGURES = 7;
	static const int AMOUNT_ROTATIONS = 4;
	
	point block[ARRAY_LEN];//point array names

	int bshape;//block name
	
	//rotation matrix 4x4 (for I)
	char block_r_four[BLOCK_MEASURE_FOUR][BLOCK_MEASURE_FOUR] = {
		{'.', '.', '.', '.'},
		{'.', '.', '.', '.'},
		{'.', '.', '.', '.'},
		{'.', '.', '.', '.'}
	};
	//rotation matrix 3x3 (for L,Z,T and reverses)
	char block_r_three[BLOCK_MEASURE_THREE][BLOCK_MEASURE_THREE] = {
		{'.', '.', '.'},
		{'.', '.', '.'},
		{'.', '.', '.'}
	};

	void rotate_clock_help();//rotating the 3x3 matrix-block clockwise
	void rotate_anticlock_help();//rotating 3x3 the matrix-block unclockwise
	void clrblock_three();//clearing matrix 3x3
	void clrblock_four();//clearing matrix 4x4
	void matrix_to_point();//getting values from the matrix to set points coordinations
	void rotate_i();//rotating the I block matrix 4x4

public:

	void set_blockarr(int i, int x, int y);
	point get_blockarr(int i) const;
	char get_block_four(int i, int j) const;
	char get_block_three(int i, int j) const ;
	void set_bshape(int shape);
	int get_bshape() const;
	void initialize();//initializing newly created block
	void rotate_clock();//rotating the block clock direction
	void rotate_anticlock();//rotating the block anti clock direction
	void moveleft(const char(*board)[GAME_WIDTH]);//moving points block left
	void moveright(const char(*board)[GAME_WIDTH]);//moving points block right
	bool movedown(const char(*board)[GAME_WIDTH]);//moving points block down
	void drop(const char(*board)[GAME_WIDTH]);//drop block to the lowest point possible
};
#endif