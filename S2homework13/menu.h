#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "console.h"

using namespace std;


class Menu {
private:
	int activeOption = 0;
	vector<string> options;
	size_t getMaxItemSize() const;
	size_t getFrameWidth() const;
	size_t getFrameHeight() const;
public:
	Menu(const vector<string>& options);
	void drawFrame();

	void drawOptions();

	void down();

	void up();

	int getSelectedOption() const;
};

