//-----------------------------------------------------
// FILE: MenuState.cpp
//-----------------------------------------------------


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "MenuState.h"
#include "GameStateControl.h"


//-----------------------------------------------------
// MENU STATE CLASS CONSTRUCTORS & DESTRUCTOR
//-----------------------------------------------------
CMenuState::CMenuState() : CGameState()
{
	
}

CMenuState::~CMenuState()
{

}


//-----------------------------------------------------
// MENU STATE CLASS METHODS
//-----------------------------------------------------
void CMenuState::NewGame()
{
	gCurState = GS_NEW_GAME;
}

void CMenuState::LoadGame()
{
	// Verify the file name provided
	std::stringstream fileName;
	fileName << "..\\Saves\\" << mpTypeBox->GetText() << ".dws";
	ifstream validate(fileName.str());

	// If the file opens, it is successful otherwise it is not valid
	if (!validate.good())
	{
		// File failed to open
		validate.close();
		std::string error = "File not found! (Delete key to clear)";
		mpTypeBox->SetText(error);
		return;
	}
	validate.close();

	// If the players are already initialised, remove them
	CPlayerManager* pPlayerManager = CStateControl::GetInstance()->GetPlayerManager();
	if (pPlayerManager->ArePlayersInitialised())
	{
		pPlayerManager->RemovePlayers();
	}

	// Pass on the name of the file to be loaded
	CStateControl::GetInstance()->GetSettingsManager()->SetIfLoadingGame(true);
	CStateControl::GetInstance()->GetSettingsManager()->SetLoadFile(fileName.str());

	// Set current state to be world state
	gCurState = GS_WORLD;
}

void CMenuState::ChangeSettings()
{
	gCurState = GS_SETTINGS;
}

void CMenuState::Quit()
{
	gpEngine->Stop();
}

void CMenuState::OnChooseLoadGame()
{
	// Create a typebox
	mpTypeBox = new CTypeBox(SPointData{ 760, 420 });

	// Remove the buttons as they are no longer needed
	while (!mpButtonList.empty())
	{
		CAdvancedButton<CMenuState, void>* pButton = mpButtonList.back();
		SafeDelete(pButton);
		mpButtonList.pop_back();
	}

	// Create the save related buttons
	CAdvancedButton<CMenuState, void>* pNewButton = new CAdvancedButton<CMenuState, void>("DefSmallButton.png", "SelSmallButton.png", SPointData(895, 480),
		SAABoundingBox(730.0f, 995.0f, 480.0f, 895.0f), *this, &CMenuState::LoadGame);
	mpButtonList.push_back(pNewButton);

	pNewButton = new CAdvancedButton<CMenuState, void>("DefSmallButton.png", "SelSmallButton.png", SPointData(1035, 480),
		SAABoundingBox(730.0f, 1135.0f, 480.0f, 1035.0f), *this, &CMenuState::OnChooseCancel);
	mpButtonList.push_back(pNewButton);
}

void CMenuState::OnChooseCancel()
{
	// Remove type box
	SafeDelete(mpTypeBox);

	// Remove the buttons as they are no longer needed
	while (!mpButtonList.empty())
	{
		CAdvancedButton<CMenuState, void>* pButton = mpButtonList.back();
		SafeDelete(pButton);
		mpButtonList.pop_back();
	}

	// Return main menu buttons
	CAdvancedButton<CMenuState, void>* pNewButton = new CAdvancedButton<CMenuState, void>("DefMenuButton.png", "SelMenuButton.png", SPointData(815, 350),
		SAABoundingBox(400.0f, 1215.0f, 350.0f, 815.0f), *this, &CMenuState::NewGame);
	mpButtonList.push_back(pNewButton);

	pNewButton = new CAdvancedButton<CMenuState, void>("DefMenuButton.png", "SelMenuButton.png", SPointData(815, 420),
		SAABoundingBox(470.0f, 1215.0f, 420.0f, 815.0f), *this, &CMenuState::OnChooseLoadGame);
	mpButtonList.push_back(pNewButton);

	pNewButton = new CAdvancedButton<CMenuState, void>("DefMenuButton.png", "SelMenuButton.png", SPointData(815, 490),
		SAABoundingBox(540.0f, 1215.0f, 490.0f, 815.0f), *this, &CMenuState::ChangeSettings);
	mpButtonList.push_back(pNewButton);

	pNewButton = new CAdvancedButton<CMenuState, void>("DefMenuButton.png", "SelMenuButton.png", SPointData(815, 560),
		SAABoundingBox(610.0f, 1215.0f, 560.0f, 815.0f), *this, &CMenuState::Quit);
	mpButtonList.push_back(pNewButton);
}


