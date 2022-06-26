#pragma once
#include "Point.h"
// #include "Fruit.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
#define ROW 25
#define COL 80

#define SPACE ' '
#define WALL '#'
#define FOOD '.'
#define PACMAN 'C'
#define GHOST '$'



class Board
{
	char _board[ROW][COL];
	Point pacmanStartingPoint;
	Point legendXY;
	vector<Point> ghosts;
	int remainingFood = 0;
	static int gamePoints;
	int remainingLives = 3;
	int boardRows;
	int boardCols;

public:
	Board(string name);
	void printBoard();
	void printLegend()const;
	bool isFood(int x, int y)const;
	vector<Point> getGhostsVector() { return ghosts; }
	void setRemainingLives(int num) { remainingLives = num; }
	int getBoardRows()const { return boardRows; }
	int getRemainingLives()const { return remainingLives; }
	int getBoardCols()const { return boardCols; }
	int getBoardPoints()const { return gamePoints; }
	Point getPacmanStartingPoint()const { return pacmanStartingPoint; }
	char getBoardItem(int x, int y)const { return _board[y][x]; }
	int getCurrFood()const { return remainingFood; }
	Point getLegendPoint()const { return legendXY; }
	void setBoardRows(int row) { boardRows = row; }
	void setBoardCols(int col) { boardCols = col; }
	void setBoardPoints(int points) { gamePoints = points; } 
	// ^ In case we won one map and continue to another, we want to change the curr board points.
	void minusOneFood() { remainingFood--; gamePoints++; }
	void minusOneLife() { remainingLives--; }
	void addFruitPoints(int num) { gamePoints += num; }
	bool isValidMove(int x, int y)const {
		if (getBoardItem(x, y) != WALL)
			return true;
		return false;
	}
	void setBoardItem(int x, int y, char item)
	{
		_board[y][x] = item;
	}

};




