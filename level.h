#pragma once
#include <SDL.h>

class level
{
public:
	level();
	~level();

private:
	int _rowCount = 1;
	int _columnCount = 1;
	int _rowSpacing = 1;
	int _columnSpacing = 1;

	SDL_Texture* background = NULL;
};

