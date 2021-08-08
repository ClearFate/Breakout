#include "GameBall.h"

GameBall::GameBall() {

}

GameBall::GameBall(int newX, int newY, double ballSpeed, std::string ballTexturePath)
{
    x = newX;
    y = newY;
    _ballSpeed = ballSpeed;
    _direction.rotateDirection(-45); //direction vector defaults are to x-axis unit vector so here we rotate that default direction
    
    if (! _ballTexture.loadScaledFromFile(ballTexturePath, 20, 20)) {  // load ball texture
        printf("Greska prilikom ucitavanja slike lopte \"%s\".", ballTexturePath.c_str());
    }
    else {
        _width = _ballTexture.getWidth();
        _height = _ballTexture.getHeight();
    }

    _collisionBox = { x, y, _width, _height };
}


void GameBall::move(double deltaTime)  // deltaTime for frame rate independant movement (if game is capped on only one frame rate then it's not needed but I put it anyway)
{
    // update position of ball and it's collider to new coordinates   
    x += int(_direction.getRightUnitVector() * _ballSpeed * deltaTime);
    y += int(_direction.getUpUnitVector() * _ballSpeed * deltaTime);

    //update x and y of collisionBox to new values 
    _collisionBox.x = x;
    _collisionBox.y = y;

}

DirectionVector& GameBall::getDirectionVector()
{
    return _direction;
}

Tekstura GameBall::getTexture()
{
    return _ballTexture;
}
