#pragma once
#include "tekstura.h"
#include <string>

class brickResources 
{
public:
	brickResources(std::string texturePath, int sirina, int visina, std::string hitSoundPath, std::string breakSoundPath);  //loads .wav or .ogg vorbis music format
	~brickResources();

	//friend class BrickType; // if brickType in the future will need to change any of the private members - it can but usually they won't be touched after they're loaded 

private:
	Tekstura _brickTexture = Tekstura();
	Mix_Chunk* _hitSound = NULL;
	Mix_Chunk* _breakSound = NULL;
};

class BrickType
{
public:
	BrickType(char id, int hp, int score, bool breakable, brickResources& resource);
	brickResources* loseHP(); //when hit by ball change resources accordingly to number of hp left

private:
	char _ID = 'a';
	int _hitpoints = 1;
	int _breakScore = 1;
	bool _isBreakable = false;

	int x = 0; //position on the lvl
	int y = 0; //position on the lvl

	brickResources* _brick;

	  // TODO nakon svakog nivoa - mora se pozvat procedura za reloadanje tekstura brikova (jer moguce je da na sljedecem nivou budu drugacijih dimenzija)
};

