//-----------------------------------------------------
// FILE: GameStateControl.cpp
//-----------------------------------------------------


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "GameStateControl.h"

CStateControl* CStateControl::mspSingleton = nullptr;


//-----------------------------------------------------
// GAME STATE CONTROL CLASS CONSTRUCTORS & DESTRUCTOR
//-----------------------------------------------------
CStateControl::CStateControl(EGameStates inStartState)
{
	// Initialise states
	//mpPlayState = new CPlayState();
	mpMenuState = new CMenuState();
	mpSpaceState = new CSpaceState();
	mpWorldState = new CWorldState();

	// Initialise player manager
	mpPlayerManager = new CPlayerManager();

	// Initialise settings manager
	mpSettingsManager = new CSettingsManager();

	// Set global state
	gCurState = inStartState;
	mCurState = inStartState;

	// Initialise music
	ALuint musicBuffer = alutCreateBufferFromFile("Intro.wav");
	ALuint musicSource;
	alGenSources(1, &musicSource);
	DX::XMFLOAT3 mSourcePos = { 0.0f, 0.0f, 0.0f };
	DX::XMFLOAT3 mSourceVel = { 0.0f, 0.0f, 0.0f };
	DX::XMFLOAT3 listenerPos = { 0.0f, 0.0f, 0.0f };
	DX::XMFLOAT3 listenerVel = { 0.0f, 0.0f, 0.0f };
	float volume = 0.6f;
	mMusic = new CSound(musicBuffer, mSourcePos, mSourceVel, true, volume, listenerPos, listenerVel, musicSource);


	// Set current state
	switch (inStartState)
	{
		case GS_MAIN_MENU:
			mpCurGameState = mpMenuState;
			mMusic->PlaySound();
			break;
		case GS_SPACE:
			mpCurGameState = mpSpaceState;
			break;
		case GS_WORLD:
			mpCurGameState = mpWorldState;
			break;
	}

	// Setup scene
	mpCurGameState->StateSetup();
}

CStateControl::~CStateControl()
{
	SafeDelete(mpPlayerManager);

	SafeDelete(mpMenuState);
	SafeDelete(mpSpaceState);
	SafeDelete(mpWorldState);
}


//-----------------------------------------------------
// GAME STATE CONTROL CLASS MUTATORS
//-----------------------------------------------------
void CStateControl::SetCurrentState(EGameStates inNewState)
{
	// Before changing pointer, unload current level
	mpCurGameState->StateCleanup();
	
	// Set new current state
	switch (inNewState)
	{
	case GS_MAIN_MENU:
		mpCurGameState = mpMenuState;
		mMusic->PlaySound();
		break;
	case GS_SPACE:
		mpCurGameState = mpSpaceState;
		mMusic->StopSound();
		break;
	case GS_WORLD:
		mpCurGameState = mpWorldState;
		mMusic->StopSound();
		break;
	}

	OnStateChange();
}


//-----------------------------------------------------
// GAME STATE CONTROL CLASS METHODS
//-----------------------------------------------------
void CStateControl::Update()
{
	// Compare current state to global state to check for state changes
	if (gCurState != mCurState)
	{
		// Update class' current stored state
		mCurState = gCurState;

		// Update polymorphic pointer
		SetCurrentState(gCurState);
	}

	// Increment time since game has started
	if (mCurState == GS_WORLD)
	{
		mTimeSinceGameStart += gFrameTime;
		mpPlayerManager->SetGameTime(mTimeSinceGameStart);
	}
}

void CStateControl::OnStateChange()
{
	// Call the setup function of the new state
	mpCurGameState->StateSetup();
}
