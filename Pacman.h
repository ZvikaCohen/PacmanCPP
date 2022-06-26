#pragma once
#include "GameObject.h"
#include "Fruit.h"
class Pacman : public GameObject
{
	char pacmanKeys[5] = { 'W','X','D','A','S' }; //UP DOWN LEFT RIGHT STAY
public:
	Pacman(Point pnt = Point(0, 0)) : GameObject(pnt) 
	{
		_p = pnt;
	}
	virtual void move(Board& b, Direction direction);
	Direction getDirection(char key)const;
	void setDirection(Direction dir) { _dir = dir; }
};

