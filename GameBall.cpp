#include "GameBall.h"

GameBall::GameBall() {

}

GameBall::GameBall(int newX, int newY, double upDirection, double rightDirection, double ballSpeed, std::string ballTexturePath)
{
    x = newX;
    y = newY;
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

    _collisionBox = { x, y, _width, _height };
}


void GameBall::move(double deltaTime)  // deltaTime for frame rate independant movement (if game is capped on only one frame rate then it's not needed but I put it anyway)
{
    // update position of ball and it's collider to new coordinates   
    x += int(_direction.getRightUnitVector() * _ballSpeed * deltaTime);
    y += int(_direction.getUpUnitVector() * _ballSpeed * deltaTime);

    //printf("R: %d  U: %d  SPD %lf  D %lf\n", rDiff, uDiff, _ballSpeed, deltaTime);

    //update x and y of collisionBox to new values 
    _collisionBox.x = x;
    _collisionBox.y = y;

}

//int GameBall::getWidth()
//{
//    return _width;
//}
//
//int GameBall::getHeight()
//{
//    return _height;
//}

DirectionVector& GameBall::getDirectionVector()
{
    return _direction;
}

Tekstura GameBall::getTexture()
{
    return _ballTexture;
}
