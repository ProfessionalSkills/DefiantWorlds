//-----------------------------------------------------
// FILE: Fleet.cpp
//-----------------------------------------------------


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "Fleet.h"
#include "GameStateControl.h"


//-----------------------------------------------------
// FLEET CLASS CONSTRUCTORS & DESTRUCTOR
//-----------------------------------------------------
CFleet::CFleet() :mFleetRowSize(20), mFleetRowSeperation(7), mFleetZAdjust(8), mFleetYCyleHeight(0.01f), mNumFleetSections(5),
mSpecialAttackCooldownTime(5.0f), mExplosionTime(4.0f), mExplosionNumParticle(25.0f), mSpecialAttackCost(500.0f),
mSceneStartX(500.0f), mSceneDuration(5.0f)
{
	//Value Mods
	mDamegMod = 1.0f;
	mHitMod = 1.0f;
	mSize = 0;
	mTargetedFireVariance = 5;
	mFleetYAdjust = 20.0f;

	//Tactics
	mFleetTactics = None;
	mShotsFired = 0;
	mHits = 0;
	mFleetSectionFiring = 0;

	//scene
	mSceneTimeElapsed = 0.0f;

	//Misc
	mTarget = new CRandomiser();
	mFleetYHeighCycle = mTarget->GetRandomFloat(0.0, 6.0);//starts the fleet adjust cycle on a random point, so both fleets dont just float at the same hight all the time
	mNumMothership = 0;
	mNumSpaceFighter = 0;
	mNumTransport = 0;
	mUnitsLostValue = 0;

	//used to determine weather or not the fleet can use its special attacks
	mSpecialAttackCooldownTimer = 0.0f;
	mFleetWidth = (mFleetRowSize/2)-1;
}

CFleet::~CFleet()
{
	if (mTarget != 0) delete mTarget;
}

//-----------------------------------------------------
// FLEET CLASS METHODS
//-----------------------------------------------------
void CFleet::MoveFleet()
{
	for (int i = 0; i < mSize; i++)
	{
		mpFleet[i]->Move();
	}
}

void CFleet::IdleFleet()
{
	mFleetYHeighCycle += gFrameTime;
	float yChange=mFleetYCyleHeight*sinf(mFleetYHeighCycle);
	CSpaceUnit* mpTemp = nullptr;
	for (int i = 0; i < mSize; i++)
	{
		mpTemp = (CSpaceUnit*)(mpFleet[i]);
		mpTemp->MoveY(yChange*0.1f);
	}
}

void CFleet::ChargeFleetLazers()
{
	for (int i = 0; i < mSize; i++)
	{
		CSpaceUnit* mpTemp = (CSpaceUnit*)(mpFleet[i]);
		mpTemp->ChargeLazer();
	}
}


void CFleet::Fight()
{
	if (mpEnemyFleet->GetSize() != 0)
	{
		int target = 0;
		
		switch (mFleetTactics)
		{
			case Tactics::None:
				//just gets each ship to attack one random enemy ship, no effects on accuracy or damage
				for (int i = mFleetSectionFiring*mSize / mNumFleetSections; i < (mFleetSectionFiring + 1)*mSize / mNumFleetSections; i++)
				{
					target = mTarget->GetRandomInt(0, mpEnemyFleet->GetSize() - 1);
					if (mpFleet[i]->Attack(mpEnemyFleet->GetShip(target), mHitMod, mDamegMod)) mHits++;
					mShotsFired++;
				}

				break;
			case Tactics::Rapid:
				//gets each ship to attack the same enemy twice
				//reduces accuracy of the ship
				for (int i = mFleetSectionFiring*mSize / mNumFleetSections; i < (mFleetSectionFiring + 1)*mSize / mNumFleetSections; i++)
				{
					target = mTarget->GetRandomInt(0, mpEnemyFleet->GetSize() - 1);
					if (mpFleet[i]->Attack(mpEnemyFleet->GetShip(target), mHitMod, mDamegMod)) mHits++;
					if (mpFleet[i]->Attack(mpEnemyFleet->GetShip(target), mHitMod, mDamegMod)) mHits++;
					mShotsFired++;
					mShotsFired++;
				}

				break;
			case Tactics::Targeted:
				//picks a section of the enemy fleet to attack
				//only attacks ship withn a range of that target
				target = mTarget->GetRandomInt(0, mpEnemyFleet->GetSize() - 1);
				int variance=0;
				for (int i = mFleetSectionFiring*mSize / mNumFleetSections; i < (mFleetSectionFiring + 1)*mSize / mNumFleetSections; i++)
				{
					mTarget->SetSeed((float)mHits, (float)mpEnemyFleet->GetShip(0)->GetHealth());
					mShotsFired++;
					if (mpEnemyFleet->GetSize()>1)
					{
						target = mTarget->GetRandomInt(-mTargetedFireVariance, mTargetedFireVariance);
						target = abs(target) % (mpEnemyFleet->GetSize() - 1);
					}
					else target = 0;
					if (mpFleet[i]->Attack(mpEnemyFleet->GetShip(target), mHitMod, mDamegMod)) mHits++;
				}
				break;
		}
		mFleetSectionFiring = (mFleetSectionFiring + 1) % mNumFleetSections;
	}
}

