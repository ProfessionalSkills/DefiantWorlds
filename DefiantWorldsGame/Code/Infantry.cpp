//-----------------------------------------------------
// FILE: Infantry.cpp
//-----------------------------------------------------


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "Infantry.h"

IMesh* CInfantry::mspMshInfantry = nullptr;
IMesh* CInfantry::mspMshInfantryBullet = nullptr;

//-----------------------------------------------------
// INFANTRY CLASS CONSTRUCTORS & DESTRUCTOR
//-----------------------------------------------------
CInfantry::CInfantry()
{
	mAgentInfo = SAgentData(GAV_INFANTRY, "Infantry");
	mMaxHealth = 250.0f;
	mHealth = 250.0f;
	mSpeed = 18.0f;
	mProductionTime = 12.0f;
	mCurProductionTimeLeft = mProductionTime;
	mDamage = 25.0f;
	mFireRate = 2.0f;
	mAttackTimer = 1.0f / mFireRate;
	mHasPathTarget = false;
	mAttackTarget = nullptr;
	mState = OBJ_CONSTRUCTING;
	mIsMoving = false;
	mScale = 1.5f;
	mBuildCost = 300;
	mPopCost = 2;
	mTurretNode = 3;
	mRange = 50.0f;
	mObjectType = Q_INFANTRY;
}

CInfantry::~CInfantry()
{

}

//-----------------------------------------------------
// INFANTRY CLASS METHODS
//-----------------------------------------------------

void CInfantry::UnloadIModel()
{
	if (mpObjModel != 0)
	{
		mspMshInfantry->RemoveModel(mpObjModel);
		mpObjModel = nullptr;
	}
}

void CInfantry::LoadIModel()
{
	if (mpObjModel == nullptr)
	{
		mpObjModel = mspMshInfantry->CreateModel(mWorldPos.x, mWorldPos.y, mWorldPos.z);
		mpObjModel->Scale(mScale);
		mpObjModel->RotateY(180.0f);
		if (mFaction == FAC_EARTH_DEFENSE_FORCE)
		{
			mpObjModel->SetSkin("tiger.jpg");
		}
		else
		{
			mpObjModel->SetSkin("tigerMars.jpg");
		}
	}
}


//-----------------------------------------------------
// INFANTRY CLASS OVERRIDE METHODS
//-----------------------------------------------------
bool CInfantry::Attack(CGameObject* target, float hitMod, float damageMod)
{
	// The RayCollision function calculates this value for us - so it needs no starting value. Only to be defined.
	float distance;

	// Get the local Z axis of the turret
	DX::XMFLOAT4X4 objMatrix;
	DX::XMFLOAT4X4 turMatrix;
	mpObjModel->GetMatrix(&objMatrix.m[0][0]);
	mpObjModel->GetNode(mTurretNode)->GetMatrix(&turMatrix.m[0][0]);

	// As the matrix of the turret is RELATIVE to the base model matrix, you have to multiply them together to get the ACTUAL matrix for the turret
	DX::XMFLOAT4X4 finalMatrix;
	DX::XMMATRIX matMul = DX::XMMatrixMultiply(DX::XMLoadFloat4x4(&objMatrix), DX::XMLoadFloat4x4(&turMatrix));
	DX::XMStoreFloat4x4(&finalMatrix, matMul);

	DX::XMFLOAT3 localZ{ finalMatrix.m[2][0], finalMatrix.m[2][1], finalMatrix.m[2][2] };

	// Normalise this local axis
	DX::XMVECTOR vecNormal = DX::XMVector4Normalize(DX::XMLoadFloat3(&localZ));
	DX::XMStoreFloat3(&localZ, vecNormal);

	// If the target is being looked at and is within range
	if (mAttackTarget->RayCollision(mWorldPos, localZ, distance) && distance <= mRange)
	{
		if (mAttackTimer >= (1.0f / mFireRate)) //Control rate of fire of the unit
		{
			SProjectile* newProjectile = new SProjectile();
			newProjectile->mModel = mspMshInfantryBullet->CreateModel(mWorldPos.x, mWorldPos.y, mWorldPos.z);
			newProjectile->mDirection = localZ;
			newProjectile->mSpeed = 1000.0f;
			newProjectile->mLifeTime = 3.0f;

			mpProjectiles.push_back(newProjectile);
			mAttackTimer = 0.0f;
		}
	}

	// Do this bit all the time so that if the target is moving, it follows it whilst still firing (for added effect)
	DX::XMFLOAT3 vectorZ = { (target->GetWorldPos().x - mWorldPos.x), 0.0f, (target->GetWorldPos().z - mWorldPos.z) };
	// Normalise vectorZ
	vecNormal = DX::XMVector4Normalize(DX::XMLoadFloat3(&vectorZ));
	DX::XMStoreFloat3(&vectorZ, vecNormal);

	DX::XMFLOAT3 localX = { finalMatrix.m[0][0], finalMatrix.m[0][1], finalMatrix.m[0][2] };

	// Normalise this local axis
	vecNormal = DX::XMVector4Normalize(DX::XMLoadFloat3(&localX));
	DX::XMStoreFloat3(&localX, vecNormal);

	float dotProduct = Dot(localX, vectorZ);

	if (dotProduct > 0.001f)
	{
		mpObjModel->GetNode(mTurretNode)->RotateY(250.0f * gFrameTime);
	}
	else if (dotProduct < -0.001f)
	{
		mpObjModel->GetNode(mTurretNode)->RotateY(-250.0f * gFrameTime);
	}

	// Check for is the dot product is in the range of -0.001 and 0.001. The reason for this is to make sure
	// that the target is IN FRONT of the turret and not behind it
	if (dotProduct > -0.001f && dotProduct < 0.001f)
	{
		// Do another dot product, this time checking for it being in front
		dotProduct = Dot(localZ, vectorZ);

		// Check for behind
		if (dotProduct < 0.0f)
		{
			mpObjModel->GetNode(mTurretNode)->RotateY(250.0f * gFrameTime);
		}
	}

	// Increment attack timer
	mAttackTimer += gFrameTime;
	return false;
}

bool CInfantry::Destroy()
{
	UnloadIModel();
	return false;
}

IModel* CInfantry::CreateModel(DX::XMFLOAT3 pos)
{
	// Load model and set required skin
	IModel* pModel = mspMshInfantry->CreateModel(pos.x, pos.y, pos.z);
	if (mFaction == FAC_EARTH_DEFENSE_FORCE)
	{
		pModel->SetSkin("tiger.jpg");
	}
	else
	{
		pModel->SetSkin("tigerMars.jpg");
	}

	return pModel;
}
