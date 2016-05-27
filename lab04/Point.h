#pragma once

#include <windows.h>
#include <iostream>

using namespace std; 

class CPoint
{
private: 
	int x, y;
public:
	CPoint();
	CPoint(int x, int y);

	CPoint operator+ (const CPoint A);
	CPoint operator- (const CPoint A);

	int GetX();
	int GetY();
	CPoint Get();

	friend istream& operator>> (istream& Stream, CPoint& point);
	friend ostream& operator<< (ostream& Stream, const CPoint& point);

	~CPoint();
};

