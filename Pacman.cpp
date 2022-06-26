#include "Pacman.h"

void Pacman::move(Board& b, Direction direction)
{
		int currX = _p.getX();
		int currY = _p.getY();
		int boardCols = b.getBoardCols();
		int boardRows = b.getBoardRows();
		char currItem = b.getBoardItem(currX, currY);
		switch (direction) {
		case UP: // UP
			if (b.isValidMove(currX, currY - 1) && currY>0) // Is the next move different than wall?
			{
				char itemInNextStep = b.getBoardItem(currX, currY - 1);
				if (itemInNextStep == FOOD)
					b.minusOneFood();
				_p.draw(SPACE);
				b.setBoardItem(currX, currY, SPACE);
				b.setBoardItem(currX, currY - 1, PACMAN);
				_p.move(currX, currY - 1);
				_p.draw(PACMAN);
				if (currY-1 == 0 && b.isValidMove(currX, boardRows-1)) // Is this a tunnel?
				{
					if (b.isFood(currX, boardRows - 1))
						b.minusOneFood();
					_p.draw(SPACE);
					b.setBoardItem(currX, currY, SPACE);
					_p.move(currX, boardRows - 1);
					_p.draw(PACMAN);
					b.setBoardItem(currX, boardRows - 1, PACMAN);
				}
			}
			else
				_dir = STAY;
			break;
		case DOWN: // DOWN
			if (b.isValidMove(currX, currY + 1) && currY < boardRows-1)
			{
				char itemInNextStep = b.getBoardItem(currX, currY+1);
				if (b.isFood(currX, currY+1))
					b.minusOneFood();
				_p.draw(SPACE);
				b.setBoardItem(currX, currY, SPACE);
				b.setBoardItem(currX, currY + 1, PACMAN);
				_p.move(currX, currY + 1);
				_p.draw(PACMAN);
				if ((currY+1 == boardRows-1) && b.isValidMove(currX, 0))
				{
					if (b.isFood(currX, 0))
						b.minusOneFood();
					_p.draw(SPACE);
					b.setBoardItem(currX, currY + 1, SPACE);
					_p.move(currX, 0);
					_p.draw(PACMAN);
					b.setBoardItem(currX, 0, PACMAN);
				}
			}
			else
				_dir = STAY;
			break;
		case LEFT: // LEFT
			if (b.isValidMove(currX - 1, currY) && currX > 0)
			{
				char itemInNextStep = b.getBoardItem(currX - 1, currY);
				if (b.isFood(currX - 1, currY))
					b.minusOneFood();
				_p.draw(SPACE);
				b.setBoardItem(currX, currY, SPACE);
				b.setBoardItem(currX - 1, currY, PACMAN);
				_p.move(currX - 1, currY);
				_p.draw(PACMAN);
				if ((currX-1 == 0) && b.isValidMove(boardCols-1, currY))
				{
					if (b.isFood(boardCols - 1, currY))
						b.minusOneFood();
					_p.draw(SPACE);
					b.setBoardItem(0, currY, SPACE);
					_p.move(boardCols - 1, currY);
					_p.draw(PACMAN);
					b.setBoardItem(boardCols - 1, currY, PACMAN);
				}
			}
			else
				_dir = STAY;
			break;
		case RIGHT: // RIGHT
			if (b.isValidMove(currX + 1, currY) && currX < boardCols-1)
			{
				char itemInNextStep = b.getBoardItem(currX + 1, currY);
				if (b.isFood(currX + 1, currY))
					b.minusOneFood();
				_p.draw(SPACE);
				b.setBoardItem(currX, currY, SPACE);
				b.setBoardItem(currX + 1, currY, PACMAN);
				_p.move(currX + 1, currY);
				_p.draw(PACMAN);
				if ((currX + 1 == boardCols - 1) && (b.isValidMove(0, currY)))
				{
					if (b.isFood(0, currY))
						b.minusOneFood();
					_p.draw(SPACE);
					b.setBoardItem(currX + 1, currY, SPACE);
					_p.move(0, currY);
					_p.draw(PACMAN);
					b.setBoardItem(0, currY, PACMAN);
				}
			}
			else
				_dir = STAY;
			break;
		default:
		{
			_p.draw(PACMAN);
			b.setBoardItem(currX, currY, PACMAN);
		}
		}
}




Direction Pacman::getDirection(char key)const // Get a key from the user, and check if its WASXD
{
		for (int i = 0; i < 5; ++i)
		{
			if (key == pacmanKeys[i] || key == pacmanKeys[i] + 32)
				return (Direction)i;
		}
		return illgal_key_pressed;

}

