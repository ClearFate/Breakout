#include "BrickType.h"


BrickType::BrickType(char id, int hp, int score, bool breakable, brickResources& resource) {

	_ID = id;
	_hitpoints = hp;
	_breakScore = score;
	_isBreakable = breakable;
	_brick = &resource;
}

brickResources::brickResources(std::string texturePath, int sirina, int visina, std::string hitSoundPath, std::string breakSoundPath) {
	_brickTexture.loadScaledFromFile(texturePath, sirina, visina);
	_hitSound = Mix_LoadWAV( hitSoundPath.c_str() );
	_breakSound = Mix_LoadWAV( breakSoundPath.c_str() );

	if (_hitSound == NULL)
		printf("Failed to load hit sound effect \"%s\"! SDL_mixer Error: %s\n", hitSoundPath.c_str(), Mix_GetError());

	if (_breakSound == NULL)
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

   