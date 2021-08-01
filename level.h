#pragma once
#include "Tekstura.h"
#include "BrickType.h"
#include <vector>
using std::vector;

extern const int GAME_WIDTH;
extern const int GAME_HEIGHT;

class Level
{
public:
	Level(int rowCount, int columnCount, int rowSpacing, int columnSpacing, std::string backgroundPath, std::string levelLayout);
	~Level();
	void destroyLevel();

	//populateResources();

private:
	int _rowCount = 1;
	int _columnCount = 1;
	int _rowSpacing = 1;
	int _columnSpacing = 1;

	std::string _levelLayout = "";

	vector<brickResources> _resources;  // level holds reference to every texture/sound needed to build level just once
	vector < vector<BrickType*> > _brickList; //bricks on the level

	Tekstura _background = Tekstura();
};

