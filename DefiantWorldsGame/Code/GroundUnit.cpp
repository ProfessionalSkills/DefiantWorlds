//-----------------------------------------------------
// FILE: GroundUnit.cpp
//-----------------------------------------------------


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "GroundUnit.h"

//-----------------------------------------------------
// GROUND UNIT CLASS CONSTRUCTORS & DESTRUCTOR
//-----------------------------------------------------
CGroundUnit::CGroundUnit()
{
	mScale = 2.0f;
}

CGroundUnit::~CGroundUnit()
{	

}


//-----------------------------------------------------
// GROUND UNIT CLASS OVERRIDE METHODS
//-----------------------------------------------------

//CGroundUnit::void MoveTo(CTile* dest)

void CGroundUnit::Spawn(CGrid* pGrid, SPointData pCentre)
{					
	//Sets the tile usage so vehicles cannot overlap and spawns the vehicle in

	mpObjModel = CreateModel(DX::XMFLOAT3(pGrid->GetTileData(pCentre)->GetWorldPos().x, 1.0f, (pGrid->GetTileData(pCentre)->GetWorldPos().z)));
	mpObjModel->RotateY(180.0f);
	mWorldPos.x = pGrid->GetTileData(pCentre)->GetWorldPos().x;
	mWorldPos.y = 1.0f;
	mWorldPos.z = pGrid->GetTileData(pCentre)->GetWorldPos().z;
	mpObjModel->Scale(mScale);

	CalculateBoundingSphere();
}


