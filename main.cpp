#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "tinyxml2.h"

using namespace tinyxml2;
using namespace std;

TTF_Font* gameFont = NULL;
SDL_Window* gameWindow = NULL;
SDL_Renderer* gameRenderer = NULL;

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
	SDL_Quit();
}

int main(int argc, char* argv[]) {


	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "SDL could not initialise! SDL error: " << SDL_GetError() << endl;
	}

	// test tinyXML
	XMLDocument doc(true,COLLAPSE_WHITESPACE);

	// load xml level
	if (doc.LoadFile("levelsXML.xml")) {
		cout << "Error opening xml document!" << endl;
		return doc.ErrorID();
	}

	XMLElement* level = doc.FirstChildElement("Level"); 

	while(level != nullptr) {
		cout << "==========================================================================================\n";
		cout << level->FirstChildElement("Bricks")->GetText() << endl;
		cout << "==========================================================================================\n";
		level = level->NextSiblingElement("Level");
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
