#pragma once
#include "GameObject.h"
#define FRUIT_STEPS_LIMIT 80

class Fruit : public GameObject
{
	int fruitNum = 5;
	static int movesCount;
	static int flag;
	char underFruit = -1;


public:
	Fruit(Point pnt = (4,4)) : GameObject(pnt)
	{
		_p = pnt;
		_dir = RIGHT;
	}
	void fruitMove(Board& b, Direction dir);
	int getFruitNum()const { return fruitNum; }
	int getMovesCount()const { return movesCount; }
	void resetMovesCount() { movesCount = 0; }
	char getUnderFruit()const { return underFruit; }
	void resetPoint(Point pnt = (Point)(0, 0))
	{
		_p = pnt;
	}
	void setUnderFruit(char c) {
		underFruit = c;
	}
	void move(Board& b, Direction dir) override;
	Direction fruitDirectionDecider(Board& b, int* possibleSpots)const;
	static void pacmanEatFruit() { movesCount = 0; }
	bool fruitValidRandomLocation(Board b, int x, int y)const;
};

