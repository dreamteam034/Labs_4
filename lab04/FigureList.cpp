#include "stdafx.h"
#include "FigureList.h"


CFigureList::CFigureList()
{
	count = 0;
	list = NULL;
}

void CFigureList::PrintList(wchar_t *path, float Scale, CPoint cameraPos)
{
	ofstream out(path);

	out << "Scale = " << Scale << ";" << endl;
	out << "Camera_Pos = " << cameraPos.GetX() << ", " << cameraPos.GetY() << ";" << endl;
	out << endl;

	if (count > 0) {
		for (int i = 0; i < count; i++) {
			out << list[i];
		}
	}
}

CCamera CFigureList::ReadData(wchar_t * path)
{
	ifstream in(path);
	bool inFigureData = false;
	CCamera cameraPos;
	CFigure figure;
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
				cameraPos.Zoom = (atof(bufVal));
			}
			else if (strcmp(buffer, "Camera_Pos") == 0) {
				cameraPos.CameraPos = { atoi(bufVal), atoi(secBufVal) };
			}

			bufPtr = buffer;
		}
		else if (c == '}') {
			Add(figure);
			//sprintf_s(debug, "Found figure: Type = %s; Start = %d, %d; End  = %d, %d; Fill = %u, %d; Border = %u, %d\n", 
			//	"some", 0, 0, 0, 0, figure.getBackColor(), figure.getBackStyle(), figure.getBorderColor(), figure.getBorderStyle());
			//OutputDebugStringA(debug);
			bufPtr = buffer;
		}
	}

	return cameraPos;
}

bool CFigureList::Add(CFigure figure)
{
	CFigure * listPtr;
	count++;
	listPtr = (CFigure *)realloc(list, count * sizeof(CFigure));
	list = listPtr; 
	list[count - 1] = figure;
	list[count - 1].setPosInList(count - 1);
	return true;
}

void CFigureList::DrawList(HDC hdc, float Scale)
{
	for (int i = 0; i < count; i++) {
		list[i].Draw(hdc, Scale);
	}
}

bool CFigureList::Remove(unsigned int pos)
{
	for (int i = pos; i < count - 1; i++) {
		list[i] = list[i + 1];
		list[i].setPosInList(list[i].getPosInList() - 1);
	}
	count--;
	return true;
}

void CFigureList::Clean()
{
	for (int i = 0; i < count; i++) {
		list[i] = CFigure();
	}
	count = 0;
}

unsigned CFigureList::GetLength()
{
	return count;
}

CFigureList::~CFigureList()
{
}
