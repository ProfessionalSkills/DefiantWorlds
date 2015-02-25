//-----------------------------------------------------
// FILE: Fighter.cpp
//-----------------------------------------------------


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "Fighter.h"

IMesh* CFighter::mspMshFighter = nullptr;


//-----------------------------------------------------
// FIGHTER CLASS CONSTRUCTORS & DESTRUCTOR
//-----------------------------------------------------
CFighter::CFighter()
{
	mAgentInfo = SAgentData(GAV_FIGHTER, "Fighter");
	mHealth = 100.0f;
	mSpeed = 1.0f;
	mProductionTime = 15.0f;
	mProductionCost = 0.0f;
	mCurProductionTimeLeft = mProductionTime;
	mDamage = 1.0f;
	//mAttackParticleFX;
	//mDestroyParticleFX;
	mState = OBJ_CONSTRUCTING;
	//mDestGridSq;
	mIsMoving = false;
	mPopCost = 1;
}

CFighter::~CFighter()
{

}

//-----------------------------------------------------
// FIGHTER CLASS METHODS
//-----------------------------------------------------

void CFighter::UnloadIModel()
{
	if (mpObjModel != 0)
	{
		mspMshFighter->RemoveModel(mpObjModel);
		mpObjModel = nullptr;
	}
}


//-----------------------------------------------------
// FIGHTER CLASS OVERRIDE METHODS
//-----------------------------------------------------
bool CFighter::Attack(CGameAgent* target, float hitMod, float damageMod)
{
	return false;
}


//CFighter::void MoveTo(CTile* dest)


bool CFighter::Move()
{
	return false;
}

bool CFighter::Destroy()
{
	return false;
}

IModel* CFighter::CreateModel(DX::XMFLOAT3 pos)
{
	return mspMshFighter->CreateModel(pos.x, pos.y, pos.z);
}
