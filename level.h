#pragma once
#include "Tekstura.h"
#include "BrickType.h"
#include <vector>
using std::vector;

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

	vector<BrickType> brickTypes;  // level holds reference to every texture needed to build level just once
	vector < vector<BrickType*> > brickList; //bricks on the level

	Tekstura background = Tekstura();
};

