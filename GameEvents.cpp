#include "GameEvents.h"

void EventUtil::handlePlayerInput(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {  // we only care about first DOWN PRESS OF A KEY (when holding a key SDL reports it as multiple presses of same key)
        switch (e.key.keysym.sym) {

        case SDLK_RIGHT:
            gameBall.getDirectionVector().setRightDirection(1);
            break;

        case SDLK_LEFT:
            gameBall.getDirectionVector().setRightDirection(-1);
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
            gameBall.getDirectionVector().setRightDirection(0);
            break;

        case SDLK_LEFT:
            gameBall.getDirectionVector().setRightDirection(0);
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

void EventUtil::handleGameEvents(SDL_Event& e)
{
}
