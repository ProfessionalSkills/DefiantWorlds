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
CSpaceState::CSpaceState() :mTimeToUpdate(0.1f), mCamRotSpeed(0.7),mCamZAdjust(-10.4f),mBaseCamZ(-188.0f), mDisplacement(30),CGameState()
{
	mTimeSinceUpdate = 0.0f;
	mCamZ = 0.0f;
}

CSpaceState::~CSpaceState()
{

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

	// INITIALISE SKYBOX
	//------------------------------
	mpMshSkybox = gpEngine->LoadMesh("SkyboxSpace.x");
	mpMdlSkybox = mpMshSkybox->CreateModel(0.0f, -1000.0f, 0.0f);

	// INITIALISE MUSIC
	//------------------------------
	string mMusicFile = "Space_Music.wav";
	DX::XMFLOAT3 mSourcePos = { mpCamMain->GetX(), mpCamMain->GetY(), mpCamMain->GetZ() };
	DX::XMFLOAT3 mSourceVel = { 0.0f, 0.0f, 0.0f };
	DX::XMFLOAT3 listenerPos = { mpCamMain->GetX(), mpCamMain->GetY(), mpCamMain->GetZ() };
	DX::XMFLOAT3 listenerVel = { 0.0f, 0.0f, 0.0f };
	mMusic = new CSound(mMusicFile, mSourcePos, mSourceVel, true, 0.8f, listenerPos, listenerVel);
	mMusic->PlaySound();

	// LOAD MODELS
	//------------------------------
	mpPlayerOneFleet->LoadShipModels(-mDisplacement);
	mpPlayerTwoFleet->LoadShipModels(mDisplacement);
	mpMdlSkybox->AttachToParent(mpCamMain);

	// INITIALISE USER INTERFACE
	//-----------------------------
	mFntDebug = gpEngine->LoadFont("Calibri", 20U);
} 

void CSpaceState::StateUpdate()
{
	// Draw the scene
	gpEngine->DrawScene();

	if (gpEngine->KeyHit(Key_R))
	{
		gCurState = GS_WORLD;
	}

	if (gpEngine->KeyHit(Key_M))
	{
		gCurState = GS_MAIN_MENU;
	}

	//update time, used to slow down the speed of the fight
	mTimeSinceUpdate += gFrameTime;

	if (mTimeSinceUpdate >= mTimeToUpdate)
	{
		//fleets attack each other according to tactics
		mpPlayerOneFleet->UnloadShieldModels();
		mpPlayerTwoFleet->UnloadShieldModels();

		//randomizes the order of fleet attack->update
		if (mNewRandom.GetRandomInt(1, 2) == 1)
		{
			mpPlayerOneFleet->Fight();
			mpPlayerTwoFleet->UpdateCondition();

			//finds and removes dead ships
			mpPlayerTwoFleet->Fight();
			mpPlayerOneFleet->UpdateCondition();
		}
		else 
		{
			//finds and removes dead ships
			mpPlayerTwoFleet->Fight();
			mpPlayerOneFleet->UpdateCondition();

			mpPlayerOneFleet->Fight();
			mpPlayerTwoFleet->UpdateCondition();	
		}

		
		//reset timer
		mTimeSinceUpdate = 0.0f;
	}

	if (mpPlayerOneFleet->GetSize() == 0)
	{
		mpPlayerTwoFleet->MoveFleet();
	}
	else if (mpPlayerTwoFleet->GetSize() == 0)
	{
		mpPlayerOneFleet->MoveFleet();
	}
	else 
	{
		mpPlayerOneFleet->IdleFleet();
		mpPlayerTwoFleet->IdleFleet();
	}

	DrawFontData();
}

void CSpaceState::StateLoad()
{

}

void CSpaceState::StateSave()
{

}

void CSpaceState::DrawFontData()
{
	int playerOneTextX = 5;
	int playerTwoTextX = 1580;

	//fleet size output
	strStream << "player one fleet size: " << mpPlayerOneFleet->GetSize();
	mFntDebug->Draw(strStream.str(), playerOneTextX, 715, kWhite, kLeft, kTop);
	strStream.str("");

	strStream << "  player two fleet size: " << mpPlayerTwoFleet->GetSize();
	mFntDebug->Draw(strStream.str(), playerTwoTextX, 715, kWhite, kRight, kTop);
	strStream.str("");

	//fleet total health output
	strStream << "player one fleet total health: " << mpPlayerOneFleet->GetFleetTotalHealth();
	mFntDebug->Draw(strStream.str(), playerOneTextX, 730, kWhite, kLeft, kTop);
	strStream.str("");

	strStream << "  player two fleet total health: " << mpPlayerTwoFleet->GetFleetTotalHealth();
	mFntDebug->Draw(strStream.str(), playerTwoTextX, 730, kWhite, kRight, kTop);
	strStream.str("");

	//fleet total health output
	strStream << "player one fleet avarage health: " << mpPlayerOneFleet->GetFleetAvargeHealth();
	mFntDebug->Draw(strStream.str(), playerOneTextX, 745, kWhite, kLeft, kTop);
	strStream.str("");

	strStream << "  player two fleet avarage health: " << mpPlayerTwoFleet->GetFleetAvargeHealth();
	mFntDebug->Draw(strStream.str(), playerTwoTextX, 745, kWhite, kRight, kTop);
	strStream.str("");

	//fleet total accuracy
	strStream << "player one fleet shots hit: " << mpPlayerOneFleet->GetHits() << "//" << mpPlayerOneFleet->GetShotsFired();
	mFntDebug->Draw(strStream.str(), playerOneTextX, 760, kWhite, kLeft, kTop);
	strStream.str("");

	strStream << "  player two fleet shots hit: " << mpPlayerTwoFleet->GetHits() << "//" << mpPlayerTwoFleet->GetShotsFired();
	mFntDebug->Draw(strStream.str(), playerTwoTextX, 760, kWhite, kRight, kTop);
	strStream.str("");

	//fleet total accuracy percentage output
	strStream << "player one fleet avarage accuracy: " << mpPlayerOneFleet->GetHitPercentage()<<"%";
	mFntDebug->Draw(strStream.str(), playerOneTextX, 775, kWhite, kLeft, kTop);
	strStream.str("");

	strStream << "  player two fleet avarage accuracy: " << mpPlayerTwoFleet->GetHitPercentage() << "%";
	mFntDebug->Draw(strStream.str(), playerTwoTextX, 775, kWhite, kRight, kTop);
	strStream.str("");
}

void CSpaceState::StateCleanup()
{
	//stop sound
	mMusic->StopSound();

	//unload models
	mpMshSkybox->RemoveModel(mpMdlSkybox);

	mpPlayerOneFleet->ReturnFleet(mpHumanPlayer);
	mpPlayerTwoFleet->ReturnFleet(mpAIPlayer);

	//set pointers to null
	mpPlayerOneFleet = nullptr;
	mpPlayerTwoFleet = nullptr;
}
