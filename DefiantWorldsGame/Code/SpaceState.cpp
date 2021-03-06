//-----------------------------------------------------
// FILE: SpaceState.cpp
//-----------------------------------------------------


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "SpaceState.h"
#include "GameStateControl.h"


//-----------------------------------------------------
// SPACE STATE CLASS CONSTRUCTORS & DESTRUCTOR
//-----------------------------------------------------
CSpaceState::CSpaceState() :mTimeToUpdate(1.0f), mTimeToUpdateEffects(0.1f), mCamRotSpeed(0.7), mCamZAdjust(-10.4f), mBaseCamZ(-188.0f), mCameraMoveSpeed(4.0f),
mDisplacement(30), mNumCamStates(4), CGameState()
{
	mpMdlSkybox = 0;
	mpMdlEarth = 0;
	mpMdlJupiter = 0;
	mpMdlMars = 0;
	mpMdlMoon = 0;
	mpMdlSun = 0;
	mpMdlVenus = 0;
	mpMdlMercury = 0;
	mpMdlNeptune = 0;
	mpMdlEarthAtmos = 0;
	mCutScene = false;
	PlayerOneVictory = false;
	PlayerTwoVictory = false;
	mTacticChoosen = false;
	mPaused = false;
	mTimeSinceUpdate = 0.0f;

	mpPlayerOneFleet = 0;
	mpPlayerTwoFleet = 0;

	//Set Camera Values
	mCamZ = 0.0f;
	mCamState = 0;
	mCamZMovement = 0.0f;

	//Set Planet Positions
	mEarthPos = { -1000,-50 , 50, 100 };
	mMoonPos = { 100, 100, 100, 10 };
	mMarsPos = { 500, -400, 100, 50 };
	mSunPos = { 100, 50, -1000, 400 };
	mJupiterPos={ -900, -900, 800, 80 };
	mMercuryPos = { -200, -900, -600, 10 };
	mVenusPos ={ -200, 0, 700, 15 };
	mNeptunePos ={ 600, 100, 650, 25 };
}

CSpaceState::~CSpaceState()
{
	StateCleanup();
}


