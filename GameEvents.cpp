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

        }
    }
}

void handleCollision_BricksAndBall() {
    

    for (auto& row : currentGameLevel._brickList) {

        for (auto& brick : row) {

            if (!brick.IsKilled()) {
                if (GameUtil::checkCollision(gameBall._collisionBox, brick._collisionBox)) {
                    if (brick.IsBreakable())
                        brick.loseHP();
                        brickResources* newRes = currentGameLevel.findBrickByHP(brick.getHitpoints());
                        brick.changeResource(newRes);

                    // additional checks to determine how to bounce the ball off off the brick
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
}

void handleCollision_PadAndGameWindow() {
    
    if (GameUtil::checkCollision(gamePad._collisionBox, {-1, -1, 1, GAME_HEIGHT+1})) {  // if pad collides with left border of window
        gamePad.x = 0;
        gamePad._collisionBox.x = 0;
    }
    else if (GameUtil::checkCollision(gamePad._collisionBox, { GAME_WIDTH, -1, 1, GAME_HEIGHT+1 })) {  // if pad collides with right border of window
        gamePad.x = GAME_WIDTH - gamePad.getTexture().getWidth();
        gamePad._collisionBox.x = gamePad.x;
    }
}

void handleCollision_PadAndBall() {

    if (GameUtil::checkCollision(gameBall._collisionBox, gamePad._collisionBox)) {  // if ball collides with left border of window
        Side pointOfContact = GameUtil::returnSideOfCollision(gamePad._collisionBox, gameBall._collisionBox);

        //gameBall.getDirectionVector().perfectBounce(pointOfContact);

        if (pointOfContact == Side::UP) {
            // add zone logic here

            //-------------------------------
            gameBall.getDirectionVector().perfectBounce(pointOfContact);  // if white zone
            // put ball to position above brick
            gameBall.y = gamePad.y - gameBall.getTexture().getHeight();
            gameBall._collisionBox.y = gameBall.y;
        }
        else if (pointOfContact == Side::RIGHT) {
            gameBall.x = gamePad.x + gamePad._collisionBox.w;
            gameBall._collisionBox.x = gameBall.x;
        }
        else if (pointOfContact == Side::LEFT) {
            gameBall.x = gamePad.x - gameBall.getTexture().getWidth();
            gameBall._collisionBox.x = gameBall.x;
        }
    
    }
}

void handleCollision_BallAndGameWindow() {

    if (GameUtil::checkCollision(gameBall._collisionBox, { -50, -1, 50, GAME_HEIGHT + 2 })) {  // if ball collides with left border of window
        gameBall.x = 0;
        gameBall._collisionBox.x = 0;
        gameBall.getDirectionVector().perfectBounce(Side::RIGHT);
    }
    else if (GameUtil::checkCollision(gameBall._collisionBox, { GAME_WIDTH, -1, 50, GAME_HEIGHT + 2 })) {  // if ball collides with right border of window
        gameBall.x = GAME_WIDTH - gameBall.getTexture().getWidth();
        gameBall._collisionBox.x = gameBall.x;
        gameBall.getDirectionVector().perfectBounce(Side::LEFT);
    }
    else if (GameUtil::checkCollision(gameBall._collisionBox, { -1, -50, GAME_WIDTH + 2, 50 })) {  // if ball collides with top border of window
        gameBall.y = 0;
        gameBall._collisionBox.y = 0;
        gameBall.getDirectionVector().perfectBounce(Side::DOWN);
    }
    else if (GameUtil::checkCollision(gameBall._collisionBox, { -1, GAME_HEIGHT, GAME_WIDTH + 2, 50 })) {  // if ball collides with bottom border of window end the game
        gameIsRunning = false;
    }
}




void EventUtil::handleGameEvents()
{
    handleCollision_PadAndGameWindow();
    handleCollision_BallAndGameWindow();

    handleCollision_BricksAndBall();
    handleCollision_PadAndBall();

}


