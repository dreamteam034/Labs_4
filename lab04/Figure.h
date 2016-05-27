#pragma once

#include <windows.h>
#include "Point.h"
#include <iostream>

using namespace std;

class CFigure
{
private:
	CPoint start, end;
	unsigned backgroundColor, borderColor;
	int backgroundStyle, borderStyle ;
	char *type = "";
	bool selected;

	unsigned int posInList; 
public:
	CFigure();
	CFigure(static CPoint start, static CPoint end, static char *type);
	CFigure(static CPoint start, static CPoint end, static char *type, static unsigned backgroundColor, static unsigned borderColor, static int backgroundStyle, static int borderStyle);

	// Я очень долгое время не хотел это так писать, но ничего не сделаешь

	void setType(char *type, int size);
	void setStart(CPoint point);
	void setEnd(CPoint point);
	void setBackColor(unsigned backgroundColor);
	void setBackStyle(int backgroundStyle);
	void setBorderColor(unsigned borderColor);
	void setBorderStyle(int borderStyle);

	unsigned int CheckCol(CPoint mousePos);

	BOOL Draw(static HDC hdc, static float Zoom);
	void move(static CPoint oldMousePos, static CPoint newMousePos);
	void destroy();

	void setPosInList(static unsigned int value);

	unsigned int getPosInList();
	char * getType();
	CPoint getStart();
	CPoint getEnd();
	unsigned getBackColor();
	int getBackStyle();
	unsigned getBorderColor();
	int getBorderStyle();

	friend ostream& operator<< (ostream& Stream, const CFigure& figure);

	~CFigure();
};

