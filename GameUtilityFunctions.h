#pragma once
#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "tinyxml2.h"
#include "level.h"
#include "GameBall.h"
#include "GamePad.h"

extern const int GAME_WIDTH;
extern const int GAME_HEIGHT;

extern vector<Level> gameLevelList;
extern TTF_Font* gameFont;
extern SDL_Window* gameWindow;
extern SDL_Renderer* gameRenderer;
extern GamePad gamePad;
extern Level currentGameLevel;
extern GameBall gameBall;

namespace GameUtil {

	bool init(std::string nazivIgre);
	bool loadGameFont();
	bool loadLevel(std::string XMLpath);
	bool renderBricks(Level& lvl);
	bool checkCollision(SDL_Rect a, SDL_Rect b);
	Side returnSideOfCollision(SDL_Rect brickBox, SDL_Rect ballBox);
	void showBrickCollisionBoxes();
	void showBallAndPadCollisionBoxes();
	void showBallDirectionVector();
	void close();
	
}



