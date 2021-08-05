#include "GameBall.h"

GameBall::GameBall() {
    // do fucking nothing
}

GameBall::GameBall(int x, int y, double upDirection, double rightDirection, double ballSpeed, std::string ballTexturePath)
{
    _x = x;
    _y = y;
    _ballSpeed = ballSpeed;
    _direction.setRightDirection(rightDirection);
    _direction.setUpDirection(upDirection);
    
    if (! _ballTexture.loadScaledFromFile(ballTexturePath, 20, 20)) {  // load ball texture
        printf("Greska prilikom ucitavanja slike lopte \"%s\".", ballTexturePath.c_str());
    }
    else {
        _width = _ballTexture.getWidth();
        _height = _ballTexture.getHeight();
    }

    _collisionBox = { _x, _y, _width, _height };
}


void GameBall::move(double deltaTime)  // deltaTime for frame rate independant movement (if game is capped on only one frame rate then it's not needed but I put it anyway)
{
    // update position of ball and it's collider to new coordinates
    int rDiff = _direction.getRightUnitVector() * _ballSpeed * deltaTime;
    int uDiff = _direction.getUpUnitVector() * _ballSpeed * deltaTime;
    
    _x = _x + rDiff;
    _y = _y + uDiff;

    //printf("R: %d  U: %d  SPD %lf  D %lf\n", rDiff, uDiff, _ballSpeed, deltaTime);

    _collisionBox = { _x, _y, _width,  _height };

}

int GameBall::getWidth()
{
    return _width;
}

int GameBall::getHeight()
{
    return _height;
}

DirectionVector& GameBall::getDirectionVector()
{
    return _direction;
}

Tekstura GameBall::getTexture()
{
    return _ballTexture;
}
