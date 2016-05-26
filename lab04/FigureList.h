#pragma once

#include <iostream>
#include <fstream>

#include "Figure.h"

using namespace std;

class FigureList
{
private:
	Figure *list;
	unsigned int count;
public:
	FigureList();

	void printList(wchar_t *path);

	//
	//	Point start, end;
	//	unsigned backgroundColor, borderColor;
	//	int backgroundStyle, borderStyle;
	//	char *type = "";
	//

	void readData(wchar_t *path);

	bool checkClick(Point mousePos) {
		
		return false;
	}

	unsigned getLength();
	bool add(Figure figure);
	void drawList(HDC hdc, float Scale);
	bool remove(unsigned int pos); //	пока что не знаю что с этим делать
	void clean();

	~FigureList();
};

