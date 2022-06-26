#include "Point.h"

void Point::draw(char ch)const {
	gotoxy(_x, _y);
	cout << ch << endl;
}

bool Point::operator==(const Point& pnt)
{
	if (_x == pnt.getX() && _y == pnt.getY())
		return true;
	return false;
}