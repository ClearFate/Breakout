#pragma once
#include "Tekstura.h"
#include "DirectionVector.h"

extern const int GAME_WIDTH;
extern const int GAME_HEIGHT;

class GameBall
{
public:
	int _x = 0; 
	int _y = 0;
	double _ballSpeed = 10;
	SDL_Rect collisionBox;

	GameBall();
	GameBall(int x, int y, double upDirection, double rightDirection, double ballSpeed, std::string texturePath);
	void move();

	Tekstura getTexture();

private:
	Tekstura _ballTexture = Tekstura();
	DirectionVector _direction;
};

