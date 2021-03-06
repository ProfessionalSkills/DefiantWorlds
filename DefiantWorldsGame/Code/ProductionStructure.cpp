//-----------------------------------------------------
// FILE: ProductionStructure.cpp
//-----------------------------------------------------


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "ProductionStructure.h"
#include "Player.h"
#include "GameStateControl.h"


//-----------------------------------------------------
// PRODUCTION STRUCTURE CLASS CONSTRUCTORS & DESTRUCTOR
//-----------------------------------------------------
CProductionStructure::CProductionStructure()
{

}

CProductionStructure::~CProductionStructure()
{

}


//-----------------------------------------------------
// PRODUCTION STRUCTURE CLASS METHODS
//-----------------------------------------------------
EErrorTypes CProductionStructure::AddToQueue(size_t agentIndex, CRTSPlayer* pPlayer)
{	
	// Check state of the production building
	if (mState == OBJ_CONSTRUCTING)
	{
		// Cannot queue units before the structure is ready
		return ERR_NOT_READY;
	}

	// Get the size of the respective agents array and compare with index
	if (agentIndex >= mRespectiveAgentsList.size())
	{
		return ERR_INCORRECT_INDEX;
	}

	// Check if queue is at maximum
	if (mpProductionQueue.size() >= MAX_QUEUE_SIZE)
	{
		// *** TO DO *** return error code rather than boolean
		return ERR_MAX_QUEUE_SIZE;
	}

	miterRespectiveAgents = mRespectiveAgentsList.begin();
	std::advance(miterRespectiveAgents, agentIndex);

	if (pPlayer->PopLimitReached((*miterRespectiveAgents)->GetPopValue()))
	{
		return ERR_POP_LIMIT;
	}
	else
	{
		pPlayer->IncreasePopValue((*miterRespectiveAgents)->GetPopValue());
	}
	// Create instance based on created type
	switch ((*miterRespectiveAgents)->GetAgentData()->mAgentType)
	{
	case GAV_ARTILLERY:
		mpProductionQueue.push_back(new CArtillery());
		break;

	case GAV_BOMBER:
		mpProductionQueue.push_back(new CBomber());
		break;

	case GAV_FIGHTER:
		mpProductionQueue.push_back(new CFighter());
		break;

	case GAV_INFANTRY:
		mpProductionQueue.push_back(new CInfantry());
		break;

	case GAV_MOTHERSHIP:
		// Check production queue for another mothership
		for (auto iter : mpProductionQueue)
		{
			if (iter->GetAgentData()->mAgentType == GAV_MOTHERSHIP)
			{
				// Show error message through the ticker, but return no error for AI purposes
				if (pPlayer->GetPlayerFaction() == FAC_EARTH_DEFENSE_FORCE) gpNewsTicker->AddNewElement("Mothership already under construction!", true);
				return ERR_NONE;
			}
		}

		// Check if there is already a mothership in the player's arsenal
		for (auto iter : (*pPlayer->GetSpaceUnitList()))
		{
			if (iter->GetAgentData()->mAgentType == GAV_MOTHERSHIP)
			{
				// Show error message through the ticker, but return no error for AI purposes
				if (pPlayer->GetPlayerFaction() == FAC_EARTH_DEFENSE_FORCE) gpNewsTicker->AddNewElement("You already own a Mothership!", true);
				return ERR_NONE;
			}
		}

		// Unit is fine to build
		mpProductionQueue.push_back(new CMothership());
		break;

	case GAV_SPACE_FIGHTER:
		mpProductionQueue.push_back(new CSpaceFighter());
		break;

	case GAV_TANK:
		mpProductionQueue.push_back(new CTank());
		break;

	case GAV_TRANSPORT:
		mpProductionQueue.push_back(new CTransport());
		break;

	case GAV_WORKER:
		mpProductionQueue.push_back(new CWorker());
		break;
	}

	// Check if the player has enough funds
	if (pPlayer->GetMineralAmount() - mpProductionQueue.back()->GetBuildCost() < 0)
	{
		// Not enough funds - remove the object at the front of the queue
		RemoveFromQueue(mpProductionQueue.size() - 1, pPlayer);
		return ERR_NO_MINERALS;
	}

	// Enough funds - subtract them
	pPlayer->MineralTransaction(-mpProductionQueue.back()->GetBuildCost());
	mpProductionQueue.back()->SetFaction(pPlayer->GetPlayerFaction());

	// Success
	return ERR_NONE;
}

