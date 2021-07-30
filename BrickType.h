#pragma once
#include <string>
#include <SDL_image.h>

class BrickType
{
public:
	BrickType(char id, int hp, int score, bool breakable, std::string putanjaTeksture);
	~BrickType();

	bool loadScaledFromFile(std::string putanja, int duzina, int visina);  // ucitavanje png tekstura i skaliranje na odredjene dimenzije
	void free(); // oslobodjenje zauzetih resursa 

private:
	char _ID;
	int _hitpoints = 1;
	int _breakScore = 1;
	bool _isBreakable;

	SDL_Texture* brickTexture = NULL;  // TODO nakon svakog nivoa - mora se pozvat procedura za reloadanje tekstura brikova (jer moguce je da na sljedecem nivou budu drugacijih dimenzija)

	//SDL_MIXER hitSound = nullptr;
	//breakSound = nullptr;
};

