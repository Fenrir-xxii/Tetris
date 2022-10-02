#pragma once
#include "menu.h"

class BaseCell
{
protected:
	COORD coord = { 0, 0 };
	ConsoleColor color = WHITE;
	//void _drawUseColor(ConsoleColor color);
public:
	void setCoord(const COORD& coord);
	void _drawUseColor(ConsoleColor color);
	COORD getCoord() const;

	ConsoleColor getColor();

	void setColor(const ConsoleColor color);
	void draw();
	void clear();
};

class FieldCell : public BaseCell
{
protected:
	bool empty = true;
public:
	FieldCell() = default;
	FieldCell(FieldCell& f)
	{
		f.coord = this->coord;
		f.color = this->color;
		f.coord = this->coord;
		f.empty = this->empty;
	}
	void down();
	bool isEmpty();
	void setEmpty(bool e);
	void drawFieldCell();
};


class FigureCell : public FieldCell {

public:

	void left();
	void right();
};