//-----------------------------------------------------
// MENU STATE CLASS OVERRIDE METHODS
//-----------------------------------------------------
void CSpaceState::StateSetup()
{
	// PLAYERS
	//-----------------------------
	mpPlayerManager = CStateControl::GetInstance()->GetPlayerManager();
	mpHumanPlayer = mpPlayerManager->GetHumanPlayer();
	mpAIPlayer = mpPlayerManager->GetAIPlayer(0);
	
	// FLEET SETUP
	//------------------------------
	mpPlayerOneFleet = mpHumanPlayer->GetFleet();
	mpPlayerTwoFleet = mpAIPlayer->GetFleet();

	mpPlayerOneFleet->SetEnemy(mpPlayerTwoFleet);
	mpPlayerTwoFleet->SetEnemy(mpPlayerOneFleet);

	// INITIALISE CAMERAS
	//------------------------------
	//figures out which fleet has the most ships, then adjusts the camera to fit in all of the ships in that fleet
	if (mpPlayerOneFleet->GetRows() > mpPlayerTwoFleet->GetRows())
	{
		mCamZ = mBaseCamZ + (mpPlayerOneFleet->GetRows()*mCamZAdjust);
	}
	else
	{
		mCamZ = mBaseCamZ + (mpPlayerTwoFleet->GetRows()*mCamZAdjust);
	}

	mpCamMain = gpEngine->CreateCamera(kManual, 0.0f, 0.0f, mCamZ);
	gpCam = mpCamMain;
	ChangeCameraPosition();

	// INITIALISE SKYBOX
	//------------------------------
	mpMshSkybox = gpEngine->LoadMesh("SkyboxSpace.x");
	mpMdlSkybox = mpMshSkybox->CreateModel(0.0f, -1000.0f, 0.0f);

	// INITIALISE MUSIC
	//------------------------------
	ALuint alMusicBuffer = alutCreateBufferFromFile("Space_Music.wav");
	ALuint alMusicSource;
	alGenSources(1, &alMusicSource);
	DX::XMFLOAT3 mSourcePos = { mpCamMain->GetX(), mpCamMain->GetY(), mpCamMain->GetZ() };
	DX::XMFLOAT3 mSourceVel = { 0.0f, 0.0f, 0.0f };
	DX::XMFLOAT3 listenerPos = { mpCamMain->GetX(), mpCamMain->GetY(), mpCamMain->GetZ() };
	DX::XMFLOAT3 listenerVel = { 0.0f, 0.0f, 0.0f };
	float volume = CStateControl::GetInstance()->GetSettingsManager()->GetMusicVolume();
	mMusic = new CSound(alMusicBuffer, mSourcePos, mSourceVel, true, volume, listenerPos, listenerVel, alMusicSource);
	mMusic->PlaySound();

	// LOAD MODELS
	//------------------------------
	mpPlayerOneFleet->LoadShipModels(-mDisplacement);
	mpPlayerTwoFleet->LoadShipModels(mDisplacement);
	LoadPlanets();

	// CREATE SPRITES, BUTTONS & FONTS
	//------------------------------
	mpSprCursor = gpEngine->CreateSprite("BaseCursor.png", 5.0f, 50.0f, 0.0f);
	mpSprHealth1 = gpEngine->CreateSprite("HealthBar100.png", 50.0f, 765.0f, 0.0f);
	mpSprHealth2 = gpEngine->CreateSprite("HealthBar100.png", 1050.0f, 765.0f, 0.0f);

	

	// Tactics Buttons
	CAdvancedButton<CSpaceState, void>* pNewButton = new CAdvancedButton<CSpaceState, void>("NoTactics.png", "NoTacticsMO.png", SPointData(900, 750),
		DX::XMFLOAT2(80.0f, 80.0f), *this, &CSpaceState::ChangeTacNone, TR_UP, true, 0.8f);
	mpButtonListTactics.push_back(pNewButton);
	mpButtonListAll.push_back(pNewButton);
	pNewButton->SetHoverOverText("Don't use any special tactics. cost:0");

	pNewButton = new CAdvancedButton<CSpaceState, void>("DefRapidFireButton.png", "SelRapidFireButton.png", SPointData(750, 750),
		DX::XMFLOAT2(80.0f, 80.0f), *this, &CSpaceState::ChangeTacRapid, TR_UP, true, 0.8f);
	mpButtonListTactics.push_back(pNewButton);
	mpButtonListAll.push_back(pNewButton);
	pNewButton->SetHoverOverText("your fleet will fire twice as fast, but at the cost of some accuracy. cost:1000");

	pNewButton = new CAdvancedButton<CSpaceState, void>("TargetButton.png", "TargetButtonMO.png", SPointData(600, 750),
		DX::XMFLOAT2(80.0f, 80.0f), *this, &CSpaceState::ChangeTacTargated, TR_UP, true, 0.8f);
	mpButtonListTactics.push_back(pNewButton);
	mpButtonListAll.push_back(pNewButton);
	pNewButton->SetHoverOverText("the fleet will target a smaller range of ships, killing them faster. however, his comes at the cost of some power cost:1000");

	// Pause Buttons
	pNewButton = new CAdvancedButton<CSpaceState, void>("DefMenuButton.png", "SelMenuButton.png", SPointData(600, 420),
		DX::XMFLOAT2(400.0f, 50.0f), *this, &CSpaceState::Resume, TR_RIGHT, false,0.001f);
	mpButtonListPause.push_back(pNewButton);
	mpButtonListAll.push_back(pNewButton);

	pNewButton = new CAdvancedButton<CSpaceState, void>("DefMenuButton.png", "SelMenuButton.png", SPointData(600, 470),
		DX::XMFLOAT2(400.0f, 50.0f), *this, &CSpaceState::GoToMainMenu, TR_RIGHT, false, 0.0001f);
	mpButtonListPause.push_back(pNewButton);
	mpButtonListAll.push_back(pNewButton);

	pNewButton = new CAdvancedButton<CSpaceState, void>("DefMenuButton.png", "SelMenuButton.png", SPointData(600, 520),
		DX::XMFLOAT2(400.0f, 50.0f), *this, &CSpaceState::ReturnToEarth, TR_RIGHT, false, 0.0001f);
	mpButtonListPause.push_back(pNewButton);
	mpButtonListAll.push_back(pNewButton);
	mpButtonListDefeat.push_back(pNewButton);
	mpButtonListVictory.push_back(pNewButton);

	//special attack buttons
	pNewButton = new CAdvancedButton<CSpaceState, void>("LaserBarrage.png", "LaserBarrageMO.png", SPointData(650, 750),
		DX::XMFLOAT2(80.0f, 80.0f), *this, &CSpaceState::SALazerBarrage, TR_UP, false, 0.8f);
	mpButtonListAttacks.push_back(pNewButton);
	mpButtonListAll.push_back(pNewButton);
	pNewButton->SetHoverOverText("The Mothership will fire a barrage of lasers at the enemy fleet. Cost: 500 Minerals");

	pNewButton = new CAdvancedButton<CSpaceState, void>("UnitsHeal.png", "UnitsHealMO.png", SPointData(850, 750),
		DX::XMFLOAT2(80.0f, 80.0f), *this, &CSpaceState::SAMassHeal, TR_UP, false, 0.8f);
	mpButtonListAttacks.push_back(pNewButton);
	mpButtonListAll.push_back(pNewButton);
	pNewButton->SetHoverOverText("The Mothership will Heal your fleet. Cost: 500 Minerals");

	// INITIALISE USER INTERFACE
	//-----------------------------
	mFntDebug = gpEngine->LoadFont("Calibri", 20U);
	mpButtonFont = gpEngine->LoadFont("font2.bmp", 15U);
	mpTitleFont = gpEngine->LoadFont("font2.bmp", 35U);

	//temp change camera
	mCamState = 3;
	ChangeCameraPosition();
} 

