#include "level.h"


Level::Level()
{
	
}

Level::Level(int rowCount, int columnCount, int rowSpacing, int columnSpacing, std::string backgroundPath)
{
	_rowCount = rowCount;
	_columnCount = columnCount;
	_rowSpacing = rowSpacing;
	_columnSpacing = columnSpacing;

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

brickResources* Level::findMatchingResourceById(std::string id)
{
	brickResources* result = nullptr;
	for (auto& it : _resources) {

		if (it->getId().compare(id) == 0) {
			result = it;
			break;
		}
	}

	return result;
}

int Level::getRowCount()
{
	return _rowCount;
}

int Level::getColumnCount()
{
	return _columnCount;
}

int Level::getRowSpacing()
{
	return _rowSpacing;
}

int Level::getColumnSpacing()
{
	return _columnSpacing;
}
