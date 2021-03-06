//-----------------------------------------------------
// FILE: GameAgent.cpp
//-----------------------------------------------------


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "GameAgent.h"
#include "GameStateControl.h"
#include "PlayerManager.h"
#include "StaticStructure.h"

IMesh* CGameAgent::mspMshWaypointArrow = nullptr;
//-----------------------------------------------------
// GAME AGENT CLASS CONSTRUCTORS & DESTRUCTOR
//-----------------------------------------------------
CGameAgent::CGameAgent()
{
	mPopCost = 0;
	mTargettingTimer = gpRandomiser->GetRandomFloat(5.0f, 10.0f);
	mAutoTargetting = 0.0f;
	mAutoTargetTime = 3.0f;
}

CGameAgent::~CGameAgent()
{
	// Delete any particle effects attached to this model
	while (mpProjectiles.size() > 0)
	{
		SProjectile* pProjectile = mpProjectiles.back();
		SafeDelete(pProjectile);
		mpProjectiles.pop_back();
	}

	while (mpAttackExplosions.size() > 0)
	{
		CExplosion* pExplosion = mpAttackExplosions.back();
		SafeDelete(pExplosion);
		mpAttackExplosions.pop_back();
	}

	// Give the player the population resources back
	if (mpOwner)
	{
		mpOwner->IncreasePopValue(-mPopCost);
	}
}

//-----------------------------------------------------
// GAME AGENT CLASS ACCESSORS
//-----------------------------------------------------
eFleetPos CGameAgent::GetPosType()
{
	return mFleetPosition;
}

float CGameAgent::GetUnitSpacing()
{
	return mUnitSpacing;
}

//-----------------------------------------------------
// GAME AGENT CLASS MUTATORS
//-----------------------------------------------------
bool CGameAgent::Heal(float amount)
{
	mHealth += amount;
	return false;
}

bool CGameAgent::RayCollision(DX::XMFLOAT3 origin, DX::XMFLOAT3 direction, float& distance)
{
	return mBoundingSphere.GetCollisionDistance(DX::XMLoadFloat3(&origin),
		DX::XMLoadFloat3(&direction), distance);
}

bool CGameAgent::SphereCollision(SBoundingSphere& sphere)
{
	return sphere.CollidingWith(mBoundingSphere.mSphere);
}

bool CGameAgent::DragBoxCollision(DX::BoundingBox& box)
{
	return mBoundingSphere.CollidingWith(box);
}

void CGameAgent::DisplayInfo(IFont* font)
{
	// Output selected agent
	mStrDisplay << mAgentInfo.mAgentName;
	font->Draw(mStrDisplay.str(), 610, 825, 0xff002930, kLeft, kTop);
	mStrDisplay.str("");

	// Display health
	mStrDisplay << (int)mHealth << " \\ " << (int)mMaxHealth;
	font->Draw(mStrDisplay.str(), 990, 825, 0xff002930, kRight, kTop);
	mStrDisplay.str("");
}

void CGameAgent::SetAttackSound(ALuint attackBuffer, ALuint attackSource)
{
	if (mAttackSound)
	{
		SafeDelete(mAttackSound);
	}
	
	DX::XMFLOAT3 mSourcePos = { mWorldPos.x, mWorldPos.y, mWorldPos.z };
	DX::XMFLOAT3 mSourceVel = { 0.0f, 0.0f, 0.0f };
	DX::XMFLOAT3 listenerPos = { 0.0f,0.0f,0.0f};
	ICamera* pCamera;
	//checks to make sure gpworldcam is pointing to somthing
	if (gpCurWorldCamera)
	{
		pCamera = gpCurWorldCamera->GetCamera();
		listenerPos = { pCamera->GetX(), pCamera->GetY(), pCamera->GetZ() };
	}
	else if (gpCam)
	{
		listenerPos = mSourcePos;
	}
	DX::XMFLOAT3 listenerVel = { 0.0f, 0.0f, 0.0f };

	float volume = CStateControl::GetInstance()->GetSettingsManager()->GetEffectsVolume();	// MAKE SURE TO INCLUDE GameStateControl in the

	// .cpp file ONLY otherwise you'll get cyclic redundancy
	mAttackSound = new CSound(attackBuffer, mSourcePos, mSourceVel, false, volume, listenerPos, listenerVel, attackSource);
	mAttackSound->PlaySound(); //construction sound
}