void CSpaceState::StateUpdate()
{
	gpEngine->DrawScene();

	// Controls
	//-----------------------------
	if (gpEngine->KeyHit(Key_R))
	{
		gCurState = GS_WORLD;
	}

	if (gpEngine->KeyHit(Key_M))
	{
		gCurState = GS_MAIN_MENU;
	}

	if (gpEngine->KeyHit(Key_Escape))
	{
		if (!mPaused)
		{
			mPaused = true;
			ShowButtonsPaused();
		}
		else
		{
			mPaused = false;
			HideButtonsPaused();
		}
	}

	if (gpEngine->KeyHit(Key_C))
	{
		mCamState = (mCamState + 1) % mNumCamStates;
	}

	leftClicked = false;
	if (gpEngine->KeyHit(Mouse_LButton))
	{
		leftClicked = true;
	}

	mMousePos.x = (float)gpEngine->GetMouseX();
	mMousePos.y = (float)gpEngine->GetMouseY();
	UpdateButtons();

	if (!mCutScene)
	{
		mCutScene = mpPlayerOneFleet->SceneSpaceFight();
		mpPlayerTwoFleet->SceneSpaceFight();
		return;
	}

	if (mpPlayerOneFleet->GetCooldownTimer() > 0)
	{
		float time = mpPlayerOneFleet->GetCooldownTimer();
		if (time > 4.5f)
		{
			ChanageSprite("ButtonProg1.png");
		}
		else if (time > 4.0f)
		{
			ChanageSprite("ButtonProg2.png");
		}
		else if (time > 3.5f)
		{
			ChanageSprite("ButtonProg3.png");
		}
		else if (time > 3.0f)
		{
			ChanageSprite("ButtonProg4.png");
		}
		else if (time > 2.5f)
		{
			ChanageSprite("ButtonProg5.png");
		}
		else if (time > 2.0f)
		{
			ChanageSprite("ButtonProg6.png");
		}
		else if (time > 1.5f)
		{
			ChanageSprite("ButtonProg7.png");
		}
		else if (time > 1.0f)
		{
			ChanageSprite("ButtonProg8.png");
		}
		else if (time > 0.5f)
		{
			ChanageSprite("ButtonProg9.png");
		}
		else
		{
			if (mpCoolDownTimer1)
			{
				delete mpCoolDownTimer1;
				mpCoolDownTimer1 = nullptr;
			}
			if (mpCoolDownTimer2)
			{
				delete mpCoolDownTimer2;
				mpCoolDownTimer2 = nullptr;
			}
		}
	
	}

	if (!mPaused&&!PlayerOneVictory&&!PlayerTwoVictory)
	{
		if (mTacticChoosen)
		{
			//update time, used to slow down the speed of the fight
			//Space Controls -Combat Controls
			if (gpEngine->KeyHit(Key_B))
			{
				SALazerBarrage();
			}

			mTimeSinceUpdate += gFrameTime;
			mpPlayerOneFleet->ChargeFleetLazers();
			mpPlayerTwoFleet->ChargeFleetLazers();

			if (mTimeSinceUpdate >= mTimeToUpdate)
			{
				//randomizes the order of fleet attack->update
				if (mNewRandom.GetRandomInt(1, 2) == 1)
				{
					mpPlayerOneFleet->Fight();
					mpPlayerTwoFleet->Fight();
				}
				else
				{
					//finds and removes dead ships
					mpPlayerTwoFleet->Fight();
					mpPlayerOneFleet->Fight();
				}

				//reset timer
				mTimeSinceUpdate = 0.0f;
				mTimeSinceEffectsUpdate = mTimeToUpdateEffects;
			}

			//update effects time
			mTimeSinceEffectsUpdate -= gFrameTime;

			if (mTimeSinceEffectsUpdate <= 0.0f)
			{
				//unload the shield models
				mpPlayerOneFleet->UnloadShieldModels();
				mpPlayerTwoFleet->UnloadShieldModels();

				//unload the lazer models
				mpPlayerOneFleet->UnloadLazers();
				mpPlayerTwoFleet->UnloadLazers();

				//update fleet status
				mpPlayerOneFleet->UpdateCondition();
				mpPlayerTwoFleet->UpdateCondition();

				//update health bars
				UpdateHealthbars();

				//reset timer
				mTimeSinceEffectsUpdate = 0.0f;
			}

			//moves fleets
			mpPlayerTwoFleet->MoveFleet();
			mpPlayerOneFleet->MoveFleet();

			mpPlayerOneFleet->IdleFleet();
			mpPlayerTwoFleet->IdleFleet();

			mCamZMovement += mCameraMoveSpeed*gFrameTime;
		}
	}
	else if (PlayerOneVictory||PlayerTwoVictory)
	{
		ShowButtonsVictory();
	}

	ChangeCameraPosition();

	// UPDATE CURSOR
	//------------------------------
	mMousePos.x = (float)gpEngine->GetMouseX();
	mMousePos.y = (float)gpEngine->GetMouseY();

	mpSprCursor->SetPosition(mMousePos.x, mMousePos.y);
	gpNewsTicker->Display();
	DrawFontData();

	// UPDATE VICTORY STATE
	//------------------------------
	CheckForVictory();

	// UPDATE PARTICLE SYSTEMS
	//------------------------------
	mpPlayerOneFleet->UpdateExplosions();
	mpPlayerTwoFleet->UpdateExplosions();
}

