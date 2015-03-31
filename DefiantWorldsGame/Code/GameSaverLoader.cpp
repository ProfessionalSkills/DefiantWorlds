//-----------------------------------------------------
// FILE: GameSaverLoader.cpp
//-----------------------------------------------------


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "GameSaverLoader.h"


//-----------------------------------------------------
// GAME SAVER & LOADER CLASS CONSTRUCTORS & DESTRUCTOR
//-----------------------------------------------------
CGameSaverLoader::CGameSaverLoader()
{

}

CGameSaverLoader::~CGameSaverLoader()
{

}


//-----------------------------------------------------
// GAME SAVER & LOADER CLASS METHODS
//-----------------------------------------------------
void CGameSaverLoader::LoadGame(std::string& fileName)
{

}

void CGameSaverLoader::SaveGame(std::string& fileName)
{
	// Concatenate file type onto end of file name & open the stream to this file
	stringstream saveFile;
	saveFile << "..\\Saves\\" << fileName << ".dws";
	ofstream saveStream(saveFile.str());

	// SAVE FILE STRUCTURE:
	// Settings
	//     - Music vol, Effects vol, AI Difficulty, Starting Resources
	// <Player>
	//     - Minerals, Faction, num spacefighters, num transport ships, num motherships
	// Grid
	//     - Line by line get state of grid (used or not)  -- ASSESS WHETHER REQUIRED
	// Structures
	//     - Type, Grid Position, Faction, State, World Position, Health, Queue items (Type, Progress), Rotation (currently just for wall data)
	// Ground/Air units
	//     - Type, Faction, State, Position, Health
	// Space Units
	//     - Type, Faction, State, Health, /* cargo (transport ships only) */ <- CHALLENGE
	// Resources
	//     - Grid Position

	// Save settings data through the settings manager
	CStateControl::GetInstance()->GetSettingsManager()->SaveSettings(saveStream);

	// Save player data
	CStateControl::GetInstance()->GetPlayerManager()->SavePlayers(saveStream);
}
