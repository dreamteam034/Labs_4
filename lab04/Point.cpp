#include "stdafx.h"
#include "Point.h"

#include <iostream>

Point::Point()
{
	x = NULL;
	y = NULL;
}

Point::Point(int x, int y) {
	this->x = x;
	this->y = y;
}

Point Point::operator+(const Point A) {
	return Point(x + A.x, y + A.y);
}

Point Point::operator-(const Point A)
{
	return Point(x - A.x, y - A.y);
}

int Point::getX()
{
	return x;
}

int Point::getY()
{
	return y;
}

Point Point::get()
{
	return Point(x, y);
}

Point::~Point()
{
}

istream & operator>>(istream & Stream, Point & point)
{
	Stream >> point.x >> point.y;
	return Stream;
}

ostream & operator<<(ostream & Stream, const Point & point)
{
	Stream << point.x << ", " << point.y;
	return Stream;
}

