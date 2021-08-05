#pragma once
#include <SDL.h>
#include "Level.h"
#include "GameBall.h"
#include "GamePad.h"

extern bool gameIsRunning;
extern SDL_Window* gameWindow;
extern SDL_Renderer* gameRenderer;

extern vector<Level> gameLevelList;
extern Level currentGameLevel;

extern GameBall gameBall;
extern GamePad gamePad;

namespace EventUtil {

	void handlePlayerInput(SDL_Event& e);
	void handleGameEvents();
}

