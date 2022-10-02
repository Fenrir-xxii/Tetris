#pragma once
#include "cells.h"

class Figure;

class Field
{
protected:
	int width;
	int height;
	FieldCell** fieldCell = nullptr;
	COORD coord;
public:

	Field(int width, int height);

	void init();

	void draw();

	void drawNextFigure(Figure* f);

	void addFigure(Figure* f);

	void dispose();

	~Field();

	void drawFrame();

	bool empty(const COORD& coord);

	bool checkPlace(Figure* f);
	bool isRowFull(int index);
	void deleteFullRow(int row);
	//void drawLine(int line);
};