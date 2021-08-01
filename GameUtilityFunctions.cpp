#include "GameUtilityFunctions.h"

using namespace tinyxml2;
using namespace std;

const char* extractAttribute(XMLElement* element, const char* attr) {  // helper func to avoid errors when extracting xml
	const char* result = element->Attribute(attr);
	if (result != nullptr){
		return result;
	}
	else {
		return "";
	}
}

bool GameUtil::loadGameFont() {
	gameFont = TTF_OpenFont("font/DejaVuMathTeXGyre.ttf", 24);
	if (gameFont == NULL) {
		printf("Greska pri ucitavanju game fonta: %s \n", TTF_GetError());
	}
	return gameFont != NULL;
}


bool GameUtil::loadLevel(string XMLpath)  
{
	// test tinyXML
	XMLDocument doc(true, COLLAPSE_WHITESPACE);  // to have nicely formated level layout when queried

	// load xml level
	if (doc.LoadFile( XMLpath.c_str() )) {
		cout << "Error opening xml document (" << doc.ErrorID() << ")" << endl;
		return false;
	}

	XMLElement* levelData = doc.FirstChildElement("Level");

	while (levelData != nullptr) {

		int newRowCount = atoi(extractAttribute(levelData,"RowCount"));
		int newColumnCount = atoi(extractAttribute(levelData,"ColumnCount"));
		int newRowSpacing = atoi(extractAttribute(levelData,"RowSpacing"));
		int newColumnSpacing = atoi(extractAttribute(levelData, "ColumnSpacing"));
		const char* newBgPath = levelData->Attribute("BackgroundTexture");
		const char* newLvlLayout = levelData->FirstChildElement("Bricks")->GetText();
		string newBackgroundPath = "";
		string newLevelLayout = "";

		if (newBgPath != nullptr)
			newBackgroundPath = string(newBgPath);

		if (newLvlLayout != nullptr)
			newLevelLayout = string(newLvlLayout);

		Level newLevel = Level(newRowCount, newColumnCount, newRowSpacing, newColumnSpacing, newBackgroundPath, newLevelLayout);

		// calculate brick size according to game window size, number of bricks and spacing between them
		int columnSpacesCount = newColumnCount + 1;
		int rowSpacesCount = newRowCount + 1;
		int brickPlacementArea = GAME_HEIGHT * 0.7;

		int brickWidth = (GAME_WIDTH - (columnSpacesCount) * newColumnSpacing) / newColumnCount;
		int brickHeight = (brickPlacementArea - (rowSpacesCount)*newRowSpacing) / newRowCount;
		//----------------------------------------------------------------------------------------------

		XMLElement* brickData = levelData->FirstChildElement("BrickTypes")->FirstChildElement("BrickType");

		while (brickData != nullptr) {

			string newBrickId = "";
			int newHitPoints = atoi(extractAttribute(brickData,"HitPoints"));
			int newBreakScore = atoi(extractAttribute(brickData,"BreakScore"));  // jako krhko cim ne nadje atribut ovo puca
			bool newIsBreakable = true;
			const char* brickId = brickData->Attribute("Id");

			if (brickId != nullptr){
				newBrickId = string(brickId);
				
				if (newBrickId.compare("I") == 0) {
					newIsBreakable = false;
				}
			}
			
			string newBrickTexturePath = "";
			string newBrickHitSoundPath = "";
			string newBrickBreakSoundPath = "";

			const char* brickTexturePath = brickData->Attribute("Texture");
			const char* brickHitSoundPath = brickData->Attribute("HitSound");
			const char* brickBreakSoundPath = brickData->Attribute("BreakSound");

			if (brickTexturePath != nullptr)
				newBrickTexturePath = string(brickTexturePath);

			if (brickHitSoundPath != nullptr)
				newBrickHitSoundPath = string(brickHitSoundPath);

			if (brickBreakSoundPath != nullptr)
				newBrickBreakSoundPath = string(brickBreakSoundPath);

			//SDL LOAD MEDIA RESOURCES PART
			brickResources* newBrickResource = new brickResources(newBrickId, newHitPoints, newBreakScore, newIsBreakable, newBrickTexturePath, brickWidth, brickHeight, newBrickHitSoundPath, newBrickBreakSoundPath);  // allocated on heap

			newLevel.addResource(newBrickResource);
			//------------------------------------------

			//cout << brickData->Attribute("Id") << " ";

			brickData = brickData->NextSiblingElement("BrickType");
		}
		cout << endl;
		//Level newLoadedLevel = Level(int rowCount, int columnCount, int rowSpacing, int columnSpacing, std::string backgroundPath, std::string levelLayout);

		//cout << "==========================================================================================\n";
		//cout << levelData->FirstChildElement("Bricks")->GetText() << endl;
		//cout << "==========================================================================================\n";
		gameLevelList.push_back(newLevel);

		levelData = levelData->NextSiblingElement("Level");
	}

}

void GameUtil::close()
{
	//Destroy window   
	if(gameRenderer != nullptr)
		SDL_DestroyRenderer(gameRenderer);
	gameRenderer = nullptr;

	if(gameWindow != nullptr)
		SDL_DestroyWindow(gameWindow);
	gameWindow = nullptr;
	
	if(gameFont != nullptr)
		TTF_CloseFont(gameFont);
	gameFont = nullptr;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}

bool GameUtil::init(std::string nazivIgre) {
	bool uspjelo = true;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0) {
		printf("Greska prilikom inicializacije podsistema VIDEO | AUDIO | TIMER.\n");
		uspjelo = false;
	}
	else {

		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!\n");
		}
		
		gameWindow = SDL_CreateWindow(nazivIgre.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GAME_WIDTH, GAME_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (gameWindow == nullptr) {
			printf("Greska prilikom stvaranja prozora!\n");
			uspjelo = false;
		}
		else {
			gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gameRenderer == NULL) {
				printf("Greska prilikom stvaranja renderera!\n");
				uspjelo = false;
			}
			else {
				SDL_SetRenderDrawColor(gameRenderer, 0xff, 0xff, 0xff, 0xff); // bijela boja

				int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("Greska prilikom ucitavanja podsistema za PNG i JPG slike: %s\n", IMG_GetError());
					uspjelo = false;
				}

				if (TTF_Init() == -1) {
					printf("Greska prilikom inicializacije SDL_ttf: %s\n", TTF_GetError());
					uspjelo = false;
				}

				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
					printf("Greska prilikom inicializacije SDL_mixera: %s\n", Mix_GetError());
					uspjelo = false;
				}
			}

			//TODO - ucitaj neki default font koji bude igra koristila
		}
	}

	return uspjelo;
}

