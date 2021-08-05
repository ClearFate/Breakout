#include "GameBall.h"

GameBall::GameBall(int x, int y, double upDirection, double rightDirection, double ballSpeed, std::string ballTexturePath)
{
    _x = x;
    _y = y;
    _ballSpeed = ballSpeed;
    _direction.setDirection(upDirection, rightDirection);
    
    if (! _ballTexture.loadScaledFromFile(ballTexturePath, 20, 20)) {  // load ball texture
        printf("Greska prilikom ucitavanja slike lopte \"%s\".", ballTexturePath.c_str());
    }
}

GameBall::GameBall()
{
}

void GameBall::move()
{
}

Tekstura GameBall::getTexture()
{
    return _ballTexture;
}