void CSpaceState::DrawFontData()
{
	int playerOneTextX = 150;
	int playerTwoTextX = 1430;

	//fleet total accuracy percentage output
	strStream << "player one fleet Health: " << mpPlayerOneFleet->GetFleetTotalHealth();
	mFntDebug->Draw(strStream.str(), playerOneTextX, 765, kCyan, kLeft, kTop);
	strStream.str("");

	strStream << "  player two fleet health: " << mpPlayerTwoFleet->GetFleetTotalHealth();
	mFntDebug->Draw(strStream.str(), playerTwoTextX, 765, kCyan, kRight, kTop);
	strStream.str("");

	if (mPaused)
	{
		mpTitleFont->Draw("Game Paused", 800, 90, kCyan, kCentre, kTop);
		mpButtonFont->Draw("Reume Game", 800, 435, kCyan, kCentre, kTop);
		mpButtonFont->Draw("Main Menu", 800, 485, kCyan, kCentre, kTop);
		mpButtonFont->Draw("Return To Earth", 800, 535, kCyan, kCentre, kTop);
	}
	if (PlayerOneVictory)
	{
		mpTitleFont->Draw("Victory", 800, 90, kCyan, kCentre, kTop);
		mpButtonFont->Draw("Land On Mars", 800, 535, kCyan, kCentre, kTop);
	}
	if (!mTacticChoosen&&mCutScene)
	{
		mpTitleFont->Draw("Choose A Tactic", 800, 120, kCyan, kCentre, kTop);
	}
}

