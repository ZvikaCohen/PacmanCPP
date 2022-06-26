#include "Fruit.h"

int Fruit::movesCount = 0;
int Fruit::flag = 0;

void Fruit::move(Board& b, Direction dir) // This is the fruit mechanism, not physical moving.
{
	if (movesCount < 20)
	{
		movesCount++;
	}
	else
	{
		if (movesCount == 20)
		{
			bool tmp = false;
			int rows = b.getBoardRows();
			int cols = b.getBoardCols();
			while (!tmp)
			{
				int y = (rand() % (rows - 2))+1;
				int x = (rand() % (cols - 2))+1;
				char c = b.getBoardItem(x, y);
				if (!fruitValidRandomLocation(b,x,y))
					continue;
				else
				{
					if(underFruit != PACMAN)
						underFruit = c;
					fruitNum = rand() % 5 + 5;
					_p.setX(x);
					_p.setY(y);
					tmp = true;
				}
			}
		}
		else if (movesCount == FRUIT_STEPS_LIMIT)
		{
			movesCount = 0;
			b.setBoardItem(_p.getX(), _p.getY(), underFruit);
			_p.draw(underFruit);
		}
		else
		{
			if ((flag%3) == 0)
			{
				int possibleSpots;
				Direction randDirection = fruitDirectionDecider(b, &possibleSpots);
				_dir = randDirection;
				fruitMove(b, randDirection);
			}
			else if (flag>10)
				flag = 0;
			flag++;
		}
		movesCount++;
	}
}


Direction Fruit::fruitDirectionDecider(Board& b, int* possibleSpots)const
{
	int x = _p.getX();
	int y = _p.getY();
	int rows = b.getBoardRows();
	int cols = b.getBoardCols();
	int arr[4] = { 0,0,0,0 };
	int counter = 0;
	if (b.getBoardItem(x, y - 1) != WALL && y > 1) // UP
	{
		counter++;
		arr[0] = 1;
	}
	if (b.getBoardItem(x, y + 1) != WALL && y < rows - 2) // DOWN
	{
		counter++;
		arr[1] = 1;
	}
	if (b.getBoardItem(x + 1, y) != WALL && x < cols - 2 && _dir != LEFT) // RIGHT
	{
		counter++;
		arr[2] = 1;
	}
	if (b.getBoardItem(x - 1, y) != WALL && x > 1 && _dir != RIGHT) // LEFT
	{
		counter++;
		arr[3] = 1;
	}
	*possibleSpots = counter;
	int* tempArr = new int[counter];
	if (counter == 0)
		return STAY;
	for (int j = 0; j < counter; j++)
		tempArr[j] = 0;
	int arrSpot = 0;
	for (int i = 0; i < 4; i++) // [0,1,0,1], counter = 2 -----> [3,1]
		if (arr[i] == 1)
		{
			tempArr[arrSpot] = i;
			arrSpot++;
		}
	Direction ans = (Direction)(tempArr[rand() % counter]);
	delete[] tempArr;
	return ans;
}

// Here fruit physiclly moves. Really moves. But it's track was made in Fruit::move.
void Fruit::fruitMove(Board& b, Direction dir)
{
	int currX = _p.getX();
	int currY = _p.getY();
	if (underFruit == -1)
		underFruit = b.getBoardItem(currX, currY);
	else if (underFruit != PACMAN && underFruit != GHOST)
	{
		_p.draw(underFruit);
		b.setBoardItem(currX, currY, underFruit);
	}
	switch (dir)
	{
	case UP:
	{
		if (b.getBoardItem(currX, currY - 1) != WALL)
		{
			underFruit = b.getBoardItem(currX, currY - 1);
			_p.move(currX, currY - 1);
			b.setBoardItem(currX, currY - 1, fruitNum + 48);
			_p.draw(fruitNum + 48);
		}
		break;
	}
	case DOWN:
	{
		if (b.getBoardItem(currX, currY + 1) != WALL)
		{
			underFruit = b.getBoardItem(currX, currY + 1);
			_p.move(currX, currY + 1);
			b.setBoardItem(currX, currY + 1, fruitNum + 48);
			_p.draw(fruitNum + 48);
		}
		break;
	}
	case LEFT:
	{
		if (b.getBoardItem(currX - 1, currY) != WALL)
		{
			underFruit = b.getBoardItem(currX - 1, currY);
			_p.move(currX - 1, currY);
			b.setBoardItem(currX - 1, currY, fruitNum + 48);
			_p.draw(fruitNum + 48);
		}
		break;
	}
	case RIGHT:
	{
		if (b.getBoardItem(currX + 1, currY) != WALL)
		{
			underFruit = b.getBoardItem(currX + 1, currY);
			_p.move(currX + 1, currY);
			b.setBoardItem(currX + 1, currY, fruitNum + 48);
			_p.draw(fruitNum + 48);
		}
		break;
	}
	}

}

bool Fruit::fruitValidRandomLocation(Board b, int x, int y)const
{
	char item = b.getBoardItem(x, y);
	if (item == WALL || item == PACMAN || item == GHOST)
		return false;
	Point legend = b.getLegendPoint();
	if (x >= legend.getX() && x <= legend.getX() + 20 && y >= legend.getY() && y <= legend.getY() + 3)
	{
		return false;
	}
	return true;
}