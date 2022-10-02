#pragma once
#include "cells.h"
#include "field.h"
#include <time.h>
#include <stdlib.h>

const int FIGURE_CELL_COUNT = 4;

class Figure {
protected:
	enum Direction { PHASE_1, PHASE_2, PHASE_3, PHASE_4 };
	FigureCell cells[FIGURE_CELL_COUNT];
	Direction currentDirection = PHASE_1;
	virtual void init() = 0;
	Field* field = nullptr;
	int getRandColor();
public:
	void draw();
	virtual Figure* clone() = 0;
	virtual void rotate() = 0;

	void setField(Field* f);

	FigureCell& getCell(int index);

	void clear();

	void down();
	void left();
	void right();

	Figure* getRandomFigure();
};

class TFigure : public Figure {
protected:
	void init() override;
public:
	TFigure();

	virtual Figure* clone() override;

	void clear();

	void rotate() override;

};

class IFigure : public Figure {
protected:
	void init() override;
public:
	IFigure();

	virtual Figure* clone() override;

	void clear();

	void rotate() override;

};

class ZFigure : public Figure {
protected:
	void init() override;
public:
	ZFigure();

	virtual Figure* clone() override;

	void clear();

	void rotate() override;

};

class SFigure : public Figure {
protected:
	void init() override;
public:
	SFigure();

	virtual Figure* clone() override;

	void clear();

	void rotate() override;

};

class LFigure : public Figure {
protected:
	void init() override;
public:
	LFigure();

	virtual Figure* clone() override;

	void clear();

	void rotate() override;

};

class JFigure : public Figure {
protected:
	void init() override;
public:
	JFigure();

	virtual Figure* clone() override;

	void clear();

	void rotate() override;

};

class OFigure : public Figure {
protected:
	void init() override;
public:
	OFigure();

	virtual Figure* clone() override;

	void clear();

	void rotate() override;

};