void CFleet::UpdateCondition()
{
	//reduces the cooldown time for special attacks
	if (mSpecialAttackCooldownTimer >= 0)mSpecialAttackCooldownTimer -= gFrameTime;

	//gets the health of all the ships in the fleet, then gets rid of any that are less than zero
	for (int i = 0; i < mSize; i++)
	{
		if (mpFleet[i]->GetHealth() < 0.0f)
		{
			switch (mpFleet[i]->GetPosType())
			{
			case front:
				mNumSpaceFighter--;
				break;
			case centre:
				mNumTransport--;
				break;
			case back:
				mNumMothership--;
				break;
			default:
				break;
			}
			
			CSpaceUnit* mpTemp = (CSpaceUnit*)(mpFleet[i]);
			mUnitsLostValue += mpTemp->GetPopValue()+mpTemp->GetCargoValue();
			mpFleet[i] = mpFleet[mSize - 1];
			mpFleet.pop_back();
			CExplosion* temp = new CExplosion(mpTemp->GetWorldPos(), mExplosionNumParticle, false);
			M_Explosions.emplace(temp,mExplosionTime);

			delete mpTemp;
			mSize--;
		}
	}

}

void CFleet::UpdateExplosions()
{
	//updates the explosions, and then deletes them after they have been onscreen for a given amount of time
	for (auto x : M_Explosions)
	{
		x.first->UpdateSystem();
		x.second -= gFrameTime;
		if (x.second < 0.0f)
		{
			mpParticleIt = M_Explosions.find(x.first);
			delete x.first;
			M_Explosions.erase(mpParticleIt);
		}
	}
}

int CFleet::YSwitch(int x)
{
	if (x < -mFleetWidth || x>mFleetWidth)return 0;
	if (x > 0) return x*-1;
	else return (x*-1) + 1;
}

void CFleet::LoadShipModels(float xPos)
{
	SetShipPositions(xPos);
	int posMod;
	CSpaceUnit* temp;
	//reset scene
	mSceneTimeElapsed = 0;

	if (xPos < 0.0f)
	{
		posMod = -1;
	}
	else
	{
		posMod = 1;
	}

	for (auto unit: mpFleet)
	{
		temp = (CSpaceUnit*)unit;
		unit->LoadModel(posMod*mSceneStartX, 0.0f, temp->GetTargetPos().z - temp->GetTravelRadius());
	}
}

void CFleet::SetShipPositions(float xPos)
{
	int SpaceFighterLoaded = 0;
	int TransportLoaded = 0;
	int MothershipLoaded = 0;
	int SpaceFighterY = 0;
	int TransportY = 0;
	int MothershipY = 0;
	int posMod = 1;
	int TransportRowsBack = (mNumSpaceFighter / mFleetRowSize) + 1;
	int MotherShipRowsBack = (mNumTransport / mFleetRowSize) + TransportRowsBack + 1;
	float StartingX = 0;
	if (xPos < 0.0f)
	{
		posMod = -1;
		StartingX = -mSceneStartX;
	}
	else
	{
		posMod = 1;
		StartingX = mSceneStartX;
	}
	CSpaceUnit* temp;

	for (int i = 0; i < mSize; i++)
	{
		temp = (CSpaceUnit*)mpFleet[i];
		//uses intager deviosion to seperate ships into rows of x, where x is the fleet row size, and each row is seperated by a distance of fleet row seperation
		switch (mpFleet[i]->GetPosType())
		{
		case front:
			temp->SetTargetPos(xPos + (float)((SpaceFighterLoaded / mFleetRowSize) * (mFleetRowSeperation)*posMod),
				((float)SpaceFighterY*mFleetRowSeperation) + mFleetYAdjust, (float)mFleetZAdjust*SpaceFighterY);
			SpaceFighterLoaded++;
			SpaceFighterY = YSwitch(SpaceFighterY);
			break;
		case centre:
			temp->SetTargetPos(xPos + (float)(((TransportLoaded / mFleetRowSize) + TransportRowsBack + mpFleet[i]->GetUnitSpacing()) * mFleetRowSeperation*posMod),
				((float)TransportY*mFleetRowSeperation) + mFleetYAdjust, (float)mFleetZAdjust*TransportY);
			TransportLoaded++;
			TransportY = YSwitch(TransportY);
			break;
		case back:
			temp->SetTargetPos(xPos + (float)(((MothershipLoaded / mFleetRowSize) + MotherShipRowsBack + mpFleet[i]->GetUnitSpacing()) * mFleetRowSeperation*posMod),
				((float)MothershipY*mFleetRowSeperation) + mFleetYAdjust, (float)mFleetZAdjust*MothershipY);
			MothershipLoaded++;
			MothershipY = YSwitch(MothershipY);
			break;
		default:
			break;
		}
		temp->CalculateSceneValues(mSceneDuration,StartingX);
	}
}

