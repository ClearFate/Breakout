#include "GamePad.h"

GamePad::GamePad() {

}

GamePad::GamePad(int newX, int newY, double padSpeed, std::string padTexturePath)
{
    x = newX;
    y = newY;
    _padSpeed = padSpeed;

    if (!_padTexture.loadScaledFromFile(padTexturePath, GAME_WIDTH / 10, 17)) {  // load ball texture
        printf("Greska prilikom ucitavanja slike game pad-a \"%s\".", padTexturePath.c_str());
    }

    _collisionBox = { x, y, _padTexture.getWidth(), _padTexture.getHeight() };
}


void GamePad::move(double deltaTime)  // deltaTime for frame rate independant movement (if game is capped on only one frame rate then it's not needed but I put it anyway)
{
    // update position of ball and it's collider to new coordinates   
    x += int(sideVelocity * _padSpeed * deltaTime);

    //update x and y of collisionBox to new values 
    _collisionBox.x = x;
    _collisionBox.y = y;

}
DirectionVector& GamePad::getDirectionVector()
{
    return _direction;
}

Tekstura GamePad::getTexture()
{
    return _padTexture;
}
