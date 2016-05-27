#include "stdafx.h"
#include "Point.h"

#include <iostream>

CPoint::CPoint()
{
	x = NULL;
	y = NULL;
}

CPoint::CPoint(int x, int y) {
	this->x = x;
	this->y = y;
}

CPoint CPoint::operator+(const CPoint A) {
	return CPoint(x + A.x, y + A.y);
}

CPoint CPoint::operator-(const CPoint A)
{
	return CPoint(x - A.x, y - A.y);
}

int CPoint::GetX()
{
	return x;
}

int CPoint::GetY()
{
	return y;
}

CPoint CPoint::Get()
{
	return CPoint(x, y);
}

CPoint::~CPoint()
{
}

istream & operator>>(istream & Stream, CPoint & point)
{
	Stream >> point.x >> point.y;
	return Stream;
}

ostream & operator<<(ostream & Stream, const CPoint & point)
{
	Stream << point.x << ", " << point.y;
	return Stream;
}