void CFleet::UnloadShieldModels()
{
	for (int i = 0; i < mSize; i++)
	{
		// Unload the shield for this space unit
		CSpaceUnit* mpTemp = (CSpaceUnit*)(mpFleet[i]);
		mpTemp->UnloadFlash();
	}
}

void CFleet::UnloadLazers()
{
	for (int i = 0; i < mSize; i++)
	{
		// Unload the shield for this space unit
		CSpaceUnit* mpTemp = (CSpaceUnit*)(mpFleet[i]);
		mpTemp->UnloadLazer();
	}
}

bool CFleet::SpecialAttackLazerBarrage(CRTSPlayer* player)
{
	if (player->GetMineralAmount()>mSpecialAttackCost)
	{
		if (mSpecialAttackCooldownTimer <= 0)
		{
			for (int i = 0; i < mSize; i++)
			{
				if (mpFleet[i]->GetAgentData()->mAgentType == GAV_MOTHERSHIP)
				{
					int target = 0;
					for (int j = 0; j < 10; j++)
					{
						target = mTarget->GetRandomInt(0, mpEnemyFleet->GetSize() - 1);
						if (mpFleet[i]->Attack(mpEnemyFleet->GetShip(target), mHitMod, mDamegMod)) mHits++;
						mShotsFired++;
					}
					mSpecialAttackCooldownTimer = mSpecialAttackCooldownTime;
					player->MineralTransaction((int)-mSpecialAttackCost);
					gpNewsTicker->AddNewElement("Mothership Fired a Lazer Barrage", false);
					return true;
				}
			}
			gpNewsTicker->AddNewElement("You need a mothership to use this attack", false);
		}
		else
		{
			gpNewsTicker->AddNewElement("Special attacks are on cooldown", false);
		}
	}
	else
	{
		gpNewsTicker->AddNewElement("Not enough minerals to use this attack", false);
	}
	return false;
}

bool CFleet::SpecialAttackMassHeal(CRTSPlayer* player)
{
	if (player->GetMineralAmount() > mSpecialAttackCost)
	{
		if (mNumMothership != 0)
		{
			if (mSpecialAttackCooldownTimer <= 0)
			{
				for (int i = 0; i < mSize; i++)
				{
					mpFleet[i]->Heal(10.0f);
				}
				mSpecialAttackCooldownTimer = mSpecialAttackCooldownTime;
				player->MineralTransaction((int)-mSpecialAttackCost);
				gpNewsTicker->AddNewElement("Mothership Healed Fleet", false);
				return true;
			}
			else
			{
				gpNewsTicker->AddNewElement("Special attacks are on cooldown", false);
			}
		}
		else
		{
			gpNewsTicker->AddNewElement("You need a mothership to use this attack", false);
		}
	}
	else
	{
		gpNewsTicker->AddNewElement("Not enough minerals to use this attack", false);
	}
	return false;
}

bool CFleet::SceneSpaceFight()
{
	if (mSceneTimeElapsed > mSceneDuration)
	{
		return true;
	}
	else
	{
		CSpaceUnit* temp;
		for (auto x : mpFleet)
		{
			temp = (CSpaceUnit*)x;
			temp->MoveInScene();
		}
		mSceneTimeElapsed += gFrameTime;
		return false;
	}
}

