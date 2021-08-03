#pragma once
#include <SDL.h>

extern SDL_Window* gameWindow;
extern SDL_Renderer* gameRenderer;

namespace EventUtil {

	void handleGameEvents(SDL_Event& e);
}

