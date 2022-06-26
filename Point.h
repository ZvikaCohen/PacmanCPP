#pragma once
#include "io_utils.h"

class Point
{
	int _x, _y;

public:
	Point(int x = 0, int y = 0) : _x(x), _y(y) {}
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
	int getX()const { return _x; };
	int getY()const { return _y; };
	void draw(char ch)const;
	void move(int x, int y) { _x = x, _y = y; } // Setter
	bool operator==(const Point& pnt);
};

