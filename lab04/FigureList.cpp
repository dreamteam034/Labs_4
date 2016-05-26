﻿#include "stdafx.h"
#include "FigureList.h"


FigureList::FigureList()
{
	count = 0;
	list = NULL;
}

void FigureList::printList(wchar_t *path, float Scale, Point cameraPos)
{
	ofstream out(path);

	out << "Scale = " << Scale << ";" << endl;
	out << "Camera_Pos = " << cameraPos.getX() << ", " << cameraPos.getY() << ";" << endl;
	out << endl;

	if (count > 0) {
		for (int i = 0; i < count; i++) {
			out << list[i];
		}
	}
}

Camera FigureList::readData(wchar_t * path)
{
	ifstream in(path);
	bool inFigureData = false;
	Camera cameraPos;
	Figure figure;
	char c, buffer[32] = "", bufVal[32] = "", secBufVal[32] = "", *bufPtr = buffer, debug[4096];

	while (in >> c) {
		if (isalpha(c) || c == '_') {
			*bufPtr++ = c;
		}
		else if (isdigit(c) || c == '-' || c == '.') {
				*bufPtr++ = c;
		}
		else if (c == '{') {
			*bufPtr = '\0';
			//sprintf_s(debug, "Type: %s", buffer);
			//OutputDebugStringA(debug);
			figure.setType(buffer, sizeof(buffer));
			bufPtr = buffer;
		}
		else if (c == '=') {
			*bufPtr = '\0';
			bufPtr = bufVal;
			//sprintf_s(debug, "Point: %s", buffer);
			//OutputDebugStringA(debug);
		}
		else if (c == ',') {
			*bufPtr = '\0';
			bufPtr = secBufVal;
		}
		else if (c == ';') {
			*bufPtr = '\0';
			if (strcmp(buffer, "A") == 0) {
				figure.setStart({ atoi(bufVal), atoi(secBufVal) });
			}
			else if (strcmp(buffer, "B") == 0) {
				figure.setEnd({ atoi(bufVal), atoi(secBufVal) });
			}
			else if (strcmp(buffer, "Fill_Color") == 0) {
				figure.setBackColor(atoi(bufVal)); 
			}
			else if (strcmp(buffer, "Border_Color") == 0) {
				figure.setBorderColor(atoi(bufVal));
			}
			else if (strcmp(buffer, "Fill_Style") == 0) {
				figure.setBackStyle(atoi(bufVal));
			}
			else if (strcmp(buffer, "Border_Style") == 0) {
				figure.setBorderStyle(atoi(bufVal));
			}
			else if (strcmp(buffer, "Scale") == 0) {
				cameraPos.Scale = (atof(bufVal));
			}
			else if (strcmp(buffer, "Camera_Pos") == 0) {
				cameraPos.CameraPos = { atoi(bufVal), atoi(secBufVal) };
			}

			bufPtr = buffer;
		}
		else if (c == '}') {
			add(figure);
			//sprintf_s(debug, "Found figure: Type = %s; Start = %d, %d; End  = %d, %d; Fill = %u, %d; Border = %u, %d\n", 
			//	"some", 0, 0, 0, 0, figure.getBackColor(), figure.getBackStyle(), figure.getBorderColor(), figure.getBorderStyle());
			//OutputDebugStringA(debug);
			bufPtr = buffer;
		}
	}

	return cameraPos;
}

bool FigureList::add(Figure figure)
{
	Figure * listPtr;
	count++;
	listPtr = (Figure *)realloc(list, count * sizeof(Figure));
	list = listPtr; 
	list[count - 1] = figure;
	list[count - 1].setPosInList(count - 1);
	return true;
}

void FigureList::drawList(HDC hdc, float Scale)
{
	for (int i = 0; i < count; i++) {
		list[i].draw(hdc, Scale);
	}
}

bool FigureList::remove(unsigned int pos)
{
	for (int i = pos; i < count - 1; i++) {
		list[i] = list[i + 1];
		list[i].setPosInList(list[i].getPosInList() - 1);
	}
	count--;
	return true;
}

void FigureList::clean()
{
	for (int i = 0; i < count; i++) {
		list[i] = Figure();
	}
	count = 0;
}

unsigned FigureList::getLength()
{
	return count;
}

FigureList::~FigureList()
{
}
