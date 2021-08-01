#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Level.h"

//global game context
const int GAME_WIDTH = 640;
const int GAME_HEIGHT = 480;

TTF_Font* gameFont = NULL;
SDL_Window* gameWindow = NULL;
SDL_Renderer* gameRenderer = NULL;

vector<Level> gameLevelList;
//------------------------------------------------------------


void close()
{
	//Destroy window    
	SDL_DestroyRenderer( gameRenderer );
	gameRenderer = NULL;
	SDL_DestroyWindow( gameWindow );
	gameWindow = NULL;
	TTF_CloseFont( gameFont );
	gameFont = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[]) {


	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL could not initialise! SDL error: " << SDL_GetError() << std::endl;
	}

	

	
	//Clear screen
	SDL_RenderClear(gameRenderer);

	//Render texture to screen
	//SDL_RenderCopy(gameRenderer, gameTexture, NULL, NULL);

	//Update screen
	SDL_RenderPresent(gameRenderer);


	getchar();

	close();
	return EXIT_SUCCESS;
}
