#pragma once

#include <windows.h>
#include "Point.h"
#include <iostream>

using namespace std;

class Figure
{
private:
	Point start, end;
	unsigned backgroundColor, borderColor;
	int backgroundStyle, borderStyle ;
	char *type = "";
	bool selected;

	unsigned int posInList; 
public:
	Figure();
	Figure(static Point start, static Point end, static char *type);
	Figure(static Point start, static Point end, static char *type, static unsigned backgroundColor, static unsigned borderColor, static int backgroundStyle, static int borderStyle);

	// Я очень долгое время не хотел это так писать, но ничего не сделаешь

	void setType(char *type, int size);
	void setStart(Point point);
	void setEnd(Point point);
	void setBackColor(unsigned backgroundColor);
	void setBackStyle(int backgroundStyle);
	void setBorderColor(unsigned borderColor);
	void setBorderStyle(int borderStyle);

	unsigned int CheckCol(Point mousePos);

	BOOL draw(static HDC hdc, static float Scale);
	void move(static Point oldMousePos, static Point newMousePos);
	void destroy();

	void setPosInList(static unsigned int value);

	unsigned int getPosInList();
	char * getType();
	Point getStart();
	Point getEnd();
	unsigned getBackColor();
	int getBackStyle();
	unsigned getBorderColor();
	int getBorderStyle();

	friend ostream& operator<< (ostream& Stream, const Figure& figure);

	~Figure();
};

