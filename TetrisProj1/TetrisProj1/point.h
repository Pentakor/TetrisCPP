#ifndef __POINT_H
#define __POINT_H
class point
{
	int x;
	int y;
public://point coordinations on the board
	point()
	{
		x = 0;
		y = 0;
	}
	//each function returns the value of named data member
	int getx() const;
	int gety() const;
	//each function sets the value of named data member
	void changex(int newx);
	void changey(int newy);
	void changepoint(int x, int y);
};
#endif