std::deque<CGameAgent*>* CProductionStructure::GetQueue()
{
	return &mpProductionQueue;
}

void CProductionStructure::RemoveFromQueue(size_t agentIndex,CRTSPlayer* pPlayer)
{
	// Increment the iterator by the amount provided
	miterProdQ = mpProductionQueue.begin();
	std::advance(miterProdQ, agentIndex);
	pPlayer->IncreasePopValue(-(*miterRespectiveAgents)->GetPopValue());
	// Remove the unit at the given location
	CGameAgent* tmp = (*miterProdQ);
	SafeDelete(tmp);
	mpProductionQueue.erase(miterProdQ);
}

bool CProductionStructure::SpawnFront(CRTSPlayer* pPlayer)
{
	CGameAgent* tmp = mpProductionQueue.front();
	tmp->Spawn(mpGrid, GetGridSpawnLocation());
	tmp->SetOwner(pPlayer);

	// Display data on news ticker if this concerns the player
	if (mFaction == FAC_EARTH_DEFENSE_FORCE)
	{
		mStrDisplay << "A " << mpProductionQueue.front()->GetAgentData()->mAgentName
			<< " unit is ready for orders.";
		gpNewsTicker->AddNewElement(mStrDisplay.str(), false);
		mStrDisplay.str("");
	}

	//delete tmp;
	mpProductionQueue.pop_front();
	return false;
}

bool CProductionStructure::UpdateProduction()
{
	return false;
}

CGameAgent* CProductionStructure::CreateAgent()
{
	return nullptr;
}


//-----------------------------------------------------
// PRODUCTION STRUCTURE CLASS OVERRIDE METHODS
//-----------------------------------------------------
void CProductionStructure::UnloadIModel()
{

}

void CProductionStructure::SetBuiltModel()
{

}

bool CProductionStructure::Update(CRTSPlayer* pPlayer)
{
	// Determine state of the structure
	switch (mState)
	{ 
		case OBJ_CONSTRUCTING:
			// Update the timer left until construction is finished
			mCurBuildTimeLeft -= gFrameTime;

			// Check if the timer has reached 0
			if (mCurBuildTimeLeft < 0.0f)
			{
				// Set the building to the correct model type
				SetBuiltModel();
				if (mStructureType != STR_COM_CENTRE && pPlayer->GetPlayerFaction() == FAC_EARTH_DEFENSE_FORCE) //If the structure is not the player's command centre and belongs to the human player
				{
					ALuint alBuildBuffer = alutCreateBufferFromFile("drill.wav"); //Sets the music file
					ALuint alBuildSource;
					alGenSources(1, &alBuildSource);
					DX::XMFLOAT3 mSourcePos = { mpObjModel->GetX(), mpObjModel->GetY(), mpObjModel->GetZ() };
					DX::XMFLOAT3 mSourceVel = { 0.0f, 0.0f, 0.0f };
					DX::XMFLOAT3 listenerPos = { mpObjModel->GetX(), 50.0f, mpObjModel->GetZ() };
					DX::XMFLOAT3 listenerVel = { 0.0f, 0.0f, 0.0f };
					float volume = CStateControl::GetInstance()->GetSettingsManager()->GetEffectsVolume();		// MAKE SURE TO INCLUDE GameStateControl in the
																												// .cpp file ONLY otherwise you'll get cyclic redundancy
					mGenSound = new CSound(alBuildBuffer, mSourcePos, mSourceVel, false, volume, listenerPos, listenerVel, alBuildSource);
					mGenSound->PlaySound(); //construction sound

					// Display on ticker
					switch (GetStructureType())
					{
					case STR_BARRACKS:
						mStrDisplay << "The new Barracks";
						break;

					case STR_HELLIPAD:
						mStrDisplay << "The new Hellipad";
						break;

					case STR_SPACE_CENTRE:
						mStrDisplay << "The new Space Centre";
						break;
					}
					mStrDisplay << " has been constructed.";
					gpNewsTicker->AddNewElement(mStrDisplay.str(), false);
					mStrDisplay.str("");
				}
			
				// Change status of the building to 'built'
				mState = OBJ_BUILT;
			}
			// Object still alive
			return true;
			
			break;

		case OBJ_BUILT:
			// Update the modle being built at front of queue
			if (mpProductionQueue.size() != 0)
			{
				if (mpProductionQueue.front()->Construct())
				{
					// Unit fully constructed - add to units list
					if (mStructureType == STR_SPACE_CENTRE)
					{
						// Space units list
						pPlayer->GetSpaceUnitList()->push_back(mpProductionQueue.front());
					}
					else
					{
						// World units list
						EGameAgentVariations agentVar = mpProductionQueue.front()->GetAgentData()->mAgentType;
						pPlayer->GetWorldUnitList()->insert(GA_MultiMap::value_type(agentVar, mpProductionQueue.front()));
					}
					// Spawn the unit
					SpawnFront(pPlayer);
				}
			}

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
					if (mStructureType == STR_COM_CENTRE)
						mDestructionExplosion = new CExplosion({mWorldPos.x, mWorldPos.y + 20.0f, mWorldPos.z}, 150, true);
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
			return true;

			break;

		case OBJ_DEAD:

			// Object no longer alive
			return false;

			break;
	}
}

