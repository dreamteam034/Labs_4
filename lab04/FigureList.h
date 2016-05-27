#pragma once

#include <iostream>
#include <fstream>

#include "Figure.h"

using namespace std;

struct CCamera {
	CPoint CameraPos = { 0 , 0 };
	float Zoom = 1.0;
};

class CFigureList
{
private:
	CFigure *list;
	unsigned int count;
public:
	CFigureList();

	void PrintList(wchar_t *wcPathP, float Zoom, CPoint CameraPos);

	//
	//	Point start, end;
	//	unsigned backgroundColor, borderColor;
	//	int backgroundStyle, borderStyle;
	//	char *type = "";
	//

	CCamera ReadData(wchar_t *wcPathP);

	bool checkClick(CPoint mousePos) {
		
		return false;
	}

	unsigned GetLength();
	bool Add(CFigure figure);
	void DrawList(HDC hdc, float Scale);
	bool Remove(unsigned int pos); //	пока что не знаю что с этим делать
	void Clean();

	~CFigureList();
};