void CSpaceState::StateCleanup()
{
	//unload explosions
	mpPlayerOneFleet->CleanUpExplosions();
	mpPlayerTwoFleet->CleanUpExplosions();

	// Unload fonts
	gpEngine->RemoveFont(mpTitleFont);
	gpEngine->RemoveFont(mpButtonFont);
	gpEngine->RemoveFont(mFntDebug);

	//reset scene
	mCutScene = false;
	// DISPLAY LOADING SCREEN
	ISprite* pLoading = gpEngine->CreateSprite("Loading.png");

	gpEngine->DrawScene();

	// Remove loading screen sprite
	gpEngine->RemoveSprite(pLoading);
	
	//remove sprites
	if (mpSprCursor!=0)
	{
		gpEngine->RemoveSprite(mpSprCursor);
		mpSprCursor = 0;
	}
	if (mpSprHealth1 != 0)
	{
		gpEngine->RemoveSprite(mpSprHealth1);
		mpSprHealth1 = 0;
	}
	if (mpSprHealth2 != 0)
	{
		gpEngine->RemoveSprite(mpSprHealth2);
		mpSprHealth2 = 0;
	}

	//remove buttons
	RemoveButtons();
	mTacticChoosen = false;
	mPaused = false;
	//stop sound
	mMusic->StopSound();

	//unload models
	if (mpMdlSkybox) mpMshSkybox->RemoveModel(mpMdlSkybox);

	if (mpMdlEarth) mpMshPlanet->RemoveModel(mpMdlEarth);
	if (mpMdlJupiter) mpMshPlanet->RemoveModel(mpMdlJupiter);
	if (mpMdlMars) mpMshPlanet->RemoveModel(mpMdlMars);
	if (mpMdlMoon) mpMshPlanet->RemoveModel(mpMdlMoon);
	if (mpMdlSun) mpMshPlanet->RemoveModel(mpMdlSun);
	if (mpMdlVenus) mpMshPlanet->RemoveModel(mpMdlVenus);
	if (mpMdlMercury) mpMshPlanet->RemoveModel(mpMdlMercury);
	if (mpMdlNeptune) mpMshPlanet->RemoveModel(mpMdlNeptune);

	if (mpMdlEarthAtmos) mpMshAtmosphere->RemoveModel(mpMdlEarthAtmos);

	//decide which player won, or if neither won
	CheckForVictory();

	mpHumanPlayer->SetWonLastSpaceBattle(PlayerOneVictory);
	mpAIPlayer->SetWonLastSpaceBattle(PlayerTwoVictory);

	//return fleets
	if (mpPlayerOneFleet) mpPlayerOneFleet->ReturnFleet(mpHumanPlayer,PlayerOneVictory);
	if (mpPlayerTwoFleet) mpPlayerTwoFleet->ReturnFleet(mpAIPlayer,PlayerTwoVictory);

	//reset camera
	mCamZMovement = 0.0f;

	//set pointers to null
	mpPlayerOneFleet = nullptr;
	mpPlayerTwoFleet = nullptr;

	//reset victory
	PlayerOneVictory = false;
	PlayerTwoVictory = false;
}

// Camera Control
//-----------------------------
void CSpaceState::ChangeCameraPosition()
{
	switch (mCamState)
	{
	case 0:
		mpCamMain->ResetOrientation();
		mpCamMain->SetPosition(0.0f, 10.0f, mCamZ + mCamZMovement);
		mpCamMain->LookAt(0.0f, 0.0f, mCamZMovement);
		break;
	case 1:
		mpCamMain->ResetOrientation();
		mpCamMain->SetPosition(mCamZ, -mCamZ / 2.0f, mCamZMovement);
		mpCamMain->LookAt(0.0f, 0.0f, mCamZMovement);
		break;
	case 2:
		mpCamMain->ResetOrientation();
		mpCamMain->SetPosition(-mCamZ , -mCamZ / 2.0f, mCamZMovement);
		mpCamMain->LookAt(0.0f, 0.0f, mCamZMovement);
		break;
	case 3:
		mpCamMain->ResetOrientation();
		mpCamMain->SetPosition(0.0f, 160.0f, -mCamZ + mCamZMovement);
		mpCamMain->LookAt(0.0f, 0.0f, mCamZMovement);
		break;
	default:
		break;
	}
}

