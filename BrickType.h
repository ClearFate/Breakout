#pragma once
#include "tekstura.h"


class BrickType
{
public:
	BrickType(char id, int hp, int score, bool breakable, std::string putanjaTeksture, int sirina, int visina);



private:
	char _ID = 'a';
	int _hitpoints = 1;
	int _breakScore = 1;
	bool _isBreakable = false;

	Tekstura _brickTexture = Tekstura();  // TODO nakon svakog nivoa - mora se pozvat procedura za reloadanje tekstura brikova (jer moguce je da na sljedecem nivou budu drugacijih dimenzija)

	//SDL_MIXER hitSound = nullptr;
	//breakSound = nullptr;
};

