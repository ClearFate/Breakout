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
	double _ballSpeed;
	SDL_Rect _collisionBox;

	GameBall();
	GameBall(int x, int y, double upDirection, double rightDirection, double ballSpeed, std::string texturePath);
	void move(double deltaTime);  // to pass delta time calculate how 

	int getWidth();
	int getHeight();
	DirectionVector& getDirectionVector();
	Tekstura getTexture();

private:
	int _width = 0;  // i can find it out through tekstura class but just for convenience I put it here too
	int _height = 0;

	Tekstura _ballTexture = Tekstura();
	DirectionVector _direction;
};

