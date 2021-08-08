#pragma once
#include "Tekstura.h"
#include "DirectionVector.h"

extern const int GAME_WIDTH;
extern const int GAME_HEIGHT;

class GameBall
{
public:
	int x = 0; 
	int y = 0;
	double _ballSpeed = 700;
	SDL_Rect _collisionBox = { 0,0,0,0 };

	GameBall();
	GameBall(int x, int y, double ballSpeed, std::string texturePath);
	void move(double deltaTime);  

	//int getWidth();
	//int getHeight();
	DirectionVector& getDirectionVector();
	Tekstura getTexture();

private:
	int _width = 0;  // i can find it out through tekstura class but just for convenience I put it here too
	int _height = 0;

	Tekstura _ballTexture;
	DirectionVector _direction;
};

