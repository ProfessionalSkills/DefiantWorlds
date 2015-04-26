//-----------------------------------------------------
// FILE: Turret.cpp
//-----------------------------------------------------


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "AATurret.h"

IMesh* CTurretStructure::mspMshTurret = nullptr;
IMesh* CTurretStructure::mspMshTurretShell = nullptr;
//-----------------------------------------------------
// STATIC STRUCTURE CLASS CONSTRUCTORS & DESTRUCTOR
//-----------------------------------------------------
CTurretStructure::CTurretStructure(DX::XMFLOAT3 position)
{
	mpObjModel = mspMshTurret->CreateModel(position.x, 73.0f, position.z); //Position Turret at top of tower
	mpObjModel->Scale(5.0f);
	mHealth = 100.0f;
	mRange = 250.0f;
	mWorldPos = { position.x, 70.0f, position.z };
	mState = OBJ_BUILT;
	mMaxHealth = 100.0f;
	mDamage = 14.0f;
}

CTurretStructure::~CTurretStructure()
{

}


//-----------------------------------------------------
// STATIC STRUCTURE CLASS OVERRIDE METHODS
//-----------------------------------------------------
bool CTurretStructure::Update(CRTSPlayer* pPlayer)
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
				SafeDelete(mWarningSmoke);
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

		if (mAttackTarget != nullptr) //If the turret has a target
		{
			// Check if target is dead
 			if (mAttackTarget->GetHealth() <= 0.0f)
			{
				mAttackTarget = nullptr;
			}
			// Check the target is not in space or constructing
			else if (!mAttackTarget->GetModel() || mAttackTarget->GetState() == OBJ_CONSTRUCTING)
			{
				mAttackTarget = nullptr;
			}
			else
			{
				//Get the distance between target and turret
				float distX = ((GetWorldPos().x - mAttackTarget->GetWorldPos().x) * (GetWorldPos().x - mAttackTarget->GetWorldPos().x));
				float distY = ((GetWorldPos().y - mAttackTarget->GetWorldPos().y) * (GetWorldPos().y - mAttackTarget->GetWorldPos().y));
				float distZ = ((GetWorldPos().z - mAttackTarget->GetWorldPos().z) * (GetWorldPos().z - mAttackTarget->GetWorldPos().z));

				float distance = distX + distY + distZ;

				//If the target is out of range, remove it as a target
				if (distance > (mRange * mRange))
				{
					mAttackTarget = nullptr;
				}
			}

			// If there is still a target, attack it
			if (mAttackTarget != nullptr)
			{
				Attack(mAttackTarget, 100, mDamage);
			}
		}

		return true;

		break;

	case OBJ_DEAD:

		// Object no longer alive
		return false;

		break;
	}

	if (mpProjectiles.size() > 0)
	{
		for (auto iter = mpProjectiles.begin(); iter != mpProjectiles.end(); iter++) //For each projectile that unit has fired
		{
			SProjectile* projectile = (*iter);
			projectile->Update();
			DX::XMFLOAT3 position = { projectile->mModel->GetX(), projectile->mModel->GetY(), projectile->mModel->GetZ() }; //projectile's new position stored for collision detection

			// Check to see if the attack target has been lost or it has been destroyed
			if (mAttackTarget == nullptr)
			{
				SafeDelete(projectile);
				mpProjectiles.erase(iter);
				break;
			}
			else if (mAttackTarget->SphereCollision(projectile->mCollisionSphere)) //Point to Box collision between the projectile and the attack target
			{
				mAttackTarget->TakeDamage(mDamage);
				mpAttackExplosions.push_back(new CExplosion(position, 25, false));
				SafeDelete(projectile);
				mpProjectiles.erase(iter);
				break; //Breaks out of the loop as the vector size has been changed, comprimising the iterator loop
			}
		}
	}

	if (mpAttackExplosions.size() > 0)
	{
		for (auto explosions : mpAttackExplosions) //For each explosion resulting from a projectile colliding
		{
			explosions->UpdateSystem(); //Update systems 
		}
	}
}

void CTurretStructure::DisplayInfo(IFont* font)
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