//-----------------------------------------------------
// GAME AGENT CLASS METHODS
//-----------------------------------------------------
void CGameAgent::CalculateBoundingSphere()
{
	DX::XMFLOAT3 centre = { mpObjModel->GetX(), mpObjModel->GetY(), mpObjModel->GetZ() };
	float radius = 7.2f;

	mBoundingSphere = SBoundingSphere(centre, radius);
}

void CGameAgent::SetState(EObjectStates newState)
{
	mState = newState;
}

bool CGameAgent::Construct()
{
	// Reduce construction time left
	mCurProductionTimeLeft -= gFrameTime;

	if (mCurProductionTimeLeft >= 0)
	{
		return false;
	}
	
	return true;
}
void CGameAgent::Destroy()
{
	// Alert news ticker if structure belongs to the player
	if (mFaction == FAC_EARTH_DEFENSE_FORCE)
	{
		switch (GetAgentData()->mAgentType)
		{
		case GAV_ARTILLERY:
			mStrDisplay << "An Artillery";
			break;

		case GAV_BOMBER:
			mStrDisplay << "A Bomber";
			break;

		case GAV_FIGHTER:
			mStrDisplay << "A Fighter";
			break;

		case GAV_INFANTRY:
			mStrDisplay << "Infantry";
			break;

		case GAV_MOTHERSHIP:
			mStrDisplay << "A Mothership";
			break;

		case GAV_SPACE_FIGHTER:
			mStrDisplay << "A Space Fighter";
			break;

		case GAV_TANK:
			mStrDisplay << "A Tank";
			break;

		case GAV_TRANSPORT:
			mStrDisplay << "A Transport Ship";
			break;

		case GAV_WORKER:
			mStrDisplay << "A Worker";
			break;
		}
		mStrDisplay << " has been destroyed!";
		gpNewsTicker->AddNewElement(mStrDisplay.str(), true);
		mStrDisplay.str("");
	}

	// Do not allow the unit to be selected again by removing the bounding sphere
	mBoundingSphere = SBoundingSphere();

	// Remove the model
	UnloadIModel();
}

void CGameAgent::SaveAgent(std::ofstream& outFile)
{
	// Save the data for this unit
	outFile << mAgentInfo.mAgentType << " " << mFaction << " " << mState
		<< " " << mWorldPos.x << " " << mWorldPos.y << " " << mWorldPos.z
		<< " " << mHealth << std::endl;
}

void CGameAgent::LoadAgent(std::ifstream& inFile)
{
	// Ensure the model for the unit is not already loaded
	UnloadIModel();

	// Store the required data for the structure
	int faction;
	int state;
	int qSize;
	inFile >> faction >> state >> mWorldPos.x >> mWorldPos.y >> mWorldPos.z
		>> mHealth;

	// Convert required values to enums
	mFaction = static_cast<EFactions>(faction);
	mState = static_cast<EObjectStates>(state);

	// Load a pointer to the player based on the faction
	if (mFaction == FAC_EARTH_DEFENSE_FORCE)
	{
		mpOwner = CStateControl::GetInstance()->GetPlayerManager()->GetHumanPlayer();
	}
	else if (mFaction == FAC_THE_CRIMSON_LEGION)
	{
		mpOwner = CStateControl::GetInstance()->GetPlayerManager()->GetAIPlayer(0);
	}

	// Load the model
	LoadIModel();

	// Calculate the bounding sphere
	CalculateBoundingSphere();
}

