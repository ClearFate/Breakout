#pragma once
#include "tekstura.h"
#include <string>
#include <SDL_mixer.h>

extern int gameScore;

class brickResources //flyweight
{
public:
	brickResources(std::string id, int hp, int breakScore, bool canBeBroken, std::string texturePath, int sirina, int visina, std::string hitSoundPath, std::string breakSoundPath);  //loads .wav or .ogg vorbis music format
	~brickResources();
	void free();

	std::string getId();
	int getHitpoints();
	int getBreakScore();
	bool getIsBreakable();
	//friend class BrickType; // if brickType in the future will need to change any of the private members - it can but usually they won't be touched after they're loaded 
	Tekstura* getTexture();
	Mix_Chunk* getHitSound();
	Mix_Chunk* getBreakSound();

private:
	std::string _originalID = "_";
	int _originalhitpoints = 50;
	int _originalBreakScore = 50;
	bool _originalIsBreakable = true;

	Tekstura _brickTexture = Tekstura();
	Mix_Chunk* _hitSound = NULL;
	Mix_Chunk* _breakSound = NULL;
};

class BrickType
{
public:
	BrickType(std::string id, int hp, int score, bool breakable, brickResources* resource);
	void loseHP(); //when hit by ball change resources accordingly to number of hp left
	void updateCollisionBox();

	int getIndex();
	int getHitpoints();
	int getBreakScore();
	bool IsBreakable();
	bool IsKilled();
	bool changeResource(brickResources* res);
	brickResources* getResources();

	int x = 0; //position on the lvl
	int y = 0; //position on the lvl
	SDL_Rect _collisionBox;

private:
	int _index = 0;
	static int index_counter_sequence;

	std::string _ID = "_";
	int _hitpoints = 0;
	int _breakScore = 1;
	bool _isBreakable = true;

	brickResources* _brick;
	Mix_Chunk* _breakSound = nullptr;
	

};

