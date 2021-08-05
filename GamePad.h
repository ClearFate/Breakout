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

	GamePad();
	GamePad(int x, int y, double rightDirection, double padSpeed, std::string texturePath);
	void move(double deltaTime); 

	//int getWidth();
	//int getHeight();
	DirectionVector& getDirectionVector();
	Tekstura getTexture();

private:
	int _width = 0;  // i can find it out through tekstura class but just for convenience I put it here too
	int _height = 0;  // when creating game pad object don't use this ones bcz they're default ones before instantiation (use _padTexture.getWidth() instead)

	Tekstura _padTexture;
	DirectionVector _direction;

};

