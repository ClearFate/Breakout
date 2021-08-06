#include "GameUtilityFunctions.h"
#include "GameEvents.h"
#include "GameBall.h"
#include "GameTimer.h"
#include "GamePad.h"


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
GamePad gamePad;
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
	GameUtil::loadLevel("levelsXML.xml");
	gameBall = GameBall(GAME_WIDTH / 2 - gameBall.getTexture().getWidth()/2, GAME_HEIGHT / 2 - gameBall.getTexture().getHeight() / 2, 1, 1, 450, "images/ball2.png");
	gamePad = GamePad(GAME_WIDTH / 2 - gamePad.getTexture().getWidth()/2, GAME_HEIGHT - 50 - gamePad.getTexture().getHeight() / 2, 0, 450, "images/pad.png");

	int currLvlIndex = 0;
	currentGameLevel = gameLevelList[currLvlIndex];

	GameTimer fpsTimer;
	GameTimer deltaTimeTimer;

	while(gameIsRunning){  //game loop
		//fpsTimer.Start(); // timer starts here so move and frame cap function later get 

		while (SDL_PollEvent(&event)) {  // event loop (only active if there are events in the queue)
			
			if (event.type == SDL_QUIT) {  // pritisak na x ili ALT+F4
				gameIsRunning = false;
			}

			EventUtil::handlePlayerInput(event);
		}  // END OF EVENT LOOP
	
		EventUtil::handleGameEvents();
	// EXECUTE GAME LOGIC
		gameBall.move(deltaTimeTimer.GetTicks() / 1000.);
		gamePad.move(deltaTimeTimer.GetTicks() / 1000.);

		deltaTimeTimer.Start();  // this timer goes right after move calls


	// RENDER TO THE SCREEN
	SDL_RenderClear(gameRenderer);

	// update position of resouces on the screen
	currentGameLevel._background.render(0, 0);
	
	if (!GameUtil::renderBricks(currentGameLevel)) {
		if (currLvlIndex+1 >= gameLevelList.size()) {  // if there are no more lvls to switch to - player wins
			SDL_Delay(2000);
			gameIsRunning = false;
		}
		else {
			currentGameLevel = gameLevelList[++currLvlIndex];
		}
	}

	gameBall.getTexture().render(gameBall.x, gameBall.y);
	gamePad.getTexture().render(gamePad.x, gamePad.y);

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