//-----------------------------------------------------
// FLEET CLASS ACCESSORS
//-----------------------------------------------------

CGameAgent* CFleet::GetShip(int i)
{
	return mpFleet[i];
}

int CFleet::GetSize()
{
	return mSize;
}

int CFleet::GetRows()
{
	return (mNumSpaceFighter / mFleetRowSize) + (mNumTransport / mFleetRowSize) + 1;
}

string CFleet::GetTacticsName()
{
	switch (mFleetTactics)
	{
	case Tactics::None:
		return "None";
	case Tactics::Rapid:
		return "Rapid";
	case Tactics::Targeted:
		return "Targeted";
	}
	return "Null";
}

float CFleet::GetFleetTotalHealth()
{
	float totalHp = 0;
	for (int i = 0; i < mSize; i++)
	{
		totalHp += mpFleet[i]->GetHealth();
	}
	return totalHp;
}

float CFleet::GetFleetAvargeHealth()
{
	if (GetFleetTotalHealth()!=0) return GetFleetTotalHealth() / (float)mSize;
	else return 0;
}

float CFleet::GetFleetMaxHealth()
{
	return mFleetMaxHealth;
}

//-----------------------------------------------------
// FLEET CLASS MUTATORS
//-----------------------------------------------------

void CFleet::SetEnemy(CFleet* myEnemy)
{
	mpEnemyFleet = myEnemy;
}

bool CFleet::ManFleet(CGameAgent* UnitToLoad)
{
	for (int i = 0; i < mpFleet.size(); i++)
	{
		CSpaceUnit* mpTemp = (CSpaceUnit*)(mpFleet[i]);

		if (!mpTemp->StoreUnits(UnitToLoad)) return true;
	}
	return false;
}

vector <CGameAgent*>* CFleet::LaunchFleet(vector <CGameAgent*>* possibleShips)
{
	//temporary functionthat just transfers all of the ships from player onto fleet
	if (possibleShips->size() != 0)
	{
		for (int i = possibleShips->size() - 1; i >= 0; i--)
		{
			switch ((*possibleShips)[i]->GetPosType())
			{
			case front:
				mNumSpaceFighter++;
				break;
			case centre:
				mNumTransport++;
				break;
			case back:
				mNumMothership++;
				break;
			default:
				break;
			}
			mpFleet.push_back((*possibleShips)[i]);
			possibleShips->pop_back();
			mSize++;
		}
	}
	mFleetCurrentHealth = mFleetMaxHealth = GetFleetTotalHealth();
	return possibleShips;
}

void CFleet::SetTactic(Tactics tactics)//changes the tactics the fleet will use in battle, e.g rapid, targated
{
	mFleetTactics = tactics;
	//adds the fleet modifiers
	switch (mFleetTactics)
	{
	case Tactics::None:
		mDamegMod = 1.0f;
		mHitMod = 1.0f;

		break;
	case Tactics::Rapid:
		mDamegMod = 1.3f;
		mHitMod = 0.45f;

		break;
	case Tactics::Targeted:
		mDamegMod = 0.7f;
		mHitMod = 1.4f;

		break;
	}
	return;

}

//returns the fleet to the player
void CFleet::ReturnFleet(CRTSPlayer* Player,bool victory)
{
	int startx = 0;
	int startz = 0;
	for (int i = mSize-1; i >= 0; i--)
	{
		if (mpFleet[i]->GetAgentData()->mAgentType == GAV_TRANSPORT)
		{
			CTransport* mpTemp = (CTransport*)(mpFleet[i]);
			mpTemp->UnloadUnits(victory,startx,startz+1);
			startz = (startz + 1) % 3;
			if (startz == 0) startx++;
		}

		mpFleet[i]->UnloadIModel();
		Player->GetSpaceUnitList()->push_back(mpFleet[i]);
		mpFleet.pop_back();
		mSize--;
	}

	Player->LosePop(mUnitsLostValue);

	Player->SetNumMothership(mNumMothership);
	Player->SetNumSpaceFighter(mNumSpaceFighter);
	Player->SetNumTransport(mNumTransport);

	mNumMothership = 0;
	mNumSpaceFighter = 0;
	mNumTransport = 0;
	mShotsFired = 0;
	mHits = 0;
	mSpecialAttackCooldownTimer = 0.0f;
	mFleetMaxHealth = 0.0f;
	mFleetCurrentHealth = 0.0f;
}

