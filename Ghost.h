#pragma once
#include "GameObject.h"
#include "QItem.h"
#define X 80
#define Y 25

class Ghost : public GameObject
{
	char underGhost = SPACE;
	int flag = 0;
	int midFlag = 0;

public:
	Ghost(Point pnt = Point(0, 0)) : GameObject(pnt)
	{
		_p = pnt;
	}
	virtual void draw(Point pnt);
	virtual void move(Board& b, Direction direction);
	int getGhostCurrFlag()const { return flag; }
	char getUnderGhost()const { return underGhost; }
	Direction randDirectionForEasyGhostMove(Board& b, int x, int y, int* possibleSpots)const;
	Direction minDistance(Board& b, int oldx, int oldy)const;
	void newMove(Board& b, Direction direction, int currX, int currY);
	void setUnderGhost(char c) { underGhost = c; }
	void easyGhostMove(Board& b, int direction);
	void midMove(Board& b);
};

