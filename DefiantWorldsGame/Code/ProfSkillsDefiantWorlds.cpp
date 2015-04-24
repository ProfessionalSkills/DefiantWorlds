//-----------------------------------------------------
// FILE: Main.cpp
//-----------------------------------------------------

/*
PROJECT NAME:
ProfSkillsDefiantWorlds

TO DO:
	- Wall destruction
	- Towers on corners of wall
	- Anti-aircraft turret structures on top of corner towers
	- UI for space buttons
	- STOP button for units
	- Fix bug where human units spawning in Mars would attempt to make their way back home as they are 'out of their boundary'
	- Change the save log so that Rebel units get saved
	- Change how units are saved - instead of just their position, save their entire matrix
	- Complete UI for info at top of screen
	- Complete UI for news ticker
	- Reposition news ticker
	- Shadows beneath units
	- Model arrow to show where unit is attempting to travel to
	- Make shadow of unit glow when that unit is selected
	- Use lasers for workers when they are mining minerals
	- Ability to heal/repair
	- Stop helicopters from leaning to one side when they turn - causes too many bugs
	- Red beam from sky when unit is sent to transport ship
	- Model around building being constructed for a more interesting constructing appearance
	- Retune AI to do attacking
	- AI to load units to ships
	- AI to launch fleet
	- AI to attack enemies when they are near
	- Have a timer for when a fleet attempts to travel across space
	- Launch button glows red and a timer appears when the enemy is launching their fleet
	- Walls have a lower/raise ability
	- Ground units cannot move through walls
	- Units collide with one another
	- Units require a slightly bigger hit box
	- If time, decorate surrounding area
	- Create a model save to load so that on demo day people are not bored whilst units are constructed etc.
	- Fix game loading bugs
	- Add houses??
	- Update population costs of units
	- Change the way smoke is produced so it is not concentrated in one position for buildings &
		remove smoke limit - simply create a smoke particle every so often
*/


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "GameStateControl.h"


//-----------------------------------------------------
// MAIN GLOBALS
//-----------------------------------------------------

// Game Manager
//----------------------
CStateControl* gpStateController;


//-----------------------------------------------------
// FUNCTION PROTOTYPE DECLERATIONS
//-----------------------------------------------------

// Engine-specific
//----------------------
void SetupEngine();
void CleanupEngine();

// Scene
//----------------------
void Initialise();
void Cleanup();


//-----------------------------------------------------
// MAIN
//-----------------------------------------------------
void main()
{
	// ENGINE SETUP & INITIALISATION
	//------------------------------
	SetupEngine();
	Initialise();

	
	// FRAMETIME
	//------------------------------
	gpEngine->Timer();


	// WINDOW TITLE
	//------------------------------
	float titleChangeCounter = 1.0f;
	const std::string GAME_NAME = "Defiant Worlds";
	std::stringstream caption;


	// MAIN PROGRAM LOOP
	//------------------------------
	while (gpEngine->IsRunning())
	{
		// UPDATE CURRENT STATE
		//------------------------------
		gFrameTime = gpEngine->Timer();

		// Check if there has been a state change
		gpStateController->Update();

		// Call the update for the current state
		gpStateController->GetCurrentState()->StateUpdate();

		// Update window caption
		if (titleChangeCounter >= 1.0f)
		{
			caption << GAME_NAME << "    FT: " << gFrameTime << "    FPS: " << 1.0f / gFrameTime;
			gpEngine->SetWindowCaption(caption.str().c_str());
			caption.str("");	// Clear the string stream
			titleChangeCounter = 0.0f;
		}
		else
		{
			titleChangeCounter += gFrameTime;
		}
	}

	Cleanup();
}


//-----------------------------------------------------
// FUNCTION DEFINITIONS
//-----------------------------------------------------

