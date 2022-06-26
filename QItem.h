#pragma once
#include "GameObject.h"
#include <queue>
#define Y 25
#define X 80
class QItem {
public:
	int row;
	int col;
	Direction _dir;
	QItem(int x, int y, Direction dir)
		: row(x), col(y), _dir(dir)
	{
	}
	Direction getDirection() const;
};

