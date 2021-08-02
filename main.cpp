#include "GameUtilityFunctions.h"

//global game context
const int GAME_WIDTH = 1366;
const int GAME_HEIGHT = 720;

TTF_Font* gameFont = NULL;
SDL_Window* gameWindow = NULL;
SDL_Renderer* gameRenderer = NULL;

vector<Level> gameLevelList;
Tekstura gameBall = Tekstura();
Tekstura gamePad = Tekstura();
//------------------------------------------------------------



int main(int argc, char* argv[]) {

	
	//if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
	//	std::cout << "SDL could not initialise! SDL error: " << SDL_GetError() << std::endl;
	//}
	if (GameUtil::init("Breakout") == false) {
		std::cout << "\nIgra nije uspjela ucitati potrebne podsisteme.\nTerminirano izvrsavanje igre.\n";
		//return -1;
	}
	GameUtil::loadGameFont();

	GameUtil::loadLevel("levelsXML.xml");


	
	//Clear screen
	SDL_RenderClear(gameRenderer);

	//Render texture to screen
	//SDL_RenderCopy(gameRenderer, gameTexture, NULL, NULL);
	GameUtil::renderBricks(gameLevelList[0]);
	gameBall.render(500, 500);
	gamePad.render(GAME_WIDTH / 2, GAME_HEIGHT - 50);

	//Update screen
	SDL_RenderPresent(gameRenderer);


	

	getchar();
	for (auto& lvl : gameLevelList) {
		lvl.destroyLevel();
	}
	GameUtil::close();
	return EXIT_SUCCESS;
}
