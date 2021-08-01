#include "level.h"



Level::Level(int rowCount, int columnCount, int rowSpacing, int columnSpacing, std::string backgroundPath, std::string levelLayout)
{
	_rowCount = rowCount;
	_columnCount = columnCount;
	_rowSpacing = rowSpacing;
	_columnSpacing = columnSpacing;
	_levelLayout = levelLayout;

	_background.loadScaledFromFile(backgroundPath, GAME_WIDTH, GAME_HEIGHT);
}

Level::~Level()
{
	destroyLevel();
}

void Level::destroyLevel()
{
	_background.free();

	_resources.clear();
	_brickList.clear();
}
