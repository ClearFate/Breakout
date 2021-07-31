#include "BrickType.h"

BrickType::BrickType(char id, int hp, int score, bool breakable, std::string putanjaTeksture, int sirina, int visina) {
	
	_ID = id;
	_hitpoints = hp;
	_breakScore = score;
	_isBreakable = breakable;
	_brickTexture.loadScaledFromFile(putanjaTeksture, sirina, visina);
}

   