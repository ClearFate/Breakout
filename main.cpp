#include <iostream>
#include <SDL.h>
#include "tinyxml2.h"

using namespace tinyxml2;
using namespace std;

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
	

	cout << "opa" << endl;



	getchar();
	return EXIT_SUCCESS;
}
