#include "figure.h"

#define FIRST_ROW_FIELD  0
#define FIRST_COLUMN_FIELD 0


void Figure::draw() {
	for (size_t i = 0; i < FIGURE_CELL_COUNT; i++)
	{
		cells[i].draw();
	}
}

int Figure::getRandColor()
{
	srand(time(NULL));
	int color = 0;
	
	do {
		color = 1 + rand() % 15;
	} while (color == 4); // 4 - RED_FADE - color of frame

	return color;
}

void Figure::setField(Field* f)
{
	this->field = f;
}

FigureCell& Figure::getCell(int index)
{
	return cells[index];
}

void Figure::clear()
{
	for (size_t i = 0; i < FIGURE_CELL_COUNT; i++)
	{
		cells[i].clear();
	}
}


void Figure::down() {

	if (field == nullptr) {
		for (size_t i = 0; i < FIGURE_CELL_COUNT; i++)
		{
			cells[i].down();
		}
		return;
	}

	Figure* clone = this->clone();
	clone->down();

	if (!field->checkPlace(clone))
	{
		field->addFigure(this);
		throw "New figure";
	}

	clear();

	for (size_t i = 0; i < FIGURE_CELL_COUNT; i++)
	{
		cells[i].down();
	}

	draw();

}

void Figure::left() {

	if (field == nullptr)
	{
		for (size_t i = 0; i < FIGURE_CELL_COUNT; i++)
		{
			cells[i].left();
		}
		return;
	}

	Figure* clone = this->clone();
	clone->left();

	if (!field->checkPlace(clone))
	{
		return;
	}
	clear();

	for (size_t i = 0; i < FIGURE_CELL_COUNT; i++)
	{
		cells[i].left();
	}
	draw();
}

void Figure::right() {
	if (field == nullptr)
	{
		for (size_t i = 0; i < FIGURE_CELL_COUNT; i++)
		{
			cells[i].right();
		}
		return;
	}

	Figure* clone = this->clone();
	clone->right();

	if (!field->checkPlace(clone))
	{
		return;
	}
	clear();

	for (size_t i = 0; i < FIGURE_CELL_COUNT; i++)
	{
		cells[i].right();
	}
	draw();
}

Figure* Figure::getRandomFigure()
{

	Figure* f = new IFigure;
	int num = rand() % 7;

	switch (num)
	{
	case 0:
		f = new TFigure;
		break;
	case 1:
		f = new IFigure;
		break;
	case 2:
		f = new ZFigure;
		break;
	case 3:
		f = new SFigure;
		break;
	case 4:
		f = new LFigure;
		break;
	case 5:
		f = new JFigure;
		break;
	case 6:
		f = new OFigure;
		break;
	default:
		break;
	}

	return f;
}

void TFigure::init() {
	int color = getRandColor();
	cells[0].setCoord({ 4, 0 });
	cells[0].setColor((ConsoleColor)color);
	cells[1].setCoord({ 3, 1 });
	cells[1].setColor((ConsoleColor)color);
	cells[2].setCoord({ 4, 1 });
	cells[2].setColor((ConsoleColor)color);
	cells[3].setCoord({ 5, 1 });
	cells[3].setColor((ConsoleColor)color);
	currentDirection = Direction::PHASE_1;
}

TFigure::TFigure() : Figure() {
	init();
}


Figure* TFigure::clone()
{
	TFigure* figure = new TFigure();
	for (int i = 0; i < FIGURE_CELL_COUNT; i++)
	{
		figure->cells[i].setColor(cells[i].getColor());
		figure->cells[i].setCoord(cells[i].getCoord());
	}
	figure->currentDirection = currentDirection;
	figure->field = nullptr;
	return figure;
}

void TFigure::clear()
{
	for (size_t i = 0; i < FIGURE_CELL_COUNT; i++)
	{
		cells[i].clear();
	}
}