//-----------------------------------------------------
// MENU STATE CLASS OVERRIDE METHODS
//-----------------------------------------------------
void CMenuState::StateSetup()
{
	// INITIALISE ADDITIONAL VARIABLES
	//------------------------------
	mOrbitCentre = DX::XMFLOAT3(-60.0f, 0.0f, 50.0f);

	mEarthDistance = 35.0f;
	mMarsDistance = 65.0f;

	mMinAngle = ToRadians(33.0f);
	mMaxAngle = ToRadians(145.0f);


	// INITIALISE CAMERAS
	//------------------------------
	mpCamMain = gpEngine->CreateCamera(kManual, 0.0f, 0.0f, 0.0f);


	// INITIALISE SKYBOX
	//------------------------------
	mpMshSkybox = gpEngine->LoadMesh("SkyboxSpace.x");
	mpMdlSkybox = mpMshSkybox->CreateModel(0.0f, -1000.0f, 0.0f);


	// INITIALISE PLANETS
	//------------------------------
	// Earth
	mEarthAngle = gpRandomiser->GetRandomFloat(mMinAngle, mMaxAngle);
	mpMshPlanet = gpEngine->LoadMesh("Planet.x");
	mpMdlEarth = mpMshPlanet->CreateModel(-60.0f, 0.0f, 45.0f);
	mpMdlEarth->Scale(5.0f);

	// Mars
	mMarsAngle = gpRandomiser->GetRandomFloat(mMinAngle, mMaxAngle);
	mpMdlMars = mpMshPlanet->CreateModel(-60.0f, 0.0f, 45.0f);
	mpMdlMars->SetSkin("Mars.jpg");
	mpMdlMars->Scale(2.6f);


	// INITIALISE ATMOSPHERE
	//------------------------------
	mpMshAtmosphere = gpEngine->LoadMesh("Atmos.x");
	mpMdlAtmosphere = mpMshAtmosphere->CreateModel(0.0f, 0.0f, 0.0f);
	mpMdlAtmosphere->AttachToParent(mpMdlEarth);
	mpMdlAtmosphere->Scale(1.02f);


	// CREATE SPRITES, BUTTONS & FONTS
	//------------------------------
	mpButtonFont = gpEngine->LoadFont("font2.bmp", 15U);

	mpSprBackground = gpEngine->CreateSprite("MenuBG.png", 400.0f, 50.0f, 0.9f);
	mpSprLogo = gpEngine->CreateSprite("Logo.png", 800.0f, 100.0f, 0.8f);
	mpSprCursor = gpEngine->CreateSprite("BaseCursor.png", 5.0f, 50.0f, 0.0f);

	CAdvancedButton<CMenuState, void>* pNewButton = new CAdvancedButton<CMenuState, void>("DefMenuButton.png", "SelMenuButton.png", SPointData(815, 350),
		SAABoundingBox(400.0f, 1215.0f, 350.0f, 815.0f), *this, &CMenuState::NewGame);
	mpButtonList.push_back(pNewButton);

	pNewButton = new CAdvancedButton<CMenuState, void>("DefMenuButton.png", "SelMenuButton.png", SPointData(815, 420),
		SAABoundingBox(470.0f, 1215.0f, 420.0f, 815.0f), *this, &CMenuState::OnChooseLoadGame);
	mpButtonList.push_back(pNewButton);

	pNewButton = new CAdvancedButton<CMenuState, void>("DefMenuButton.png", "SelMenuButton.png", SPointData(815, 490),
		SAABoundingBox(540.0f, 1215.0f, 490.0f, 815.0f), *this, &CMenuState::ChangeSettings);
	mpButtonList.push_back(pNewButton);

	pNewButton = new CAdvancedButton<CMenuState, void>("DefMenuButton.png", "SelMenuButton.png", SPointData(815, 560),
		SAABoundingBox(610.0f, 1215.0f, 560.0f, 815.0f), *this, &CMenuState::Quit);
	mpButtonList.push_back(pNewButton);
}

