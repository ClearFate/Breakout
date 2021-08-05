#include "GameEvents.h"
#include "GameUtilityFunctions.h"

void EventUtil::handlePlayerInput(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {  // we only care about first DOWN PRESS OF A KEY (when holding a key SDL reports it as multiple presses of same key)
        switch (e.key.keysym.sym) {

        case SDLK_RIGHT:
            gamePad.getDirectionVector().setRightDirection(1);
            break;

        case SDLK_LEFT:
            gamePad.getDirectionVector().setRightDirection(-1);
            break;
       
        case SDLK_UP:
            gameBall.getDirectionVector().setUpDirection(-1);
            break;

        case SDLK_DOWN:
            gameBall.getDirectionVector().setUpDirection(1);
            break;

        }
    }

    if (e.type == SDL_KEYUP && e.key.repeat == 0) {  
        switch (e.key.keysym.sym) {

        case SDLK_RIGHT:
            gamePad.getDirectionVector().setRightDirection(0);
            break;

        case SDLK_LEFT:
            gamePad.getDirectionVector().setRightDirection(0);
            break;

        case SDLK_UP:
            gameBall.getDirectionVector().setUpDirection(0);
            break;

        case SDLK_DOWN:
            gameBall.getDirectionVector().setUpDirection(0);
            break;

        }
    }
}

void handleBrickAndBallCollision() {
    for (auto& row : currentGameLevel._brickList) {

        for (auto& brick : row) {

            if (GameUtil::checkCollision(gameBall._collisionBox, brick._collisionBox)) {
                Side pointOfContact = GameUtil::returnSideOfCollision(brick._collisionBox, gameBall._collisionBox);

                gameBall.getDirectionVector().perfectBounce(pointOfContact);

                if (pointOfContact == Side::UP) {
                    // put ball to position above brick
                    gameBall.y = brick.y - gameBall.getTexture().getHeight();
                    gameBall._collisionBox.y = gameBall.y;
                }
                else if (pointOfContact == Side::DOWN) {
                    gameBall.y = brick.y + brick._collisionBox.h;
                    gameBall._collisionBox.y = gameBall.y;
                }
                else if (pointOfContact == Side::RIGHT) {
                    gameBall.x = brick.x + brick._collisionBox.w;
                    gameBall._collisionBox.x = gameBall.x;
                }
                else if (pointOfContact == Side::LEFT) {
                    gameBall.x = brick.x - gameBall.getTexture().getWidth();
                    gameBall._collisionBox.x = gameBall.x;
                }
            }
        }
    }
}


void EventUtil::handleGameEvents()
{
    handleBrickAndBallCollision();

}


