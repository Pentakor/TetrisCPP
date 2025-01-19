#ifndef __COMBINATION_H
#define __COMBINATION_H
#include "point.h"
class combination//combination represents combination of moves and its statistics
{
	int rowdownscore;//amount of rows that the tetromino deleted
	int lowestrow;//lowest row that the tetromino got to
	int maxcells;//the amount of cells in the lowest row that the tetromino covered
	point coordinate;//coordinate of the tetromino (block[4])
	int rotation;//amounnt of rotations (clockwise) needed to get to this position from spawn position
	int holes;//amount of halls that the tetromino created with the board
	int highrow;//highest row the tetromino covered (implemented only for the bomb shape)
public:
	
	//each function sets the value of named data member
	void set_rowdownscore(int score);
	void set_lowestrow(int score);
	void set_maxcells(int score);
	void set_coordinate(int x, int y);
	void set_rotation(int rot);
	void set_holes(int score);
	void set_highrow(int score);

	//each function returns the value of named data member
	int get_holes() const;
	int get_rowdownscore() const;
	int get_lowestrow() const;
	int get_maxcells() const;
	point get_coordinate() const;
	int get_rotation()const;
	int get_highrow()const;

	combination()
	{
		rowdownscore = 0;
		lowestrow = 0;
		maxcells = 0;
		rotation = 0;
		holes = 0;
		highrow = 17;
	}
};
#endif