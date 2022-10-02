#include "cells.h"

void BaseCell::_drawUseColor(ConsoleColor color) {
	SetCursorPosition(coord);
	SetColor(WHITE, color);
	std::cout << ' ';
}

void BaseCell::setCoord(const COORD& coord)
{
	this->coord = coord;
}

COORD BaseCell::getCoord() const {
	return coord;
}

ConsoleColor BaseCell::getColor()
{
	return color;
}

void BaseCell::setColor(const ConsoleColor color) {
	this->color = color;
}
void BaseCell::draw() {
	_drawUseColor(color);
}
void BaseCell::clear() {
	_drawUseColor(BLACK);
}

void FieldCell::down()
{
	coord.Y++;
}
bool FieldCell::isEmpty()
{
	return this->empty;
}
void FieldCell::setEmpty(bool e)
{
	this->empty = e;
}
void FieldCell::drawFieldCell()
{
	COORD newCoord;
	newCoord.X = coord.X + 1;
	newCoord.Y = coord.Y + 1;
	SetCursorPosition(newCoord);
	SetColor(WHITE, color);
	std::cout << ' ';
}




void FigureCell::left() {
	coord.X--;
}
void FigureCell::right() {
	coord.X++;
}
