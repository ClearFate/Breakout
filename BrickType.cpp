#include "BrickType.h"


BrickType::BrickType(char id, int hp, int score, bool breakable, brickResources& resource) {

	_ID = id;
	_hitpoints = hp;
	_breakScore = score;
	_isBreakable = breakable;
	_brick = &resource;
}

brickResources::brickResources(std::string id, int hp, int breakScore, bool canBeBroken, std::string texturePath, int sirina, int visina, std::string hitSoundPath, std::string breakSoundPath) {
	
	if(!id.empty())
		originalID = id;
	
	if(hp>0)
		originalhitpoints = hp;
	
	if(breakScore>0)
		originalBreakScore = breakScore;
	
	originalIsBreakable = canBeBroken;
	
	_hitSound = Mix_LoadWAV( hitSoundPath.c_str() );
	_breakSound = Mix_LoadWAV( breakSoundPath.c_str() );

	if(! _brickTexture.loadScaledFromFile(texturePath, sirina, visina))
		printf("Failed to load brick texture \"%s\" !\n", texturePath.c_str());

	if (_hitSound == NULL && !hitSoundPath.empty())
		printf("Failed to load hit sound effect \"%s\"! SDL_mixer Error: %s\n", hitSoundPath.c_str(), Mix_GetError());

	if (_breakSound == NULL && !breakSoundPath.empty())
		printf("Failed to load break sound effect \"%s\"! SDL_mixer Error: %s\n", breakSoundPath.c_str(), Mix_GetError());

}

brickResources::~brickResources() {
	free();
}

void brickResources::free()
{
	_brickTexture.free();
	Mix_FreeChunk(_hitSound);  //if _hitSound is already nullptr does this throw exception ?
	Mix_FreeChunk(_breakSound);
}

   