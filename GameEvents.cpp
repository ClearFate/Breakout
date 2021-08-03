#include "GameEvents.h"

void EventUtil::handleUserInput(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {

        case SDLK_RIGHT:
            currentGameLevel = gameLevelList[1];
            SDL_RenderPresent(gameRenderer);
            break;


        }
    }
}