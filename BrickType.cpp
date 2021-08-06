#include "BrickType.h"

int BrickType::index_counter_sequence = 0;

BrickType::BrickType(std::string id, int hp, int score, bool breakable, brickResources* resource) {

	_index = index_counter_sequence++;
	_ID = id;
	_hitpoints = hp;
	_breakScore = score;
	_isBreakable = breakable;
	_brick = resource;

	_breakSound = _brick->getBreakSound();
}

brickResources* BrickType::loseHP()
{
	_hitpoints--;

	if (_hitpoints == 0) {
		Mix_PlayChannel(-1, _breakSound, 0);
	}
	else {
		Mix_PlayChannel(-1, _brick->getHitSound(), 0);
	}

	return nullptr;
}

void BrickType::updateCollisionBox()
{
	_collisionBox = { x,y, _brick->getTexture()->getWidth(), _brick->getTexture()->getHeight() };
}

int BrickType::getIndex()
{
	return _index;
}

int BrickType::getHitpoints()
{
	return _hitpoints;
}

int BrickType::getBreakScore()
{
	return _breakScore;
}

bool BrickType::IsBreakable()
{
	return _isBreakable;
}

bool BrickType::IsKilled()
{
	return _hitpoints <= 0;
}

bool BrickType::changeResource(brickResources* res){
	
	if (res != nullptr) {
		_brick = res;
	}
	return res != nullptr;
}

brickResources* BrickType::getResources()
{
	return _brick;
}

brickResources::brickResources(std::string id, int hp, int breakScore, bool canBeBroken, std::string texturePath, int sirina, int visina, std::string hitSoundPath, std::string breakSoundPath) {
	
	if(!id.empty())
		_originalID = id;
	
	if(hp>0)
		_originalhitpoints = hp;
	
	if(breakScore>0)
		_originalBreakScore = breakScore;
	
	_originalIsBreakable = canBeBroken;
	
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

std::string brickResources::getId()
{
	return _originalID;
}

int brickResources::getHitpoints()
{
	return _originalhitpoints;
}

int brickResources::getBreakScore()
{
	return _originalBreakScore;
}

bool brickResources::getIsBreakable()
{
	return _originalIsBreakable;
}

Tekstura* brickResources::getTexture()
{
	return &_brickTexture;
}

Mix_Chunk* brickResources::getHitSound()
{
	return _hitSound;
}

Mix_Chunk* brickResources::getBreakSound()
{
	return _breakSound;
}

   