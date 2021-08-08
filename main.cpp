#include "GameUtilityFunctions.h"
#include "GameEvents.h"
#include "GameBall.h"
#include "GameTimer.h"
#include "GamePad.h"
using std::string;

//global game context
const int GAME_WIDTH = 1366;  //1366
const int GAME_HEIGHT = 720;  //720
const int GAME_FRAME_RATE = 60;

#define milisecondsInOneSecond 1000
const int TIME_RESERVED_FOR_ONE_FRAME = milisecondsInOneSecond / GAME_FRAME_RATE;  // its int because were working with miliseconds either way


TTF_Font* gameFont = NULL;
SDL_Window* gameWindow = NULL;
SDL_Renderer* gameRenderer = NULL;

GameBall gameBall;  // loading of textures you can do only after you've initialized SDL subsystems
GamePad gamePad;
vector<Level> gameLevelList;

bool gameOver = false;
int gameScore = 0;
string stringScore = "";
string lvlTekst = "LVL ";
Tekstura levelTextTexture;
Tekstura gameScoreTexture;
Tekstura startTextTexture;

//------------------------------------------------------------
bool gameIsRunning = true;
SDL_Event event;
Level currentGameLevel;

int main(int argc, char* argv[]) {
	
	if (GameUtil::init("Breakout") == false) {
		std::cout << "\nIgra nije uspjela ucitati potrebne podsisteme.\nTerminirano izvrsavanje igre.\n";
		return -1;
	}
	// LOADING OF ALL THE RESOURCES
	int gameScoreCopy = gameScore;
	GameUtil::loadGameFont();
	SDL_Color gameScoreColor = {255,255,255};
	stringScore = std::to_string(gameScore);
	gameScoreTexture.loadBlendedText(stringScore.c_str(), gameScoreColor, 1000);

	GameUtil::loadLevel("levelsXML.xml");
	gameBall = GameBall(GAME_WIDTH / 2 - gameBall.getTexture().getWidth()/2-300, GAME_HEIGHT / 2 - gameBall.getTexture().getHeight() / 2, 450, "images/ball2.png");
	gamePad = GamePad(GAME_WIDTH / 2 - gamePad.getTexture().getWidth()/2, GAME_HEIGHT - 50 - gamePad.getTexture().getHeight() / 2, 450, "images/pad.png");

	int currLvlIndex = 0;
	currentGameLevel = gameLevelList[currLvlIndex];
	lvlTekst += std::to_string(currLvlIndex).c_str();
	levelTextTexture.loadBlendedText(lvlTekst , gameScoreColor, GAME_WIDTH);
	bool pauseScreen = true;

	startTextTexture.loadBlendedText("Press UP arrow to start", gameScoreColor, GAME_WIDTH);

	GameTimer fpsTimer;
	GameTimer deltaTimeTimer;

	// STARTING THE GAME
	while(gameIsRunning){  //game loop
		fpsTimer.Start(); // timer starts here so move and frame cap function later get 
		

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
	
	//very ugly bit of code but done in hurry
	if (!GameUtil::renderBricks(currentGameLevel)) {
		if (currLvlIndex+1 >= gameLevelList.size()) {  // if there are no more lvls to switch to - player wins
			lvlTekst = "Victory";
			levelTextTexture.loadBlendedText(lvlTekst, gameScoreColor, GAME_WIDTH);
			gameIsRunning = false;
			gameOver = true;
		}
		else {
			currentGameLevel = gameLevelList[++currLvlIndex];
			lvlTekst = "LVL ";
			lvlTekst += std::to_string(currLvlIndex).c_str();
			levelTextTexture.loadBlendedText(lvlTekst, gameScoreColor, GAME_WIDTH);
			pauseScreen = true;

			gamePad.x = GAME_WIDTH / 2;

		}
	}
	//------------------------------------------

	gameBall.getTexture().render(gameBall.x, gameBall.y);
	gamePad.getTexture().render(gamePad.x, gamePad.y);
	
	if (gameScore != gameScoreCopy) {
		stringScore = std::to_string(gameScore);
		gameScoreTexture.loadBlendedText(stringScore.c_str(), gameScoreColor, 1000);
		gameScoreCopy = gameScore;
	}
	gameScoreTexture.render(GAME_WIDTH - (gameScoreTexture.getWidth()+20), 5);
	//GameUtil::showBrickCollisionBoxes();
	//GameUtil::showBallAndPadCollisionBoxes();
	//GameUtil::showBallDirectionVector();

	//Update screen
	if (pauseScreen && !gameOver) {
		levelTextTexture.render(GAME_WIDTH / 2 - levelTextTexture.getWidth() / 2, GAME_HEIGHT / 2 - levelTextTexture.getHeight() / 2  - 50);
		startTextTexture.render(GAME_WIDTH / 2 - startTextTexture.getWidth() / 2, GAME_HEIGHT / 2 - startTextTexture.getHeight() / 2);
	}
	if (gameOver) {
		levelTextTexture.render(GAME_WIDTH / 2 - levelTextTexture.getWidth() / 2, GAME_HEIGHT / 2 - levelTextTexture.getHeight() / 2 - 50);
	}

	SDL_RenderPresent(gameRenderer);
	
	int elapsedMiliseconds = fpsTimer.GetTicks();
	if (elapsedMiliseconds < TIME_RESERVED_FOR_ONE_FRAME) {  // to cap game execution to constant 60 fps
		
		SDL_Delay( TIME_RESERVED_FOR_ONE_FRAME - elapsedMiliseconds );
	}

	if (pauseScreen) {
		fpsTimer.Pause();
		deltaTimeTimer.Pause();

		bool startKeyPressed = true;
		while (startKeyPressed) {  // event loop (only active if there are events in the queue)

			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {  // we only care about first DOWN PRESS OF A KEY (when holding a key SDL reports it as multiple presses of same key)
					switch (event.key.keysym.sym) {

					case SDLK_UP:
						startKeyPressed = false;
						break;
					}
				}
			}
		}

		pauseScreen = false;
	}

	} // END OF GAME LOOP
	SDL_Delay(2000);

	for (auto& lvl : gameLevelList) {
		lvl.destroyLevel();
	}
	GameUtil::close();
	return EXIT_SUCCESS;
}
