#include "point.h"

int point::getx() const
{
	return x;
}

int point::gety() const
{
	return y;
}

void point::changex(int newx)
{
	x = newx;
}

void point::changey(int newy)
{
	y = newy;
}

void point::changepoint(int newx, int newy)
{
	x = newx;
	y = newy;
}