void TFigure::rotate() {

	clear();

	auto coord0 = cells[0].getCoord();
	auto coord1 = cells[1].getCoord();
	auto coord2 = cells[2].getCoord();
	auto coord3 = cells[3].getCoord();

	switch (currentDirection)
	{
	case Figure::PHASE_1:
		coord0.X++;
		coord0.Y++;
		cells[0].setCoord(coord0);

		coord1.X++;
		coord1.Y--;
		cells[1].setCoord(coord1);

		coord3.X--;
		coord3.Y++;
		cells[3].setCoord(coord3);

		currentDirection = Figure::PHASE_2;
		break;
	case Figure::PHASE_2:
		coord0.X--;
		cells[0].setCoord(coord0);

		coord1.X++;
		cells[1].setCoord(coord1);

		coord2.Y--;
		cells[2].setCoord(coord2);

		coord3.X--;
		coord3.Y -= 2;
		cells[3].setCoord(coord3);

		currentDirection = Figure::PHASE_3;
		break;
	case Figure::PHASE_3:
		coord0.X--;
		cells[0].setCoord(coord0);

		coord1.X--;
		coord1.Y += 2;
		cells[1].setCoord(coord1);

		coord2.Y++;
		cells[2].setCoord(coord2);

		coord3.X++;
		cells[3].setCoord(coord3);

		currentDirection = Figure::PHASE_4;
		break;
	case Figure::PHASE_4:
		coord0.X++;
		coord0.Y--;
		cells[0].setCoord(coord0);

		coord1.X--;
		coord1.Y--;
		cells[1].setCoord(coord1);

		coord3.X++;
		coord3.Y++;
		cells[3].setCoord(coord3);

		currentDirection = Figure::PHASE_1;
		break;
	default:
		break;
	}
	draw();
}

void IFigure::init() {
	int color = getRandColor();
	cells[0].setCoord({ 3 , 0 });
	cells[0].setColor((ConsoleColor)color);
	cells[1].setCoord({ 4 , 0 });
	cells[1].setColor((ConsoleColor)color);
	cells[2].setCoord({ 5 , 0 });
	cells[2].setColor((ConsoleColor)color);
	cells[3].setCoord({ 6 , 0 });
	cells[3].setColor((ConsoleColor)color);
	currentDirection = Direction::PHASE_1;
}

IFigure::IFigure() : Figure() {
	init();
}


Figure* IFigure::clone()
{
	IFigure* figure = new IFigure();
	for (int i = 0; i < FIGURE_CELL_COUNT; i++)
	{
		figure->cells[i].setColor(cells[i].getColor());
		figure->cells[i].setCoord(cells[i].getCoord());
	}
	figure->currentDirection = currentDirection;
	figure->field = nullptr;
	return figure;
}

void IFigure::clear()
{
	for (size_t i = 0; i < FIGURE_CELL_COUNT; i++)
	{
		cells[i].clear();
	}
}

void IFigure::rotate() {

 	clear();

	auto coord0 = cells[0].getCoord();
	auto coord1 = cells[1].getCoord();
	auto coord2 = cells[2].getCoord();
	auto coord3 = cells[3].getCoord();

	switch (currentDirection)
	{
	case Figure::PHASE_1:
		coord0.X += 2;
		cells[0].setCoord(coord0);

		coord1.X++;
		coord1.Y++;
		cells[1].setCoord(coord1);

		coord2.Y += 2;
		cells[2].setCoord(coord2);

		coord3.X--;
		coord3.Y += 3;
		cells[3].setCoord(coord3);

		currentDirection = Figure::PHASE_2;
		break;
	case Figure::PHASE_2:
		coord0.X -= 2;
		cells[0].setCoord(coord0);

		coord1.X--;
		coord1.Y--;
		cells[1].setCoord(coord1);

		coord2.Y -= 2;
		cells[2].setCoord(coord2);

		coord3.X++;
		coord3.Y -= 3;
		cells[3].setCoord(coord3);

		currentDirection = Figure::PHASE_1;
		break;
	default:
		break;
	}
	bool checkCoord0 = coord0.X > 0 and coord0.X < 10 and coord0.Y >0 and coord0.Y < 20;
	bool checkCoord1 = coord1.X > 0 and coord1.X < 10 and coord1.Y >0 and coord1.Y < 20;
	bool checkCoord2 = coord2.X > 0 and coord2.X < 10 and coord2.Y >0 and coord2.Y < 20;
	bool checkCoord3 = coord3.X > 0 and coord3.X < 10 and coord3.Y >0 and coord3.Y < 20;
	
	if (checkCoord0 and checkCoord1 and checkCoord2 and checkCoord3)
	{
		draw();
	}

}

