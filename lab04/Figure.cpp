#include "stdafx.h"
#include "Figure.h"
#include "Point.h"

CFigure::CFigure()
{
	start = CPoint( NULL, NULL ); 
	end = CPoint ( NULL, NULL );
	type = NULL;
	backgroundColor = RGB(0, 0, 0);
	borderColor = RGB(0, 0, 0);
	backgroundStyle = 0;
	borderStyle = PS_SOLID;
}

CFigure::CFigure(static CPoint start, static CPoint end, static char * type) {
	this->start = start;
	this->end = end;
	this->type = type;
	backgroundColor = RGB(0, 0, 0);
	borderColor = RGB(0, 0, 0);
	backgroundStyle = 0;
	borderStyle = PS_SOLID;
}

CFigure::CFigure(static CPoint start, static CPoint end, static char * type, static unsigned backgroundColor, static unsigned borderColor, static int backgroundStyle, static int borderStyle)
{
	this->start = start;
	this->end = end;
	this->type = type;
	this->backgroundColor = backgroundColor;
	this->borderColor = borderColor; 
	this->backgroundStyle = backgroundStyle;
	this->borderStyle = borderStyle;
}

void CFigure::setType(static char * type, int size)
{
	this->type = (char*)malloc(size);
	strcpy_s(this->type, size, type); 
}

void CFigure::setStart(CPoint point)
{
	start = point;
}

void CFigure::setEnd(CPoint point)
{
	end = point;
}

void CFigure::setBackColor(unsigned backgroundColor)
{
	this->backgroundColor = backgroundColor;
}

void CFigure::setBackStyle(int backgroundStyle)
{
	this->backgroundStyle = backgroundStyle;
}

void CFigure::setBorderColor(unsigned borderColor)
{
	this->borderColor = borderColor;
}

void CFigure::setBorderStyle(int borderStyle)
{
	this->borderStyle = borderStyle;
}

unsigned CFigure::CheckCol(CPoint mousePos)
{
	if (strcmp(type, "circle") == 0) {
		
	}
	if (strcmp(type, "rectangle") == 0) {
		
	}
	if (strcmp(type, "line") == 0) {

	}
	return -1;
}

BOOL CFigure::Draw(static HDC hdc, static float Scale)
{
	BOOL tmp = true;
	wchar_t buffer[64];

	HPEN hp = CreatePen(borderStyle, 0, borderColor);
	HBRUSH hbr = CreateHatchBrush(backgroundStyle, backgroundColor);

	SelectObject(hdc, hp);

	if (backgroundStyle == -1) {
		SetDCBrushColor(hdc, backgroundColor);
		SelectObject(hdc, GetStockObject(DC_BRUSH));
	}
	else
		SelectObject(hdc, hbr);

	if (strcmp(type, "line") == 0) {
		tmp = MoveToEx(hdc, start.GetX() * Scale, start.GetY() * Scale, NULL);
		if (!tmp)
			return tmp;
		tmp = LineTo(hdc, end.GetX() * Scale, end.GetY() * Scale);
	}
	else if (strcmp(type, "rectangle") == 0) {
		tmp = Rectangle(hdc, start.GetX() * Scale, start.GetY() * Scale, end.GetX() * Scale, end.GetY() * Scale);
	}
	else if (strcmp(type, "rectangle_rounded") == 0) {
		tmp = RoundRect(hdc, start.GetX() * Scale, start.GetY()* Scale, end.GetX() * Scale, end.GetY() * Scale, 10, 10);

	}
	else if (strcmp(type, "ellipse") == 0) {
		tmp = Ellipse(hdc, start.GetX() * Scale, start.GetY()* Scale, end.GetX() * Scale, end.GetY() * Scale);
	}

	DeleteObject(hp);
	DeleteObject(hbr);

	return tmp;
}

void CFigure::move(static CPoint oldMousePos, static CPoint newMousePos)
{
	CPoint mouseDelta = newMousePos - oldMousePos;
	start = start + mouseDelta;
	end = end + mouseDelta;
}


void CFigure::setPosInList(unsigned int value)
{
	posInList = value;
}

unsigned int CFigure::getPosInList()
{
	return posInList;
}

/*
char * Figure::getType()
{
	return type;
}

Point Figure::getStart()
{
	return start;
}

Point Figure::getEnd()
{
	return end;
}
*/

unsigned CFigure::getBackColor()
{
	return backgroundColor;
}

int CFigure::getBackStyle()
{
	return backgroundStyle;
}

unsigned CFigure::getBorderColor()
{
	return borderColor;
}

int CFigure::getBorderStyle()
{
	return borderStyle;
}

CFigure::~CFigure()
{
}

ostream & operator<<(ostream & Stream, const CFigure & figure)
{
	Stream << figure.type << " {" << endl;
	Stream << "A = " << figure.start << ";\n" << "B = " << figure.end << ";" << endl;
	Stream << "Fill_Color = " << figure.backgroundColor << ";\n" << "Border_Color = " << figure.borderColor << ";" << endl;
	Stream << "Fill_Style = " << figure.backgroundStyle << ";\n" << "Border_Style = " << figure.borderStyle << ";" << endl;
	Stream << "}\n" << endl;

	return Stream;
}

