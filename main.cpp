#include "GameUtilityFunctions.h"
#include "GameEvents.h"
#include "GameBall.h"

//global game context
const int GAME_WIDTH = 1366;
const int GAME_HEIGHT = 720;

TTF_Font* gameFont = NULL;
SDL_Window* gameWindow = NULL;
SDL_Renderer* gameRenderer = NULL;

vector<Level> gameLevelList;
GameBall gameBall;
Tekstura gamePad = Tekstura();
//------------------------------------------------------------
bool gameIsRunning = true;
SDL_Event event;
Level currentGameLevel;


int main(int argc, char* argv[]) {

	
	//if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
	//	std::cout << "SDL could not initialise! SDL error: " << SDL_GetError() << std::endl;
	//}
	if (GameUtil::init("Breakout") == false) {
		std::cout << "\nIgra nije uspjela ucitati potrebne podsisteme.\nTerminirano izvrsavanje igre.\n";
		//return -1;
	}
	GameUtil::loadGameFont();
	gameBall = GameBall(GAME_WIDTH / 2, GAME_HEIGHT / 2, -1, 0, 2, "images/ball2.png");
	GameUtil::loadGamePad(GAME_WIDTH / 15, 17);
	GameUtil::loadLevel("levelsXML.xml");

	currentGameLevel = gameLevelList[0];

	while(gameIsRunning){  //game loop
	
		while (SDL_PollEvent(&event)) {  // event loop
			
			if (event.type == SDL_QUIT) {  // pritisak na x ili ALT+F4
				gameIsRunning = false;
			}

			EventUtil::handlePlayerInput(event);

		}
	
	// refresh renderer
	SDL_RenderClear(gameRenderer);

	// update position of resouces on the screen
	currentGameLevel._background.render(0, 0);
	GameUtil::renderBricks(currentGameLevel);
	gameBall.getTexture().render(gameBall._x, gameBall._y);
	gamePad.render(GAME_WIDTH / 2, GAME_HEIGHT - 50);

	//Update screen
	SDL_RenderPresent(gameRenderer);


	}

	for (auto& lvl : gameLevelList) {
		lvl.destroyLevel();
	}
	GameUtil::close();
	return EXIT_SUCCESS;
}