void ZFigure::init() {
	int color = getRandColor();
	cells[0].setCoord({ 3 , 0 });
	cells[0].setColor((ConsoleColor)color);
	cells[1].setCoord({ 4 , 0 });
	cells[1].setColor((ConsoleColor)color);
	cells[2].setCoord({ 4 , 1 });
	cells[2].setColor((ConsoleColor)color);
	cells[3].setCoord({ 5 , 1 });
	cells[3].setColor((ConsoleColor)color);
	currentDirection = Direction::PHASE_1;
}

ZFigure::ZFigure() : Figure() {
	init();
}

Figure* ZFigure::clone()
{
	ZFigure* figure = new ZFigure();
	for (int i = 0; i < FIGURE_CELL_COUNT; i++)
	{
		figure->cells[i].setColor(cells[i].getColor());
		figure->cells[i].setCoord(cells[i].getCoord());
	}
	figure->currentDirection = currentDirection;
	figure->field = nullptr;
	return figure;
}

void ZFigure::clear()
{
	for (size_t i = 0; i < FIGURE_CELL_COUNT; i++)
	{
		cells[i].clear();
	}
}


void ZFigure::rotate() {

	clear();

	auto coord0 = cells[0].getCoord();
	auto coord1 = cells[1].getCoord();
	auto coord2 = cells[2].getCoord();
	auto coord3 = cells[3].getCoord();

	switch (currentDirection)
	{
	case Figure::PHASE_1:
		coord0.X++;
		cells[0].setCoord(coord0);

		coord1.Y++;
		cells[1].setCoord(coord1);

		coord2.X--;
		cells[2].setCoord(coord2);

		coord3.X -= 2;
		coord3.Y++;
		cells[3].setCoord(coord3);

		currentDirection = Figure::PHASE_2;
		break;
	case Figure::PHASE_2:
		coord0.X--;
		cells[0].setCoord(coord0);

		coord1.Y--;
		cells[1].setCoord(coord1);

		coord2.X++;
		cells[2].setCoord(coord2);

		coord3.X += 2;
		coord3.Y--;
		cells[3].setCoord(coord3);

		currentDirection = Figure::PHASE_1;
		break;
	default:
		break;
	}
	draw();
}

void SFigure::init() {
	int color = getRandColor();
	cells[0].setCoord({ 4 , 0 });
	cells[0].setColor((ConsoleColor)color);
	cells[1].setCoord({ 5 , 0 });
	cells[1].setColor((ConsoleColor)color);
	cells[2].setCoord({ 3 , 1 });
	cells[2].setColor((ConsoleColor)color);
	cells[3].setCoord({ 4 , 1 });
	cells[3].setColor((ConsoleColor)color);
	currentDirection = Direction::PHASE_1;
}

SFigure::SFigure() : Figure() {
	init();
}

Figure* SFigure::clone()
{
	SFigure* figure = new SFigure();
	for (int i = 0; i < FIGURE_CELL_COUNT; i++)
	{
		figure->cells[i].setColor(cells[i].getColor());
		figure->cells[i].setCoord(cells[i].getCoord());
	}
	figure->currentDirection = currentDirection;
	figure->field = nullptr;
	return figure;
}

void SFigure::clear()
{
	for (size_t i = 0; i < FIGURE_CELL_COUNT; i++)
	{
		cells[i].clear();
	}
}

