#pragma once
#include "Tekstura.h"
#include "DirectionVector.h"

extern const int GAME_WIDTH;
extern const int GAME_HEIGHT;

class GamePad
{
public:
	int x = 0;
	int y = 0;
	double _padSpeed = 700;
	SDL_Rect _collisionBox = { 0,0,0,0 };
	double sideVelocity = 0; // if -1 pad is going left max speed, if 1 pad is going right 

	GamePad();
	GamePad(int x, int y, double padSpeed, std::string texturePath);
	void move(double deltaTime); 

	DirectionVector& getDirectionVector();
	Tekstura getTexture();

private:
	Tekstura _padTexture;
	DirectionVector _direction;

};

