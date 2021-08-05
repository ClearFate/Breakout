#include "GamePad.h"

GamePad::GamePad() {

}

GamePad::GamePad(int newX, int newY, double rightDirection, double padSpeed, std::string padTexturePath)
{
    x = newX;
    y = newY;
    _padSpeed = padSpeed;
    _direction.setRightDirection(rightDirection);
    _direction.setUpDirection(0);

    if (!_padTexture.loadScaledFromFile(padTexturePath, GAME_WIDTH / 15, 17)) {  // load ball texture
        printf("Greska prilikom ucitavanja slike game pad-a \"%s\".", padTexturePath.c_str());
    }
    else {
        _width = _padTexture.getWidth();
        _height = _padTexture.getHeight();
    }

    _collisionBox = { x, y, _width, _height };
}


void GamePad::move(double deltaTime)  // deltaTime for frame rate independant movement (if game is capped on only one frame rate then it's not needed but I put it anyway)
{
    // update position of ball and it's collider to new coordinates   
    x += int(_direction.getRightUnitVector() * _padSpeed * deltaTime);
    //y += int(_direction.getUpUnitVector() * _padSpeed * deltaTime);

    //update x and y of collisionBox to new values 
    _collisionBox.x = x;
    _collisionBox.y = y;

}

//int GamePad::getWidth()
//{
//    return _width;
//}
//
//int GamePad::getHeight()
//{
//    return _height;
//}

DirectionVector& GamePad::getDirectionVector()
{
    return _direction;
}

Tekstura GamePad::getTexture()
{
    return _padTexture;
}