void SFigure::rotate() {

	clear();

	auto coord0 = cells[0].getCoord();
	auto coord1 = cells[1].getCoord();
	auto coord2 = cells[2].getCoord();
	auto coord3 = cells[3].getCoord();

	switch (currentDirection)
	{
	case Figure::PHASE_1:
		coord0.Y++;
		cells[0].setCoord(coord0);

		coord1.X--;
		coord1.Y += 2;
		cells[1].setCoord(coord1);

		coord2.Y--;
		cells[2].setCoord(coord2);

		coord3.X--;
		cells[3].setCoord(coord3);

		currentDirection = Figure::PHASE_2;
		break;
	case Figure::PHASE_2:
		coord0.Y--;
		cells[0].setCoord(coord0);

		coord1.X++;
		coord1.Y -= 2;
		cells[1].setCoord(coord1);

		coord2.Y++;
		cells[2].setCoord(coord2);

		coord3.X++;
		cells[3].setCoord(coord3);


		currentDirection = Figure::PHASE_1;
		break;
	default:
		break;
	}
	draw();
}

void LFigure::init() {
	int color = getRandColor();
	cells[0].setCoord({ 4 , 0 });
	cells[0].setColor((ConsoleColor)color);
	cells[1].setCoord({ 4 , 1 });
	cells[1].setColor((ConsoleColor)color);
	cells[2].setCoord({ 4 , 2 });
	cells[2].setColor((ConsoleColor)color);
	cells[3].setCoord({ 5 , 2 });
	cells[3].setColor((ConsoleColor)color);
	currentDirection = Direction::PHASE_1;
}

LFigure::LFigure() : Figure() {
	init();
}

Figure* LFigure::clone()
{
	LFigure* figure = new LFigure();
	for (int i = 0; i < FIGURE_CELL_COUNT; i++)
	{
		figure->cells[i].setColor(cells[i].getColor());
		figure->cells[i].setCoord(cells[i].getCoord());
	}
	figure->currentDirection = currentDirection;
	figure->field = nullptr;
	return figure;
}

void LFigure::clear()
{
	for (size_t i = 0; i < FIGURE_CELL_COUNT; i++)
	{
		cells[i].clear();
	}
}

void LFigure::rotate() {

	clear();

	auto coord0 = cells[0].getCoord();
	auto coord1 = cells[1].getCoord();
	auto coord2 = cells[2].getCoord();
	auto coord3 = cells[3].getCoord();

	switch (currentDirection)
	{
	case Figure::PHASE_1:
		coord0.X++;
		cells[0].setCoord(coord0);

		coord1.Y--;
		cells[1].setCoord(coord1);

		coord2.X--;
		coord2.Y -= 2;
		cells[2].setCoord(coord2);

		coord3.X -= 2;
		coord3.Y--;
		cells[3].setCoord(coord3);

		currentDirection = Figure::PHASE_2;
		break;
	case Figure::PHASE_2:
		coord0.X--;
		coord0.Y += 2;
		cells[0].setCoord(coord0);

		coord1.Y++;
		cells[1].setCoord(coord1);

		coord2.X++;
		cells[2].setCoord(coord2);

		coord3.Y--;
		cells[3].setCoord(coord3);

		currentDirection = Figure::PHASE_3;
		break;
	case Figure::PHASE_3:
		coord0.X--;
		coord0.Y--;
		cells[0].setCoord(coord0);

		coord2.X++;
		coord2.Y++;
		cells[2].setCoord(coord2);

		coord3.X += 2;
		cells[3].setCoord(coord3);

		currentDirection = Figure::PHASE_4;
		break;
	case Figure::PHASE_4:
		coord0.X++;
		coord0.Y--;
		cells[0].setCoord(coord0);

		coord2.X--;
		coord2.Y++;
		cells[2].setCoord(coord2);

		coord3.Y += 2;
		cells[3].setCoord(coord3);

		currentDirection = Figure::PHASE_1;
		break;
	default:
		break;
	}
	draw();
}

