#include "field.h"
#include "figure.h"


FieldCell** fieldCell = nullptr;
COORD coord;

class Figure;

Field::Field(int width, int height)
{
	this->width = width;
	this->height = height;
	init();
}

void Field::init()
{
	dispose();
	fieldCell = new FieldCell * [width];
	for (int i = 0; i < width; i++)
	{
		fieldCell[i] = new FieldCell[height];

	}

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			fieldCell[x][y].setCoord({ (short)(x),(short)(y) });
			fieldCell[x][y].setColor(BLACK);
			fieldCell[x][y].setEmpty(true);
		}
	}
}

void Field::draw()
{
	for (int x = 0; x <= width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			fieldCell[x][y].draw();
		}
	}
}

void Field::drawNextFigure(Figure* f)
{
	int coordX = 15;
	int coordY = 0;
	for (int x = coordX; x < coordX + 8; x++)
	{
		for (int y = coordY; y < coordY + 7; y++)
		{
			if (x == coordX or x == coordX + 7 or y == coordY or y == coordY + 6)
			{
				SetCursorPosition(x, y);
				SetColor(ConsoleColor::WHITE, ConsoleColor::RED_FADE);
				std::cout << ' ';
			}
		}
	}

	SetCursorPosition(coordX + 2, coordY);
	SetColor(ConsoleColor::WHITE, ConsoleColor::RED_FADE);
	std::cout << "NEXT";

	for (int x = coordX+1; x < coordX + 7; x++)
	{
		for (int y = coordY+1; y < coordY + 6; y++)
		{
			SetColor(ConsoleColor::WHITE, ConsoleColor::BLACK);
			SetCursorPosition(x, y);
			std::cout << ' ';
		}
	}

	int cellCoordX = 0;
	int cellCoordY = 0;
	int color = 0;

	for (int i = 0; i < FIGURE_CELL_COUNT; i++)
	{
		cellCoordX = f->getCell(i).getCoord().X + coordX - 1;
		cellCoordY = f->getCell(i).getCoord().Y + 2;
		color = f->getCell(i).getColor();
		SetCursorPosition(cellCoordX, cellCoordY);
		SetColor(ConsoleColor::WHITE, (ConsoleColor)color);
		std::cout << ' ';
	}

	SetColor(ConsoleColor::WHITE, ConsoleColor::BLACK);
}

void Field::addFigure(Figure* f)
{
	for (int i = 0; i < FIGURE_CELL_COUNT; i++)
	{
		auto coord = f->getCell(i).getCoord();

		int fieldX = coord.X;
		int fieldY = coord.Y;

		int col = f->getCell(i).getColor();

		fieldCell[fieldX][fieldY].setColor(f->getCell(i).getColor());
		fieldCell[fieldX][fieldY].setEmpty(false);
		fieldCell[fieldX][fieldY].setCoord({ (short)coord.X, (short)coord.Y });
	}
	SetColor(WHITE, BLACK);

	for (int j = height; j > 0; j--)
	{
		if (isRowFull(j))
		{
			deleteFullRow(j);
			SetCursorPosition(25, j);
			j++;
		}
	}
}


void Field::dispose()
{
	if (fieldCell == nullptr)
		return;
	for (int i = 0; i < height; i++)
	{
		delete[] fieldCell[i];
	}
	delete[] fieldCell;
}

Field::~Field()
{
	dispose();
}

void Field::drawFrame() {

	SetCursorPosition(coord.X, coord.Y);
	for (size_t y = 0; y < height+1; y++)
	{
		for (size_t x = 0; x < width+1; x++)
		{
			if (x == width or y == height) {
				SetCursorPosition(x, y);
				SetColor(ConsoleColor::BLACK, ConsoleColor::RED_FADE);
				cout << ' ';
			}
		}
	}
	SetColor(WHITE, BLACK);
}

bool Field::empty(const COORD& coord)
{
	if (coord.X < 0 or coord.Y < 0 or coord.X > width - 1 or coord.Y > height - 1)
		return false;
	return fieldCell[coord.X][coord.Y].FieldCell::isEmpty();
}

bool Field::checkPlace(Figure* f)
{
	for (int i = 0; i < FIGURE_CELL_COUNT; i++)
	{
		if (!empty(f->getCell(i).getCoord()))
			return false;
	}
	return true;
}

bool Field::isRowFull(int index)
{
	bool res = true;
	for (int i = 0; i < width; i++)
	{
		if (fieldCell[i][index - 1].isEmpty())
		{
			return false;
		}
	}
	return res;
}

void Field::deleteFullRow(int row)
{
	for (int x = 0; x < width; x++)
	{
		for (int y = row - 1; y > 0; y--)
		{
			//short cX = fieldCell[x][y].getCoord().X;
			//short cY = fieldCell[x][y].getCoord().Y;

			//int col = fieldCell[x][y - 1].getColor();
			//bool empt = fieldCell[x][y - 1].isEmpty();

			fieldCell[x][y].setColor(fieldCell[x][y - 1].getColor());
			fieldCell[x][y].setEmpty(fieldCell[x][y - 1].isEmpty());
			fieldCell[x][y].draw();
		}
	}

	for (int i = 0; i < width; i++)
	{
		fieldCell[i][0].setColor(BLACK);
		fieldCell[i][0].setEmpty(true);
	}
}

//void Field::drawLine(int line)
//{
//
//	for (int y = 0; y < width; y++)
//	{
//		std::cout << "fieldCell[" << y << "][" << line << "] coord X -> " << fieldCell[y][line].getCoord().X << ", coord Y -> " << fieldCell[y][line].getCoord().Y << std::endl;
//		fieldCell[y][line].draw();
//	}
//}