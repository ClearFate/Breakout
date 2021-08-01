#pragma once
#include <string>
#include "tinyxml2.h"
#include "level.h"
#include <iostream>

extern vector<Level> gameLevelList;

class LevelLoader
{
	static bool loadLevel(std::string XMLpath);
};