// Engine-specific
//----------------------
void SetupEngine()
{
	//setting up windows
	gpEngine->StartWindowed(WINDOW_WIDTH, WINDOW_HEIGHT);
	SetWindowPos((HWND)gpEngine->GetWindow(), HWND_TOP, WINDOW_POS_X, WINDOW_POS_Y, WINDOW_WIDTH, WINDOW_HEIGHT, 0U);
	ShowCursor(false);

	//Get Media Folders
	gpEngine->AddMediaFolder("..\\Media\\Models\\Skybox");
	gpEngine->AddMediaFolder("..\\Media\\Models\\Planets");
	gpEngine->AddMediaFolder("..\\Media\\Models\\Structures");
	gpEngine->AddMediaFolder("..\\Media\\Models\\Grid");
	gpEngine->AddMediaFolder("..\\Media\\Models\\Particles");
	gpEngine->AddMediaFolder("..\\Media\\Models\\Units");
	gpEngine->AddMediaFolder("..\\Media\\Models\\Units\\Vehicles\\SciFi");
	gpEngine->AddMediaFolder("..\\Media\\Models\\Units\\Vehicles\\Military");
	gpEngine->AddMediaFolder("..\\Media\\Models\\Units\\Aircraft\\SciFi");
	gpEngine->AddMediaFolder("..\\Media\\Models\\Units\\Aircraft\\Modern");
	gpEngine->AddMediaFolder("..\\Media\\User Interface");

	
	// Load static meshes
	CTile::mspMshTile = gpEngine->LoadMesh("Tile.x");
	CWorldState::mspMshDrag = gpEngine->LoadMesh("DragSelection.x");
	CMinerals::mspMshMineral = gpEngine->LoadMesh("Mineral2.x");

	//Structure Meshes
	//Command Centre
	CComCentre::mspMshStructureBuilt = gpEngine->LoadMesh("ComCentreBuilt.x");
	CComCentre::mspMshStructurePlacing = gpEngine->LoadMesh("ComCentrePlacing.x");
	//Barracks
	CBarracks::mspMshStructureBuilt = gpEngine->LoadMesh("BarracksBuilt.x");
	CBarracks::mspMshStructurePlacing = gpEngine->LoadMesh("BarracksPlacing.x");
	//Helipad
	CHellipad::mspMshStructureBuilt = gpEngine->LoadMesh("HellipadBuilt.x");
	CHellipad::mspMshStructurePlacing = gpEngine->LoadMesh("HellipadPlacing.x");
	//Space Centre
	CSpaceCentre::mspMshStructureBuilt = gpEngine->LoadMesh("SpaceCentreBuilt.x");
	CSpaceCentre::mspMshStructurePlacing = gpEngine->LoadMesh("SpaceCentrePlacing.x");
	// Wall
	CWall::mspMshStructure = gpEngine->LoadMesh("wall_A1_01.x");

	
	//Spaceship Meshes
	//Space Fighter
	CSpaceFighter::mspMshSpaceFighter = gpEngine->LoadMesh("SciFiBattleship01.x");
	CSpaceFighter::mspMshSheild = gpEngine->LoadMesh("SciFiBattleship01Shield.x");
	//Mothership
	CMothership::mspMshMothership = gpEngine->LoadMesh("Spaceship02Battlecruiser.x");
	CMothership::mspMshSheild = gpEngine->LoadMesh("Spaceship02BattlecruiserShield.x");
	//Transport
	CTransport::mspMshTransport = gpEngine->LoadMesh("Spaceship01Battlecruiser.x");
	CTransport::mspMshSheild = gpEngine->LoadMesh("Spaceship01BattlecruiserShield.x");

	//lazer
	CSpaceUnit::mspMshLazer = gpEngine->LoadMesh("Lazer.x");

	//Ground Unit Meshes
	//Bomber
	CBomber::mspMshBomber = gpEngine->LoadMesh("HeliScout.x");
	CBomber::mspMshBomb = gpEngine->LoadMesh("WorldLazer.x");
	//Fighter
	CFighter::mspMshFighter = gpEngine->LoadMesh("Helicopter.x");
	CFighter::mspMshFighterBullet = gpEngine->LoadMesh("WorldLazer.x");
	//Worker
	CWorker::mspMshWorker = gpEngine->LoadMesh("transportTruck_german.x");
	CWorker::mspMshWorkerBullet = gpEngine->LoadMesh("bullet.x");
	//Tank
	CTank::mspMshTank = gpEngine->LoadMesh("HoverTank01.x");
	CTank::mspMshTankShell = gpEngine->LoadMesh("WorldLazer.x");
	//Infantry
	CInfantry::mspMshInfantry = gpEngine->LoadMesh("tigerAusfH.x");
	CInfantry::mspMshInfantryBullet = gpEngine->LoadMesh("WorldLazer.x");
	//Artillery
	CArtillery::mspMshArtillery = gpEngine->LoadMesh("marsAA.x");
	CArtillery::mspMshArtilleryShell = gpEngine->LoadMesh("WorldLazer.x");
	//Particle Mesh
	CParticle::mspMshExplosionParticle = gpEngine->LoadMesh("ExplosionParticle.x");
	CParticle::mspMshSmokeParticle = gpEngine->LoadMesh("SmokeParticle.x");
	CExplosion::mspMshExplosionBall = gpEngine->LoadMesh("ExplosionBall.x");
}

void CleanupEngine()
{
	// Cleanup engine
	gpEngine->Delete();
}


// Scene
//----------------------
void Initialise()
{
	// Initialise states
	gpStateController = CStateControl::GetInstance();
}

void Cleanup()
{
	// Cleanup variables
	ShowCursor(true);

	// Cleanup engine
	CleanupEngine();
}
