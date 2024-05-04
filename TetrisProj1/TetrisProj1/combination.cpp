#include "combination.h"

void combination::set_highrow(int score)
{
	highrow = score;
}

void combination::set_rowdownscore(int score)
{
	rowdownscore = score;
}

void combination::set_lowestrow(int score)
{
	lowestrow = score;
}

void combination::set_maxcells(int score)
{
	maxcells = score;
}

void combination::set_coordinate(int x,int y)
{
	coordinate.changepoint(x,y);
}

void combination::set_rotation(int rot)
{
	rotation = rot;
}

int combination::get_rowdownscore() const
{
	return rowdownscore;
}

int combination::get_lowestrow() const
{
	return lowestrow;
}

int combination::get_maxcells() const
{
	return maxcells;
}

point combination::get_coordinate() const
{
	return coordinate;
}

int combination::get_rotation() const
{
	return rotation;
}

void combination::set_holes(int score)
{
	holes = score;
}

int combination::get_holes() const
{
	return holes;
}

int combination::get_highrow() const
{
	return highrow;
}