void CProductionStructure::DisplayInfo(IFont* font)
{
	// Output selected building
	switch (mStructureType)
	{
	case STR_BARRACKS:
		mStrDisplay << "Barracks";
		break;

	case STR_COM_CENTRE:
		mStrDisplay << "Command Centre";
		break;

	case STR_HELLIPAD:
		mStrDisplay << "Hellipad";
		break;

	case STR_SPACE_CENTRE:
		mStrDisplay << "Space Centre";
		break;
	}

	font->Draw(mStrDisplay.str(), 610, 825, 0xff002930, kLeft, kTop);
	mStrDisplay.str("");
}

void CProductionStructure::SaveStructure(std::ofstream& outFile)
{
	// Save to the output file all the required data
	outFile << mStructureType << " " << mGridPos.mPosX << " " << mGridPos.mPosY << " " << mFaction << " " << mState
		<< " " << mWorldPos.x << " " << mWorldPos.y << " " << mWorldPos.z << " " << mHealth << " " << GetQueueSize() << " ";

	// Loop through each queue item and save its type
	for (miterProdQ = mpProductionQueue.begin(); miterProdQ != mpProductionQueue.end(); miterProdQ++)
	{
		outFile << (*miterProdQ)->GetAgentData()->mAgentType << " " << (*miterProdQ)->GetCurProductionTimeLeft() << " ";
	}

	outFile << mOrientation << std::endl;
}

void CProductionStructure::LoadStructure(std::ifstream& inFile, CGrid* pGrid, CRTSPlayer* pPlayer)
{
	// Ensure no model is already loaded for it
	UnloadIModel();

	// Store the required data for the structure
	int faction;
	int state;
	int qSize;
	inFile >> mGridPos.mPosX >> mGridPos.mPosY >> faction >> state >> mWorldPos.x >> mWorldPos.y
		>> mWorldPos.z >> mHealth >> qSize;

	// Convert required values to enums
	mFaction = static_cast<EFactions>(faction);
	mState = static_cast<EObjectStates>(state);

	// Based on the queue size, load in the required details for each queue item
	int type;
	float progress;
	EGameAgentVariations agentType;
	for (int i = 0; i < qSize; i++)
	{
		inFile >> type >> progress;
		// Convert type into an agent type
		agentType = static_cast<EGameAgentVariations>(type);

		// Loop through respective agents list and get the index of the unit to create it
		int counter = 0;			// Counter is used as an index for the QueueUnit method
		for (miterRespectiveAgents = mRespectiveAgentsList.begin(); miterRespectiveAgents != mRespectiveAgentsList.end(); miterRespectiveAgents++)
		{
			// Check if this agent matches the agent trying to be created
			if (agentType == (*miterRespectiveAgents)->GetAgentData()->mAgentType)
			{
				// Queue the unit using the index
				AddToQueue(counter, pPlayer);
				mpProductionQueue.back()->SetProdTimeLeft(progress);
				break;
			}
			// Increment counter
			counter++;
		}
	}

	// Load in orientation
	inFile >> mOrientation;

	// Load the 3D model
	LoadIModel();

	// Create the structure
	SetGridData(pGrid);
	CalculateBoundingBox();
}
