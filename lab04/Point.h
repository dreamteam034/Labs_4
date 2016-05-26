#pragma once

#include <windows.h>
#include <iostream>

using namespace std; 

class Point
{
private: 
	int x, y;
public:
	Point();
	Point(int x, int y);

	Point operator+ (const Point A);
	Point operator- (const Point A);

	int getX();
	int getY();
	Point get();

	friend istream& operator>> (istream& Stream, Point& point);
	friend ostream& operator<< (ostream& Stream, const Point& point);

	~Point();
};