void CMenuState::StateUpdate()
{
	// SCENE DRAW
	//------------------------------
	gpEngine->DrawScene();


	// ANIMATE ATMOSPHERE
	//------------------------------
	mpMdlAtmosphere->RotateLocalX(gpRandomiser->GetRandomFloat(0.0f, 2.6f) * gFrameTime);
	mpMdlAtmosphere->RotateLocalY(gpRandomiser->GetRandomFloat(-1.0f,  2.8f) * gFrameTime);
	mpMdlAtmosphere->RotateLocalZ(gpRandomiser->GetRandomFloat(0.0f,  2.0f) * gFrameTime);


	// CALCULATE PLANET ORBIT POSITIONS
	//------------------------------
	mpMdlEarth->SetX(mOrbitCentre.x + mEarthDistance * sinf(mEarthAngle));
	mpMdlEarth->SetY(mOrbitCentre.y + mEarthDistance* cosf(mEarthAngle));
	mEarthAngle += gFrameTime * 0.01f;
	if (mEarthAngle > mMaxAngle)
	{
		mEarthAngle = mMinAngle;
	}

	mpMdlMars->SetX(mOrbitCentre.x + mMarsDistance * sinf(mMarsAngle));
	mpMdlMars->SetY(mOrbitCentre.y + mMarsDistance * cosf(mMarsAngle));
	mMarsAngle += gFrameTime * 0.025f;
	if (mMarsAngle > mMaxAngle)
	{
		mMarsAngle = mMinAngle;
	}


	// UPDATE BUTTONS
	//------------------------------
	// The state of the type box determines whether the buttons have changed or not
	if (mpTypeBox == nullptr)
	{
		mpButtonFont->Draw("NEW GAME", 1015, 365, kWhite, kCentre, kTop);
		mpButtonFont->Draw("LOAD GAME", 1015, 435, kWhite, kCentre, kTop);
		mpButtonFont->Draw("CHANGE SETTINGS", 1015, 505, kWhite, kCentre, kTop);
		mpButtonFont->Draw("QUIT GAME", 1015, 575, kWhite, kCentre, kTop);
	}
	else
	{
		// Update pause menu visuals
		mpButtonFont->Draw("TYPE THE NAME OF THE FILE YOU WANT TO LOAD BELOW:", 770, 400, kWhite, kLeft, kTop);
		mpButtonFont->Draw("LOAD", 945, 495, kWhite, kCentre, kTop);
		mpButtonFont->Draw("CANCEL", 1085, 495, kWhite, kCentre, kTop);

		// Update the type box
		mpTypeBox->Update();
	}

	mMousePos.x = (float)gpEngine->GetMouseX();
	mMousePos.y = (float)gpEngine->GetMouseY();
	for (miterButtons = mpButtonList.begin(); miterButtons != mpButtonList.end(); miterButtons++)
	{
		CAdvancedButton<CMenuState, void>* pButton = (*miterButtons);
		// Check if the mouse is colliding with the object
		if (pButton->GetBoundingBox().IsColliding(DX::XMFLOAT3(mMousePos.x, 0.0f, mMousePos.y)))
		{
			pButton->SetMouseOver(true);
		}
		else
		{
			pButton->SetMouseOver(false);
		}

		// Check for click 
		if (pButton->GetMouseOver())
		{
			// Check if the mouse is over the button
			if (gpEngine->KeyHit(Mouse_LButton))
			{
				// Raise click flag
				pButton->Execute();
				// Remove self from for loop
				break;
			}
		}

		// Update the button
		pButton->Update();
	}


	// UPDATE CURSOR
	//------------------------------
	mpSprCursor->SetPosition(mMousePos.x, mMousePos.y);
}

void CMenuState::StateCleanup()
{
	mpMshAtmosphere->RemoveModel(mpMdlAtmosphere);
	mpMshPlanet->RemoveModel(mpMdlMars);
	mpMshPlanet->RemoveModel(mpMdlEarth);
	mpMshSkybox->RemoveModel(mpMdlSkybox);

	gpEngine->RemoveCamera(mpCamMain);
	gpEngine->RemoveMesh(mpMshAtmosphere);
	gpEngine->RemoveMesh(mpMshPlanet);
	gpEngine->RemoveMesh(mpMshSkybox);
	gpEngine->RemoveSprite(mpSprBackground);
	gpEngine->RemoveSprite(mpSprLogo);
	gpEngine->RemoveSprite(mpSprCursor);

	// Remove buttons
	while (!mpButtonList.empty())
	{
		CAdvancedButton<CMenuState, void>* tmp = mpButtonList.back();
		SafeDelete(tmp);
		mpButtonList.pop_back();
	}

	SafeDelete(mpTypeBox);
}
