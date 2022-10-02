#include <iostream>
#include "cells.h"
#include "figure.h"
#include <chrono>
#include <thread>


using namespace std;

class BaseCell;
class FieldCell;
class FigureCell;
class Figure;
class TFigure;
class Field;
class TetrisGame;

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

class TetrisGame {

private:
	enum MainMenuOptions { START_GAME, OPTIONS, EXIT };
	int mainMenu() {
		Menu menu({ "Start Game", "Options", "Exit" });
		menu.drawOptions();
		int key;
		while (true)
		{
			menu.drawFrame();

			key = getKey();
			if (key == -1) {
				Sleep(100);
				continue;
			}

			switch (key)
			{
			case UP_ARROW:
				menu.up();
				menu.drawOptions();
				break;
			case DOWN_ARROW:
				menu.down();
				menu.drawOptions();
				break;
			case ENTER:
				system("cls");
				return menu.getSelectedOption();
			default:
				break;
			}
			Sleep(100);
		}
	}
	void play() {

		int key = 0;

		int shiftTime = 500;
		int currentShiftTime = 0;
		bool rotate = true;

		Field* field = new Field(10, 19);
		field->drawFrame();

		Figure* figure = new IFigure;
		Figure* nextFigure = new OFigure;
		Figure* test = new TFigure;
		figure = figure->getRandomFigure();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		nextFigure = nextFigure->getRandomFigure();
		field->drawNextFigure(nextFigure);

		figure->setField(field);
		figure->draw();

		while (true)
		{
			try
			{
				key = getKey();
				if (currentShiftTime > shiftTime) {
					figure->down();
					currentShiftTime = 0;
				}

				if (key == -1) {
					currentShiftTime += 50;
					Sleep(50);
					continue;
				}

				switch (key)
				{
				case SPACE:
					test = figure->clone();
					test->rotate();
					test->clear();
					if (field->checkPlace(test))
					{
						figure->rotate();
					}
					else
					{
						field->drawFrame();
					}
					break;
				case DOWN_ARROW:
					figure->down();
					break;
				case LEFT_ARROW:
					figure->left();
					break;
				case RIGHT_ARROW:
					figure->right();
					break;
				case ESC:
					SetColor(WHITE, BLACK);
					system("cls");
					return;
				default:
					break;
				}
				currentShiftTime += 50;
				Sleep(50);
			}
			catch (...)
			{
				delete figure;
				Figure* temp = new OFigure;
				figure = nextFigure;
				nextFigure = temp;
				delete temp;
				nextFigure = nextFigure->getRandomFigure();
				field->drawNextFigure(nextFigure);
				
				if (!field->checkPlace(figure))
				{
					SetCursorPosition(25, 5);
					cout << "GAME OVER";
					_getch();
				}
				figure->setField(field);

				figure->draw();
				currentShiftTime = 0;
			}
		}
		delete figure;
		delete field;
		delete nextFigure;

	}

	bool work = true;
public:
	void run() {

		while (work)
		{
			switch (mainMenu()) {
			case MainMenuOptions::START_GAME:
				play();
				break;
			case MainMenuOptions::OPTIONS:
				//TODO
				break;
			case MainMenuOptions::EXIT:
				work = false;
				break;

			default:
				break;
			}
		}
	}
};

int main() {

	ShowConsoleCursor(false);
	srand(time(NULL));

	TetrisGame game;
	game.run();
}