//-----------------------------------------------------
// FILE: StaticStructure.cpp
//-----------------------------------------------------


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "StaticStructure.h"


//-----------------------------------------------------
// STATIC STRUCTURE CLASS CONSTRUCTORS & DESTRUCTOR
//-----------------------------------------------------
CStaticStructure::CStaticStructure()
{

}

CStaticStructure::~CStaticStructure()
{

}


//-----------------------------------------------------
// STATIC STRUCTURE CLASS OVERRIDE METHODS
//-----------------------------------------------------
bool CStaticStructure::Update(CRTSPlayer* pPlayer)
{
	// Determine state of the structure
	switch (mState)
	{
	case OBJ_CONSTRUCTING:
		// Change status of the building to 'built'
		mState = OBJ_BUILT;

		// Object still alive
		return true;

		break;

	case OBJ_BUILT:
		// Check if health below 50% for smoke system creation
		if (mHealth > 0.0f && ((mHealth / mMaxHealth) * 100.0f) <= 50.0f)
		{
			if (mWarningSmoke == nullptr)
			{
				mWarningSmoke = new CSmoke(mWorldPos, mHeight, 0.8f, mBoundingBox.GetWidthExtent() / 3.0f, mBoundingBox.GetLengthExtent() / 3.0f);
			}
			else
			{
				// Update smoke system
				mWarningSmoke->UpdateSystem();
			}
		}

		// Check if no health left
		if ((mHealth <= 0.0f))
		{
			if (mDestructionExplosion == nullptr)
			{
				// Check the faction of the structure
				if (gpCurWorldCamera->GetFaction() == mFaction)
				{
					gpCurWorldCamera->SetShaking(true);
				}
				
				SafeDelete(mWarningSmoke);
				if (mStructureType == STR_WALL)
					mDestructionExplosion = new CExplosion({ mWorldPos.x, mWorldPos.y + 20.0f, mWorldPos.z }, 150, true);
				else
					mDestructionExplosion = new CExplosion({ mWorldPos.x, mWorldPos.y + 20.0f, mWorldPos.z }, 150, false);
				Destroy();
			}
			else
			{
				// Check if the explosion system has finished
				if (!mDestructionExplosion->UpdateSystem())
				{
					// particle system is finished
					SafeDelete(mDestructionExplosion);
					mState = OBJ_DEAD;
				}
			}
		}

		// Check if it has been requested to raise
		if (mRaised)
		{
			// Varify height
			if (mRaisedAmount < 20.0f)
			{
				// Raise the wall more
				float movement = 50.0f * gFrameTime;
				mRaisedAmount += movement;
				mpObjModel->MoveY(movement);
				mWorldPos.y = mpObjModel->GetY();
				mBoundingBox.SetPosition(mWorldPos);
			}
			else
			{
				// Increment timer
				mRaisedTimer += gFrameTime;
				if (mRaisedTimer >= 3.5f)
				{
					// Start closing the wall
					mRaised = false;
					mRaised = 0.0f;
				}
			}
		}
		else
		{
			// Verify height back down to 0
			if (mRaisedAmount > 0.0f)
			{
				// Lower the wall more
				float movement = -50.0f * gFrameTime;
				mRaisedAmount += movement;
				mpObjModel->MoveY(movement);
				mWorldPos.y = mpObjModel->GetY();
				mBoundingBox.SetPosition(mWorldPos);
			}
		}

		return true;

		break;

	case OBJ_DEAD:

		// Object no longer alive
		return false;

		break;
	}
}

void CStaticStructure::DisplayInfo(IFont* font)
{
	// Output selected building
	switch (mStructureType)
	{
	case STR_HOUSE:
		mStrDisplay << "House";
		break;

	case STR_WALL:
		mStrDisplay << "Wall";
		break;
	}

	font->Draw(mStrDisplay.str(), 610, 825, 0xff002930, kLeft, kTop);
	mStrDisplay.str("");
}

EErrorTypes CStaticStructure::AddToQueue(size_t agentIndex, CRTSPlayer* pPlayer)
{
	return ERR_NONE;
}

void CStaticStructure::UnloadIModel()
{

}
void CStaticStructure::LoadIModel()
{

}

void CStaticStructure::SaveStructure(std::ofstream& outFile)
{
	// Save to the output file all the required data
	outFile << mStructureType << " " << mGridPos.mPosX << " " << mGridPos.mPosY << " " << mFaction << " " << mState
		<< " " << mWorldPos.x << " " << mWorldPos.y << " " << mWorldPos.z << " " << mHealth << " " << 0 << " ";

	outFile << mOrientation << std::endl;
}

void CStaticStructure::LoadStructure(std::ifstream& inFile, CGrid* pGrid, CRTSPlayer* pPlayer)
{
	// Ensure no model is already loaded for it
	UnloadIModel();
	
	// Store the required data for the structure
	int faction;
	int state;
	int pad;
	inFile >> mGridPos.mPosX >> mGridPos.mPosY >> faction >> state >> mWorldPos.x >> mWorldPos.y
		>> mWorldPos.z >> mHealth >> pad >> mOrientation;

	// Convert required values to enums
	mFaction = static_cast<EFactions>(faction);
	mState = static_cast<EObjectStates>(state);

	// Load the 3D model
	LoadIModel();
	CalculateBoundingBox();
}