void JFigure::init() {
	int color = getRandColor();
	cells[0].setCoord({ 5 , 0 });
	cells[0].setColor((ConsoleColor)color);
	cells[1].setCoord({ 5 , 1 });
	cells[1].setColor((ConsoleColor)color);
	cells[2].setCoord({ 5 , 2 });
	cells[2].setColor((ConsoleColor)color);
	cells[3].setCoord({ 4 , 2 });
	cells[3].setColor((ConsoleColor)color);
	currentDirection = Direction::PHASE_1;
}

JFigure::JFigure() : Figure() {
	init();
}

Figure* JFigure::clone()
{
	JFigure* figure = new JFigure();
	for (int i = 0; i < FIGURE_CELL_COUNT; i++)
	{
		figure->cells[i].setColor(cells[i].getColor());
		figure->cells[i].setCoord(cells[i].getCoord());
	}
	figure->currentDirection = currentDirection;
	figure->field = nullptr;
	return figure;
}

void JFigure::clear()
{
	for (size_t i = 0; i < FIGURE_CELL_COUNT; i++)
	{
		cells[i].clear();
	}
}

void JFigure::rotate() {

	clear();

	auto coord0 = cells[0].getCoord();
	auto coord1 = cells[1].getCoord();
	auto coord2 = cells[2].getCoord();
	auto coord3 = cells[3].getCoord();

	switch (currentDirection)
	{
	case Figure::PHASE_1:
		coord0.X++;
		coord0.Y++;
		cells[0].setCoord(coord0);

		coord2.X--;
		coord2.Y--;
		cells[2].setCoord(coord2);

		coord3.Y -= 2;
		cells[3].setCoord(coord3);

		currentDirection = Figure::PHASE_2;
		break;
	case Figure::PHASE_2:
		coord0.X -= 2;
		coord0.Y++;
		cells[0].setCoord(coord0);

		coord1.X--;
		cells[1].setCoord(coord1);

		coord2.Y--;
		cells[2].setCoord(coord2);

		coord3.X++;
		cells[3].setCoord(coord3);

		currentDirection = Figure::PHASE_3;
		break;
	case Figure::PHASE_3:
		coord0.Y -= 2;
		cells[0].setCoord(coord0);

		coord1.X++;
		coord1.Y--;
		cells[1].setCoord(coord1);

		coord2.X += 2;
		cells[2].setCoord(coord2);

		coord3.X++;
		coord3.Y++;
		cells[3].setCoord(coord3);

		currentDirection = Figure::PHASE_4;
		break;
	case Figure::PHASE_4:
		coord0.X++;
		cells[0].setCoord(coord0);

		coord1.Y++;
		cells[1].setCoord(coord1);

		coord2.X--;
		coord2.Y += 2;
		cells[2].setCoord(coord2);

		coord3.X -= 2;
		coord3.Y++;
		cells[3].setCoord(coord3);

		currentDirection = Figure::PHASE_1;
		break;
	default:
		break;
	}
	draw();
}

void OFigure::init() {
	int color = getRandColor();
	cells[0].setCoord({ 4 , 0 });
	cells[0].setColor((ConsoleColor)color);
	cells[1].setCoord({ 5 , 0 });
	cells[1].setColor((ConsoleColor)color);
	cells[2].setCoord({ 4 , 1 });
	cells[2].setColor((ConsoleColor)color);
	cells[3].setCoord({ 5 , 1 });
	cells[3].setColor((ConsoleColor)color);
	currentDirection = Direction::PHASE_1;
}

OFigure::OFigure() : Figure() {
	init();
}

Figure* OFigure::clone()
{
	OFigure* figure = new OFigure();
	for (int i = 0; i < FIGURE_CELL_COUNT; i++)
	{
		figure->cells[i].setColor(cells[i].getColor());
		figure->cells[i].setCoord(cells[i].getCoord());
	}
	figure->currentDirection = currentDirection;
	figure->field = nullptr;
	return figure;
}

void OFigure::clear()
{
	for (size_t i = 0; i < FIGURE_CELL_COUNT; i++)
	{
		cells[i].clear();
	}
}

void OFigure::rotate() {

}