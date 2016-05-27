#include "stdafx.h"
#include "Figure.h"
#include "Point.h"

Figure::Figure()
{
	start = Point( NULL, NULL ); 
	end = Point ( NULL, NULL );
	type = NULL;
	backgroundColor = RGB(0, 0, 0);
	borderColor = RGB(0, 0, 0);
	backgroundStyle = 0;
	borderStyle = PS_SOLID;
}

Figure::Figure(static Point start, static Point end, static char * type) {
	this->start = start;
	this->end = end;
	this->type = type;
	backgroundColor = RGB(0, 0, 0);
	borderColor = RGB(0, 0, 0);
	backgroundStyle = 0;
	borderStyle = PS_SOLID;
}

Figure::Figure(static Point start, static Point end, static char * type, static unsigned backgroundColor, static unsigned borderColor, static int backgroundStyle, static int borderStyle)
{
	this->start = start;
	this->end = end;
	this->type = type;
	this->backgroundColor = backgroundColor;
	this->borderColor = borderColor; 
	this->backgroundStyle = backgroundStyle;
	this->borderStyle = borderStyle;
}

void Figure::setType(static char * type, int size)
{
	this->type = (char*)malloc(size);
	strcpy_s(this->type, size, type); 
}

void Figure::setStart(Point point)
{
	start = point;
}

void Figure::setEnd(Point point)
{
	end = point;
}

void Figure::setBackColor(unsigned backgroundColor)
{
	this->backgroundColor = backgroundColor;
}

void Figure::setBackStyle(int backgroundStyle)
{
	this->backgroundStyle = backgroundStyle;
}

void Figure::setBorderColor(unsigned borderColor)
{
	this->borderColor = borderColor;
}

void Figure::setBorderStyle(int borderStyle)
{
	this->borderStyle = borderStyle;
}

unsigned Figure::CheckCol(Point mousePos)
{
	if (strcmp(type, "circle") == 0) {
		
	}
	if (strcmp(type, "rectangle") == 0) {
		
	}
	if (strcmp(type, "line") == 0) {

	}
	return -1;
}

BOOL Figure::draw(static HDC hdc, static float Scale)
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
		tmp = MoveToEx(hdc, start.getX() * Scale, start.getY() * Scale, NULL);
		if (!tmp)
			return tmp;
		tmp = LineTo(hdc, end.getX() * Scale, end.getY() * Scale);
	}
	else if (strcmp(type, "rectangle") == 0) {
		tmp = Rectangle(hdc, start.getX() * Scale, start.getY() * Scale, end.getX() * Scale, end.getY() * Scale);
	}
	else if (strcmp(type, "rectangle_rounded") == 0) {
		tmp = RoundRect(hdc, start.getX() * Scale, start.getY()* Scale, end.getX() * Scale, end.getY() * Scale, 10, 10);

	}
	else if (strcmp(type, "ellipse") == 0) {
		tmp = Ellipse(hdc, start.getX() * Scale, start.getY()* Scale, end.getX() * Scale, end.getY() * Scale);
	}

	DeleteObject(hp);
	DeleteObject(hbr);

	return tmp;
}

void Figure::move(static Point oldMousePos, static Point newMousePos)
{
	Point mouseDelta = newMousePos - oldMousePos;
	start = start + mouseDelta;
	end = end + mouseDelta;
}


void Figure::setPosInList(unsigned int value)
{
	posInList = value;
}

unsigned int Figure::getPosInList()
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

unsigned Figure::getBackColor()
{
	return backgroundColor;
}

int Figure::getBackStyle()
{
	return backgroundStyle;
}

unsigned Figure::getBorderColor()
{
	return borderColor;
}

int Figure::getBorderStyle()
{
	return borderStyle;
}

Figure::~Figure()
{
}

ostream & operator<<(ostream & Stream, const Figure & figure)
{
	Stream << figure.type << " {" << endl;
	Stream << "A = " << figure.start << ";\n" << "B = " << figure.end << ";" << endl;
	Stream << "Fill_Color = " << figure.backgroundColor << ";\n" << "Border_Color = " << figure.borderColor << ";" << endl;
	Stream << "Fill_Style = " << figure.backgroundStyle << ";\n" << "Border_Style = " << figure.borderStyle << ";" << endl;
	Stream << "}\n" << endl;

	return Stream;
}