void CGameAgent::SetSelectedTexture()
{
	// Change the shadow texture to the selected one
	if (mpObjShadow) mpObjShadow->SetSkin("tlxmul_unitShadowSelected.tga");

	// If there is a selected target, set its texture to targeted
	if (mAttackTarget)
	{
		mAttackTarget->SetTargetTexture();
	}

	// If there is a path target, place an arrow there
	if (mHasPathTarget)
	{
		SetWaypointArrow();
		// * TO DO *
	}

	// Raise selected flag
	mUnitSelected = true;
}

void CGameAgent::SetDeselectedTexture()
{
	// Set the shadow texture back to the default
	if (mpObjShadow) mpObjShadow->SetSkin("tlxmul_unitShadow.tga");

	// If there is a selected target, set it back to its normal texture
	if (mAttackTarget)
	{
		mAttackTarget->SetNormalTexture();
	}

	// If there is a path target, remove the waypoint arrow
	if (mHasPathTarget)
	{
		DeleteWaypointArrow();
	}

	// Lower selected flag
	mUnitSelected = false;
}



void CGameAgent::SetAttackTarget(CGameObject* target)
{
	// If there is already a target selected, and this unit is selected, change the target's texture back to normal
	if (mAttackTarget && mUnitSelected) mAttackTarget->SetNormalTexture();

	if (target != this)
	{
		// Apply target
		mAttackTarget = target;

		// Check if a target exists
		if (mAttackTarget)
		{
			// Go through units applying limits on what they can target
			switch (mAgentInfo.mAgentType)
			{
			case GAV_ARTILLERY:
				// If the target is not airborn, target cannot be applied
				if (mAttackTarget->IsGroundType())
				{
					mAttackTarget = nullptr;
				}
				break;
			case GAV_BOMBER:
				// If the target is airborn, target cannot be applied
				if (!mAttackTarget->IsGroundType())
				{
					mAttackTarget = nullptr;
				}
				break;
			case GAV_FIGHTER:
				// No limitations
				break;
			case GAV_INFANTRY:
				// If the target is airborn, target cannot be applied
				if (!mAttackTarget->IsGroundType())
				{
					mAttackTarget = nullptr;
				}
				break;
			case GAV_TANK:
				// If the target is airborn, target cannot be applied
				if (!mAttackTarget->IsGroundType())
				{
					mAttackTarget = nullptr;
				}
				break;
			case GAV_WORKER:
				// Worker cannot have an attack target
				mAttackTarget = nullptr;
				break;
			}
		}

		// If the target is selected, highlight the target by giving it a red texture
		if (mUnitSelected && mAttackTarget) mAttackTarget->SetTargetTexture();
	}
}

bool CGameAgent::CheckLOS(CStructure* pStructure)
{
	// Varify objects and health
	if (!mpObjModel || mHealth <= 0.0f) return false;

	// Get local Z axis
	float distance;
	DX::XMFLOAT4X4 objMatrix;
	mpObjModel->GetMatrix(&objMatrix.m[0][0]);
	DX::XMFLOAT3 localZ{ objMatrix.m[2][0], objMatrix.m[2][1], objMatrix.m[2][2] };

	// Normalise this local axis
	DX::XMVECTOR vecNormal = DX::XMVector4Normalize(DX::XMLoadFloat3(&localZ));
	DX::XMStoreFloat3(&localZ, vecNormal);
	
	// Check if the object can see the wall
	bool inLOS = pStructure->RayCollision(mWorldPos, localZ, distance);

	// If in LOS and within threshold then return true
	if (inLOS && distance < 10.0f)
	{
		return true;
	}

	// No LOS or not close enough
	return false;
}

void CGameAgent::Stop()
{
	// Stop everything that the agent could be doing
	mHasPathTarget = false;
	DeleteWaypointArrow();
	if (mAttackTarget && mUnitSelected) mAttackTarget->SetNormalTexture();
	mAttackTarget = nullptr;
}