bool CGroundUnit::Update()
{
	if (mState = OBJ_BUILT)
	{
		if (((mHealth / mMaxHealth) * 100.0f) <= 66.6f)
		{
			mState = OBJ_DAMAGED;
		}
	}
	else if (mState = OBJ_DAMAGED)
	{
		if (((mHealth / mMaxHealth) * 100.0f) <= 33.3f)
		{
			mState = OBJ_WARNING;
		}
	}
	else if (mState = OBJ_WARNING)
	{
		if (mHealth <= 0.0f)
		{
			mDestructionExplosion = new CExplosion(mpObjModel, 50);
			UnloadIModel();
			mState = OBJ_DEAD;
		}
	}

	if (mState != OBJ_DEAD)
	{
		if (HasTarget()) //If there is a path target
		{
			Move(); //Move the unit towards the path target
			LookingAt(mPathTarget); //Rotates the unit to face the path target
		}
		else if (mAttackTarget != nullptr) //Else if there is an attack target
		{
			Move(); //Move in range of the target
			if (mAttackTarget != nullptr)
			{
				if (LookingAt(mAttackTarget->GetWorldPos())) //Rotate the unit to face the target
				{
					Attack(mAttackTarget, 100, mDamage);
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
	// Check if the model is still alive
	else
	{
		if (!mDestructionExplosion->UpdateSystem())
		{
			SafeDelete(mDestructionExplosion);
			return false;
		}
	}

	if (mpProjectiles.size() > 0)
	{
		for (auto projectile : mpProjectiles) //For each projectile that unit has fired
		{
			projectile->mModel->MoveLocalZ(projectile->mSpeed * gFrameTime); //Move the projectile 
			DX::XMFLOAT3 position = { projectile->mModel->GetX(), projectile->mModel->GetY(), projectile->mModel->GetZ() }; //projectile's new position stored for collision detection

			if (projectile == mpProjectiles.front()) //As all projectiles move at the same speed, the only projectile that will collide is the one fired first  
			{
				if ((mAttackTarget == nullptr) || (BoxCollision(position, mAttackTarget->GetWorldPos(), 3.0f))) //Point to Box collision between the projectile and the attack target
				{
					if (mAttackTarget != nullptr)
					{
						mAttackTarget->TakeDamage(mDamage);
					}
					mpAttackExplosions.push_back(new CExplosion(projectile->mModel, 50));
					SafeDelete(projectile);
					mpProjectiles.erase(mpProjectiles.begin());
					break; //Breaks out of the loop as the vector size has been changed, comprimising the iterator loop
				}
			}
		}
	}

	return true;
}
bool CGroundUnit::LookingAt(DX::XMFLOAT3 target)
{
	if ((mAttackTarget != nullptr) && !mHasPathTarget && (mTurretNode != 0))
	{
		DX::XMFLOAT3 vectorZ = { (target.x - mpObjModel->GetNode(mTurretNode)->GetX()), (target.y - mpObjModel->GetNode(mTurretNode)->GetY()), (target.z - mpObjModel->GetNode(mTurretNode)->GetZ()) };
		float matrix[16];
		mpObjModel->GetNode(mTurretNode)->GetMatrix(matrix);

		DX::XMFLOAT3 facingVector = { matrix[8], matrix[9], matrix[10] };
		const DX::XMFLOAT3 kYAxis(0.0f, 1.0f, 0.0f);

		float dotProduct = Dot(vectorZ, Cross(kYAxis, facingVector));

		if (dotProduct > 0.1f)
		{
			mpObjModel->GetNode(mTurretNode)->RotateY(50.0f * gFrameTime);
			return false;
		}
		else if (dotProduct < -0.1f)
		{
			mpObjModel->GetNode(mTurretNode)->RotateY(-50.0f * gFrameTime);
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		DX::XMFLOAT3 targetPosition = target;
		DX::XMFLOAT3 vectorZ = { (targetPosition.x - mpObjModel->GetX()), (targetPosition.y - mpObjModel->GetY()), (targetPosition.z - mpObjModel->GetZ()) };
		float matrix[16];
		mpObjModel->GetMatrix(matrix);

		DX::XMFLOAT3 facingVector = { matrix[8], matrix[9], matrix[10] };
		const DX::XMFLOAT3 kYAxis(0.0f, 1.0f, 0.0f);

		float dotProduct = Dot(vectorZ, Cross(kYAxis, facingVector));

		if (dotProduct > 0.1f)
		{
			mpObjModel->RotateY(50.0f * gFrameTime);
			return false;
		}
		else if (dotProduct < -0.1f)
		{
			mpObjModel->RotateY(-50.0f * gFrameTime);
			return false;
		}
		else
		{
			return true;
		}
	}
}

void CGroundUnit::Move()
{
	if (mHasPathTarget)
	{
		int MaxX = mPathTarget.x + 1.0f;
		int MinX = mPathTarget.x - 1.0f;

		int MaxZ = mPathTarget.z + 1.0f;
		int MinZ = mPathTarget.z - 1.0f;

		if (mWorldPos.x > MinX && mWorldPos.x < MaxX && mWorldPos.z > MinZ && mWorldPos.z < MaxZ)
		{

		}
		else
		{
			float matrix[16];
			mpObjModel->GetMatrix(matrix);
			float movement = mSpeed * gFrameTime;
			mpObjModel->MoveLocalZ(movement);
			mWorldPos = DX::XMFLOAT3(mpObjModel->GetX(), mpObjModel->GetY(), mpObjModel->GetZ());
			DX::XMFLOAT3 moveAmount = { matrix[8] * movement, matrix[9] * movement, matrix[10] * movement };
			mBoundingSphere.MoveTo(mWorldPos);
		}
	}
	else if (mAttackTarget != nullptr)
	{
		float xDist = mAttackTarget->GetWorldPos().x - mWorldPos.x;
		float yDist = mAttackTarget->GetWorldPos().y - mWorldPos.y;
		float zDist = mAttackTarget->GetWorldPos().z - mWorldPos.z;

		float Distance = ((xDist * xDist) + (yDist * yDist) + (zDist * zDist));

		if (Distance > (mRange * mRange))
		{
			float matrix[16];
			mpObjModel->GetMatrix(matrix);
			float movement = mSpeed * gFrameTime;
			mpObjModel->MoveLocalZ(movement);
			mWorldPos = DX::XMFLOAT3(mpObjModel->GetX(), mpObjModel->GetY(), mpObjModel->GetZ());
			DX::XMFLOAT3 moveAmount = { matrix[8] * movement, matrix[9] * movement, matrix[10] * movement };
			mBoundingSphere.MoveTo(mWorldPos);
		}
		else
		{
			//if (mAttackTarget->GetHealth() <= 0.0f)
			//{
			//	mAttackTarget = nullptr;
			//}
		}
	}
}