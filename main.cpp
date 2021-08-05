#include "GameUtilityFunctions.h"
#include "GameEvents.h"
#include "GameBall.h"
#include "GameTimer.h"


//global game context
const int GAME_WIDTH = 1366;  //1366
const int GAME_HEIGHT = 720;  //720
const int GAME_FRAME_RATE = 60;

#define milisecondsInOneSecond 1000
const int TIME_RESERVED_FOR_ONE_FRAME = milisecondsInOneSecond / GAME_FRAME_RATE;  // its int because were working with miliseconds either way


TTF_Font* gameFont = NULL;
SDL_Window* gameWindow = NULL;
SDL_Renderer* gameRenderer = NULL;

vector<Level> gameLevelList;
GameBall gameBall;  // loading of textures you can do only after you've initialized SDL subsystems
Tekstura gamePad;
//------------------------------------------------------------
bool gameIsRunning = true;
SDL_Event event;
Level currentGameLevel;


int main(int argc, char* argv[]) {

	if (GameUtil::init("Breakout") == false) {
		std::cout << "\nIgra nije uspjela ucitati potrebne podsisteme.\nTerminirano izvrsavanje igre.\n";
		return -1;
	}
	GameUtil::loadGameFont();
	gameBall = GameBall(GAME_WIDTH / 2 - gameBall.getWidth()/2, GAME_HEIGHT / 2 - gameBall.getHeight() / 2, 0, 0, 200, "images/ball2.png");
	GameUtil::loadGamePad(GAME_WIDTH / 15, 17);
	GameUtil::loadLevel("levelsXML.xml");

	currentGameLevel = gameLevelList[0];
	GameTimer fpsTimer;
	GameTimer deltaTimeTimer;
	

	while(gameIsRunning){  //game loop
		//fpsTimer.Start(); // timer starts here so move and frame cap function later get 

		while (SDL_PollEvent(&event)) {  // event loop
			
			if (event.type == SDL_QUIT) {  // pritisak na x ili ALT+F4
				gameIsRunning = false;
			}

			EventUtil::handlePlayerInput(event);
			EventUtil::handleGameEvents();

		}  // END OF EVENT LOOP
	

	// EXECUTE GAME LOGIC
		gameBall.move(deltaTimeTimer.GetTicks() / 1000.);
		deltaTimeTimer.Start();


	// RENDER TO THE SCREEN
	SDL_RenderClear(gameRenderer);

	// update position of resouces on the screen
	currentGameLevel._background.render(0, 0);
	GameUtil::renderBricks(currentGameLevel);
	gameBall.getTexture().render(gameBall._x, gameBall._y);
	gamePad.render(GAME_WIDTH / 2, GAME_HEIGHT - 50);

	GameUtil::showBrickCollisionBoxes();
	GameUtil::showBallAndPadCollisionBoxes();

	//Update screen
	SDL_RenderPresent(gameRenderer);
	
	int elapsedMiliseconds = fpsTimer.GetTicks();
	if (elapsedMiliseconds < TIME_RESERVED_FOR_ONE_FRAME) {  // to cap game execution to constant 60 fps
		
		SDL_Delay( TIME_RESERVED_FOR_ONE_FRAME - elapsedMiliseconds );
	}

	} // END OF GAME LOOP

	for (auto& lvl : gameLevelList) {
		lvl.destroyLevel();
	}
	GameUtil::close();
	return EXIT_SUCCESS;
}
