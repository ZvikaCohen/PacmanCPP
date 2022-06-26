#pragma once
#include "Point.h"
#include "Board.h"
#include "io_utils.h"
enum Direction { UP, DOWN, RIGHT, LEFT, STAY, illgal_key_pressed = -1 };


class GameObject
{
protected:
	Point _p;
	Direction _dir = STAY;
	
public:
	GameObject(Point p) { _p = p; }
	Point getPoint()const { return _p; }
	Direction getDir()const { return _dir; };
	virtual void resetPoint(Point p) { _p = p; }
	virtual void move(Board& b, Direction direction) = 0;

};