EErrorTypes CTurretStructure::AddToQueue(size_t agentIndex, CRTSPlayer* pPlayer)
{
	return ERR_NONE;
}

void CTurretStructure::UnloadIModel()
{

}
void CTurretStructure::LoadIModel()
{

}

void CTurretStructure::SaveStructure(std::ofstream& outFile)
{
	// Save to the output file all the required data
	outFile << mStructureType << " " << mGridPos.mPosX << " " << mGridPos.mPosY << " " << mFaction << " " << mState
		<< " " << mWorldPos.x << " " << mWorldPos.y << " " << mWorldPos.z << " " << mHealth << " " << 0 << " ";

	outFile << mOrientation << std::endl;
}

void CTurretStructure::LoadStructure(std::ifstream& inFile, CGrid* pGrid, CRTSPlayer* pPlayer)
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

bool CTurretStructure::Attack(CGameObject* pTarget, float hitMod, float damageMod)
{
	// The RayCollision function calculates this value for us - so it needs no starting value. Only to be defined.
	float distance;

	// Get the local Z axis of the turret
	DX::XMFLOAT3 target = mAttackTarget->GetWorldPos();
	DX::XMFLOAT4X4 objMatrix;
	mpObjModel->GetMatrix(&objMatrix.m[0][0]);

	DX::XMFLOAT3 localZ{ objMatrix.m[2][0], objMatrix.m[2][1], objMatrix.m[2][2] };

	// Normalise this local axis
	DX::XMVECTOR vecNormal = DX::XMVector4Normalize(DX::XMLoadFloat3(&localZ));
	DX::XMStoreFloat3(&localZ, vecNormal);
	DX::XMFLOAT3 worldPos = { mWorldPos.x, 75.0f, mWorldPos.z };
	// If the target is being looked at and is within range
	if (mAttackTarget->RayCollision(worldPos, localZ, distance) && distance <= mRange)
	{
		// Calculate direction vector from the aircraft to the target
		DX::XMFLOAT3 dir{ target.x - mWorldPos.x, target.y - mWorldPos.y, target.z - mWorldPos.z };

		// Normalise direction vector
		DX::XMVECTOR vecNormal = DX::XMVector4Normalize(DX::XMLoadFloat3(&dir));
		DX::XMStoreFloat3(&dir, vecNormal);

		if (mAttackTimer >= (1.0f / mFireRate)) //Control rate of fire of the unit
		{
			SProjectile* newProjectile = new SProjectile();
			newProjectile->mModel = mspMshTurretShell->CreateModel(mWorldPos.x, mWorldPos.y, mWorldPos.z);
			newProjectile->mDirection = dir;
			newProjectile->mSpeed = 1000.0f;
			newProjectile->mLifeTime = 10.0f;

			mpProjectiles.push_back(newProjectile);
			mAttackTimer = 0.0f;
		}
	}
	else
	{
		// Move the unit toward the target
		LookingAt();
	}
	// Increment attack timer
	mAttackTimer += gFrameTime;
	return true;
}

bool CTurretStructure::LookingAt()
{
	DX::XMFLOAT3 targetPosition = mAttackTarget->GetWorldPos();
	DX::XMFLOAT3 vectorZ = { (targetPosition.x - mpObjModel->GetX()), 0.0f, (targetPosition.z - mpObjModel->GetZ()) };

	float matrix[16];
	mpObjModel->GetNode(2)->GetMatrix(matrix);

	DX::XMFLOAT3 facingVector = { matrix[8], matrix[9], matrix[10] };
	const DX::XMFLOAT3 kYAxis(0.0f, 1.0f, 0.0f);

	float dotProduct = Dot(vectorZ, Cross(kYAxis, facingVector));

	if (dotProduct > 0.01f)
	{
		mpObjModel->GetNode(2)->RotateY(100.0f * gFrameTime);
		return false;
	}
	else if (dotProduct < -0.01f)
	{
		mpObjModel->GetNode(2)->RotateY(-100.0f * gFrameTime);
		return false;
	}
	else
	{
		return true;
	}
}