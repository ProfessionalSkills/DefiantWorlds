//-----------------------------------------------------
// FILE: Bomber.cpp
//-----------------------------------------------------


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "Bomber.h"

IMesh* CBomber::mspMshBomber = nullptr;


//-----------------------------------------------------
// BOMBER CLASS CONSTRUCTORS & DESTRUCTOR
//-----------------------------------------------------
CBomber::CBomber()
{
	mAgentInfo = SAgentData(GAV_BOMBER, "Bomber");
	mHealth = 100.0f;
	mSpeed = 1.0f;
	mProductionTime = 10.0f;
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

CBomber::~CBomber()
{

}


//-----------------------------------------------------
// BOMBER CLASS OVERRIDE METHODS
//-----------------------------------------------------
bool CBomber::Attack(CGameAgent* target, float hitMod, float damageMod)
{
	return false;
}

//CBomber::void MoveTo(CTile* dest)


bool CBomber::Move()
{
	return false;
}

bool CBomber::Destroy()
{
	return false;
}

IModel* CBomber::CreateModel(DX::XMFLOAT3 pos)
{
	return mspMshBomber->CreateModel(pos.x, pos.y, pos.z);
}