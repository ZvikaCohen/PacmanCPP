#include "Ghost.h"

void Ghost::midMove(Board& b)
{
	if (midFlag < 20)
	{
		move(b, STAY);
		midFlag++;
	}
	else
	{
		easyGhostMove(b, STAY);
		midFlag++;
	}
	if (midFlag == 30)
		midFlag = 0;
}

void Ghost::draw(Point pnt)
{
	int x = pnt.getX();
	int y = pnt.getY();
	gotoxy(x, y);
	cout << underGhost;
}

void Ghost::move(Board& b, Direction direction)
{
	if (flag == 1)
	{
		int x = _p.getX();
		int y = _p.getY();
		Point oldPoint(x, y);
		Direction tmp;
		tmp = minDistance(b, x, y);
		newMove(b, tmp, x, y);
		int newx = _p.getX();
		int newy = _p.getY(); // get updated x,y
		_p.draw(GHOST);
		flag = 0;
	}
	else
	{
		flag++;
	}

}

void Ghost::newMove(Board& b, Direction direction, int currX, int currY)
{
	if (underGhost != GHOST && underGhost != '5' && underGhost != '6' && underGhost != '7' && underGhost != '8' && underGhost != '9')
	{
		_p.draw(underGhost);
		b.setBoardItem(currX, currY, underGhost);
	}
	switch (direction)
	{
	case UP:
	{

		underGhost = b.getBoardItem(currX, currY - 1);
		_p.move(currX, currY - 1);
		b.setBoardItem(currX, currY - 1, GHOST);
		break;
	}
	case DOWN:
	{
		underGhost = b.getBoardItem(currX, currY + 1);
		_p.move(currX, currY +1);
		b.setBoardItem(currX, currY + 1, GHOST);
		break;
	}
	case LEFT:
	{
		underGhost = b.getBoardItem(currX - 1, currY);
		_p.move(currX - 1, currY);
		b.setBoardItem(currX - 1, currY, GHOST);
		break;
	}
	case RIGHT:
	{
		underGhost = b.getBoardItem(currX + 1, currY);
		_p.move(currX + 1, currY);
		b.setBoardItem(currX + 1, currY, GHOST);
		break;
	}
	}
	if(midFlag >=20)
		_p.draw(GHOST);
}


void Ghost::easyGhostMove(Board& b, int direction)
{
	if (flag == 1)
	{
		int currX = _p.getX();
		int currY = _p.getY();
		int possibleDirections = 0;
		Direction dir = randDirectionForEasyGhostMove(b, currX, currY, &possibleDirections);
		_dir = dir;
		newMove(b, dir, currX, currY);
		_p.draw(GHOST);
		flag = 0;
	}
	else
		flag++;
}

Direction Ghost::randDirectionForEasyGhostMove(Board& b, int x, int y, int* possibleSpots)const
{
	int arr[4] = { 0,0,0,0 };
	int counter = 0;
	int colSize = b.getBoardCols();
	int rowSize = b.getBoardRows();
	if (b.getBoardItem(x, y - 1) != WALL && y > 1 && _dir != DOWN) // UP
	{
		counter++;
		arr[0] = 1;
	}
	if (b.getBoardItem(x, y + 1) != WALL && y < rowSize-1 && _dir != UP) // DOWN
	{
		counter++;
		arr[1] = 1;
	}
	if (b.getBoardItem(x + 1, y) != WALL && x < colSize-1 && _dir != LEFT) // RIGHT
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
		return (Direction)STAY;
	for (int j = 0; j < counter; j++)
		tempArr[j] = 0;
	int arrSpot = 0;
	for (int i = 0; i < 4; i++) // [0,1,0,1], counter = 2 -----> [3,1]
		if (arr[i] == 1)
		{
			tempArr[arrSpot] = i;
			arrSpot++;
		}
	int ans = tempArr[rand() % counter];
	delete[] tempArr;
	return (Direction)ans;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
#define Y 25
#define X 80

Direction Ghost::minDistance(Board& b, int oldx, int oldy)const
{
	QItem source(0, 0, STAY);

	// To keep track of visited QItems. Marking
	// blocked cells as visited.
	int boardRows = b.getBoardRows();
	int boardCols = b.getBoardCols();
	bool visited[Y][X];
	
	for (int i = 0; i < boardRows; i++) {
		for (int j = 0; j < boardCols; j++)
		{
			if (b.getBoardItem(j, i) == WALL)
				visited[i][j] = true;
			else
				visited[i][j] = false;
		}
	}
	source.row = oldy;
	source.col = oldx;
	// applying BFS on matrix cells starting from source
	queue<QItem> q;
	q.push(source);
	bool isFirst = true;
	visited[source.row][source.col] = true;
	QItem p = q.front();
	while (!q.empty()) {
		p = q.front();
		q.pop();
		// Destination found;
		if (b.getBoardItem(p.col, p.row) == PACMAN)
		{
			return p.getDirection();
		}
		// moving up
		if (p.row - 1 >= 0 && visited[p.row - 1][p.col] == false) {
			if (isFirst)
			{
				q.push(QItem(p.row - 1, p.col, UP));
			}
			else
				q.push(QItem(p.row - 1, p.col, p.getDirection()));
			visited[p.row - 1][p.col] = true;
		}

		// moving down
		if (p.row + 1 < boardRows && visited[p.row + 1][p.col] == false) {
			if (isFirst)
			{
				q.push(QItem(p.row + 1, p.col, DOWN));
			}
			else
				q.push(QItem(p.row + 1, p.col, p.getDirection()));
			visited[p.row + 1][p.col] = true;
		}

		// moving left
		if (p.col - 1 >= 0 && visited[p.row][p.col - 1] == false) {
			if (isFirst)
			{
				q.push(QItem(p.row, p.col - 1, LEFT));
			}
			else
				q.push(QItem(p.row, p.col - 1, p.getDirection()));
			visited[p.row][p.col - 1] = true;
		}

		// moving right
		if (p.col + 1 < boardCols && visited[p.row][p.col + 1] == false) {
			if (isFirst)
			{
				q.push(QItem(p.row, p.col + 1, RIGHT));
			}
			else
				q.push(QItem(p.row, p.col + 1, p.getDirection()));
			visited[p.row][p.col + 1] = true;
		}
		if (isFirst)
			isFirst = false; 
	}
}

