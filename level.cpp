#include "level.h"


Level::Level(int rowCount, int columnCount, int rowSpacing, int columnSpacing, std::string backgroundPath, std::string levelLayout)
{
	_rowCount = rowCount;
	_columnCount = columnCount;
	_rowSpacing = rowSpacing;
	_columnSpacing = columnSpacing;
	_levelLayout = levelLayout;

	if (!_background.loadScaledFromFile(backgroundPath, GAME_WIDTH, GAME_HEIGHT)) {
		printf("Greska prilikom ucitavanja pozadinske slike za nivo \"%s\".", backgroundPath.c_str());
	}
}

void Level::destroyLevel()
{
	_background.free();
	_brickList.clear();
	//_resources.clear();

	for (auto& res : _resources) {
		delete res;
	}

	
}

void Level::addResource(brickResources* res)
{
	_resources.push_back(res);
}
