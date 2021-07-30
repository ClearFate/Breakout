#include "BrickType.h"

BrickType::BrickType(char id, int hp, int score, bool breakable, std::string putanjaTeksture) {
	
	_ID = id;
	_hitpoints = hp;
	_breakScore = score;
	_isBreakable = breakable;
	//TODO add calculate width height according to game screen and tiles (rows and columns) and spacing


	//brickTexture = loadScaledFromFile(putanjaTeksture, );
}

void BrickType::free() {

}

bool BrickType::loadScaledFromFile(std::string putanja, int duzina, int visina) {

}