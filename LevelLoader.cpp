#include "LevelLoader.h"

using namespace tinyxml2;
using namespace std;


bool LevelLoader::loadLevel(string XMLpath)  // path rn is levelsXML.xml
{
	// test tinyXML
	XMLDocument doc(true, COLLAPSE_WHITESPACE);

	// load xml level
	if (doc.LoadFile( XMLpath.c_str() )) {
		cout << "Error opening xml document (" << doc.ErrorID() << ")" << endl;
		return false;
	}

	XMLElement* levelData = doc.FirstChildElement("Level");

	while (levelData != nullptr) {

		int newRowCount = atoi(levelData->Attribute("RowCount"));
		int newColumnCount = atoi(levelData->Attribute("ColumnCount"));
		int newRowSpacing = atoi(levelData->Attribute("RowSpacing"));
		int newColumnSpacing = atoi(levelData->Attribute("ColumnSpacing"));
		string newBackgroundPath = levelData->Attribute("BackgroundTexture");
		string newLevelLayout = levelData->FirstChildElement("Bricks")->GetText();
		
		
		//Level newLoadedLevel = Level(int rowCount, int columnCount, int rowSpacing, int columnSpacing, std::string backgroundPath, std::string levelLayout);

		//cout << "==========================================================================================\n";
		//cout << levelData->FirstChildElement("Bricks")->GetText() << endl;
		//cout << "==========================================================================================\n";
		
		levelData = levelData->NextSiblingElement("Level");
	}

}
