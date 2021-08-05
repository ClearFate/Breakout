#pragma once
#include <SDL.h>
#include "Level.h"

extern SDL_Window* gameWindow;
extern SDL_Renderer* gameRenderer;

extern vector<Level> gameLevelList;
extern Level currentGameLevel;

namespace EventUtil {

	void handlePlayerInput(SDL_Event& e);
}

