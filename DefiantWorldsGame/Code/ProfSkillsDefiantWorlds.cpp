//-----------------------------------------------------
// FILE: Main.cpp
//-----------------------------------------------------

/*
PROJECT NAME:
ProfSkillsDefiantWorlds

TO DO: * = essential
	*- Remove debug information
	- Model around building being constructed for a more interesting constructing appearance
	*- Save units saved in transport ships
	- Units collide with one another /* SAVE FOR LAST - EFFICIENCY ISSUES
	- If time, decorate surrounding area
	*- Create a saved game to load so that on demo day people are not bored whilst units are constructed etc.
	*- Update population costs of units
	*- Add UI for button mouse over descriptions
	*- Fix bug where population unit is not saved/loaded
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

	//Start up OpenAL
	alutInit(0, 0);


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
	CWorldState::mspMshUnitShadow = gpEngine->LoadMesh("UnitShadow.x");
	CMinerals::mspMshMineral = gpEngine->LoadMesh("Mineral2.x");
	CTransportBeam::mspMshBeam = gpEngine->LoadMesh("Lazer.x");

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
	CRTSPlayer::mspMshPillar = gpEngine->LoadMesh("Pillar.x");

	//Game Agent Meshes
	//Waypoint Arrow
	CGameAgent::mspMshWaypointArrow = gpEngine->LoadMesh("Arrow.x");

	//Spaceship Meshes
	//Space Fighter
	CSpaceFighter::mspMshSpaceFighter = gpEngine->LoadMesh("SciFiBattleship01.x");
	CSpaceFighter::mspMshSheild = gpEngine->LoadMesh("SciFiBattleship01Shield.x");
	CSpaceFighter::alAttackSound = alutCreateBufferFromFile("shoot.wav");
	alGenSources(1, &CSpaceFighter::alAttackSource);
	//Mothership
	CMothership::mspMshMothership = gpEngine->LoadMesh("Spaceship02Battlecruiser.x");
	CMothership::mspMshSheild = gpEngine->LoadMesh("Spaceship02BattlecruiserShield.x");
	CMothership::alAttackSound = alutCreateBufferFromFile("shoot.wav");
	alGenSources(1, &CMothership::alAttackSource);
	//Transport
	CTransport::mspMshTransport = gpEngine->LoadMesh("Spaceship01Battlecruiser.x");
	CTransport::mspMshSheild = gpEngine->LoadMesh("Spaceship01BattlecruiserShield.x");
	CTransport::alAttackSound = alutCreateBufferFromFile("shoot.wav");
	alGenSources(1, &CTransport::alAttackSource);

	//lazer
	CSpaceUnit::mspMshLazer = gpEngine->LoadMesh("Lazer.x");

	//Ground Unit Meshes
	//Bomber
	CBomber::mspMshBomber = gpEngine->LoadMesh("HeliScout.x");
	CBomber::mspMshBomb = gpEngine->LoadMesh("WorldLazer.x");
	CBomber::alAttackSound = alutCreateBufferFromFile("BomberShell.wav");
	alGenSources(1, &CBomber::alAttackSource);
	//Fighter
	CFighter::mspMshFighter = gpEngine->LoadMesh("Helicopter.x");
	CFighter::mspMshFighterBullet = gpEngine->LoadMesh("WorldLazer.x");
	CFighter::alAttackSound = alutCreateBufferFromFile("minigun.wav");
	alGenSources(1, &CFighter::alAttackSource);
	//Worker
	CWorker::mspMshWorker = gpEngine->LoadMesh("transportTruck_german.x");
	CWorker::mspMshWorkerLaser = gpEngine->LoadMesh("Lazer.x");
	CWorker::alAttackSound = alutCreateBufferFromFile("minigun.wav");
	alGenSources(1, &CFighter::alAttackSource);
	//Tank
	CTank::mspMshTank = gpEngine->LoadMesh("HoverTank01.x");
	CTank::mspMshTankShell = gpEngine->LoadMesh("WorldLazer.x");
	CTank::alAttackSound = alutCreateBufferFromFile("tank-firing.wav");
	alGenSources(1, &CTank::alAttackSource);
	//Infantry
	CInfantry::mspMshInfantry = gpEngine->LoadMesh("tigerAusfH.x");
	CInfantry::mspMshInfantryBullet = gpEngine->LoadMesh("WorldLazer.x");
	CInfantry::alAttackSound = alutCreateBufferFromFile("tank-firing.wav");
	alGenSources(1, &CInfantry::alAttackSource);
	//Artillery
	CArtillery::mspMshArtillery = gpEngine->LoadMesh("marsAA.x");
	CArtillery::mspMshArtilleryShell = gpEngine->LoadMesh("WorldLazer.x");
	CArtillery::alAttackSound = alutCreateBufferFromFile("ArtilleryGunfire.wav");
	alGenSources(1, &CArtillery::alAttackSource);
	//Particle Mesh
	CParticle::mspMshExplosionParticle = gpEngine->LoadMesh("ExplosionParticle.x");
	CParticle::mspMshSmokeParticle = gpEngine->LoadMesh("SmokeParticle.x");
	CExplosion::mspMshExplosionBall = gpEngine->LoadMesh("ExplosionBall.x");

	//Base Turret Meshes
	//Anti Air Turret
	CTurretStructure::mspMshTurret = gpEngine->LoadMesh("anti_aircraft.x");
	CTurretStructure::mspMshTurretShell = gpEngine->LoadMesh("WorldLazer.x");

	//Transport Beam
	CTransportBeam::mspMshBeam = gpEngine->LoadMesh("WorldLazer.x");
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
