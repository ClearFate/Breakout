#include "GameUtilityFunctions.h"

//global game context
const int GAME_WIDTH = 640;
const int GAME_HEIGHT = 480;

TTF_Font* gameFont = NULL;
SDL_Window* gameWindow = NULL;
SDL_Renderer* gameRenderer = NULL;

vector<Level> gameLevelList;
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

	//Update screen
	SDL_RenderPresent(gameRenderer);

	for (auto& lvl : gameLevelList) {
		lvl.destroyLevel();
	}

	getchar();
	GameUtil::close();
	return EXIT_SUCCESS;
}