void CSpaceState::LoadPlanets()
{
	// INITIALISE PLANETS
	//------------------------------
	// Earth
	mpMshPlanet = gpEngine->LoadMesh("Planet.x");
	mpMdlEarth = mpMshPlanet->CreateModel(mEarthPos.x, mEarthPos.y, mEarthPos.z);
	mpMdlEarth->Scale(mEarthPos.w);

	// Earth Atmosphere
	mpMshAtmosphere = gpEngine->LoadMesh("Atmos.x");
	mpMdlEarthAtmos = mpMshAtmosphere->CreateModel();
	mpMdlEarthAtmos->AttachToParent(mpMdlEarth);
	mpMdlEarthAtmos->Scale(1.02f);

	// Moon
	mpMdlMoon = mpMshPlanet->CreateModel(mEarthPos.x + mMoonPos.x, mEarthPos.y + mMoonPos.y, mEarthPos.z +mMoonPos.z);
	mpMdlMoon->SetSkin("texture_moon.jpg");
	mpMdlMoon->Scale(mMoonPos.w);

	// Mars
	mpMdlMars = mpMshPlanet->CreateModel(mMarsPos.x, mMarsPos.y, mMarsPos.z);
	mpMdlMars->SetSkin("Mars.jpg");
	mpMdlMars->Scale(mMarsPos.w);

	// Sun
	mpMdlSun = mpMshPlanet->CreateModel(mSunPos.x, mSunPos.y, mSunPos.z);
	mpMdlSun->SetSkin("texture_sun.jpg");
	mpMdlSun->Scale(mSunPos.w);

	// Jupiter
	mpMdlJupiter = mpMshPlanet->CreateModel(mJupiterPos.x, mJupiterPos.y, mJupiterPos.z);
	mpMdlJupiter->SetSkin("texture_jupiter.jpg");
	mpMdlJupiter->Scale(mJupiterPos.w);

	// Mercury
	mpMdlJupiter = mpMshPlanet->CreateModel(mMercuryPos.x, mMercuryPos.y, mMercuryPos.z);
	mpMdlJupiter->SetSkin("texture_mercury.jpg");
	mpMdlJupiter->Scale(mMercuryPos.w);

	// Venus
	mpMdlJupiter = mpMshPlanet->CreateModel(mVenusPos.x, mVenusPos.y, mVenusPos.z);
	mpMdlJupiter->SetSkin("texture_venus_surface.jpg");
	mpMdlJupiter->Scale(mVenusPos.w);

	// Neptune
	mpMdlNeptune = mpMshPlanet->CreateModel(mNeptunePos.x, mNeptunePos.y, mNeptunePos.z);
	mpMdlNeptune->SetSkin("texture_neptune.jpg");
	mpMdlNeptune->Scale(mNeptunePos.w);
}

int CSpaceState::FleetHealthPercentagePlayerOne()
{
	int health = (mpPlayerOneFleet->GetFleetTotalHealth() / mpPlayerOneFleet->GetFleetMaxHealth()) * 10;
	return health;
}

int CSpaceState::FleetHealthPercentagePlayerTwo()
{
	int health = (mpPlayerTwoFleet->GetFleetTotalHealth() / mpPlayerTwoFleet->GetFleetMaxHealth()) * 10;
	return health;
}

// Button Functions
//-----------------------------

//Tactics Buttons
void CSpaceState::ChangeTacTargated()
{
	mpHumanPlayer->GetFleet()->SetTactic(Targeted);
	gpNewsTicker->AddNewElement("Targeted space tactic selected.", false);
	mTacticChoosen = true;
	HideButtonsTactics();
	ShowButtonsAttack();
}

void CSpaceState::ChangeTacNone()
{
	mpHumanPlayer->GetFleet()->SetTactic(None);
	gpNewsTicker->AddNewElement("No space tactic selected.", false);
	mTacticChoosen = true;
	HideButtonsTactics();
	ShowButtonsAttack();
}

void CSpaceState::ChangeTacRapid()
{
	mpHumanPlayer->GetFleet()->SetTactic(Rapid);
	gpNewsTicker->AddNewElement("Rapid space tactic selected.", false);
	mTacticChoosen = true;
	HideButtonsTactics();
	ShowButtonsAttack();
}

//cleanup buttons
void CSpaceState::RemoveButtons()
{
	while (!mpButtonListAll.empty())
	{
		CAdvancedButton<CSpaceState, void>* tmp = mpButtonListAll.back();
		SafeDelete(tmp);
		mpButtonListAll.pop_back();
	}

	mpButtonListPause.clear();
	mpButtonListTactics.clear();
	mpButtonListDefeat.clear();
	mpButtonListVictory.clear();
	mpButtonListAttacks.clear();
}

//Menu Button Functions
void CSpaceState::GoToMainMenu()
{
	gCurState = GS_MAIN_MENU;
}

void CSpaceState::ReturnToEarth()
{
	gCurState = GS_WORLD;
}

void CSpaceState::Resume()
{
	mPaused = false;
	HideButtonsPaused();
}

//Special Attack Buttons
void CSpaceState::SALazerBarrage()
{
	mpPlayerOneFleet->SpecialAttackLazerBarrage(mpHumanPlayer);
}

void CSpaceState::SAMassHeal()
{
	mpPlayerOneFleet->SpecialAttackMassHeal(mpHumanPlayer);
}
