#pragma once

#include <iostream>
#include <fstream>

#include "Figure.h"

using namespace std;

struct Camera {
	Point CameraPos = { 0 , 0 };
	float Scale = 1.0;
};

class FigureList
{
private:
	Figure *list;
	unsigned int count;
public:
	FigureList();

	void printList(wchar_t *path, float Scale, Point cameraPos);

	//
	//	Point start, end;
	//	unsigned backgroundColor, borderColor;
	//	int backgroundStyle, borderStyle;
	//	char *type = "";
	//

	Camera readData(wchar_t *path);

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

