#include "Board.h"
int Board::gamePoints = 0;

Board::Board(string name)
{
	string firstLine;
	fstream file;
	int foodCount = 0;
	file.open(name, ios::in);
	getline(file, firstLine);
	int colSize = firstLine.size();
	file.seekg(0);
	clear_screen();
	char ch;
	int row = 0;
	while (file.get(ch))
	{
		int counter = 0;
		while (ch != '\0' && ch != '\n' && counter < colSize && !file.eof()) 
		{
			switch (ch)
			{
			case '@':
			{
				pacmanStartingPoint = Point(counter, row);
				_board[row][counter] = PACMAN;
				break;
			}
			case '$':
			{	
				ghosts.push_back(Point(counter, row));
				_board[row][counter] = GHOST;
				break;
			}
			case '&':
			{
				legendXY = (Point(counter, row));
				_board[row][counter] = SPACE;
				break;
			}
			case '#':
			{	_board[row][counter] = WALL;
				break;
			}
			case '%':
			{	_board[row][counter] = SPACE;
				break;
			}
			default:
			{
				foodCount++;
				_board[row][counter] = FOOD;
				break;
			}
			}
			counter++;
			file.get(ch);
		}

		if (counter < colSize) 
		{
			for (int i = counter; i < colSize; i++)
			{
				_board[row][i] = FOOD;
				foodCount++;
			}
		}
		else if (ch != '\0' && ch != '\n') 
		{
			string tmp;
			getline(file, tmp); 
		}
		row++;
	}
	boardRows = row;
	boardCols = colSize;
	remainingFood = foodCount;
	file.close();
}


void Board::printBoard()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
			cout << _board[i][j];
		cout << endl;
	}
	gotoxy(0, 0);
}

bool Board::isFood(int x, int y)const
{
	if (_board[y][x] == FOOD)
		return true;
	return false;
}


void Board::printLegend()const
{
	int x = legendXY.getX();
	int y = legendXY.getY();
	gotoxy(x,y);
	cout << "                    ";
	gotoxy(x, y + 1);
	cout << "                    ";
	gotoxy(x, y + 2);
	cout << "                    ";
	gotoxy(x, y);
	cout << "Points: " << gamePoints;
	gotoxy(x, y + 1);
	cout << "Remaining Lives: " << remainingLives;
}