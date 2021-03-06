//-----------------------------------------------------
// FILE: GameObject.cpp
//-----------------------------------------------------


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "GameObject.h"


//-----------------------------------------------------
// GAME OBJECT CLASS CONSTRUCTORS & DESTRUCTOR
//-----------------------------------------------------
CGameObject::CGameObject()
{
	mpObjModel = nullptr;
	mDestructionExplosion = nullptr;
	mWarningSmoke = nullptr;
	mPopCost = 1;
}

CGameObject::~CGameObject()
{
	if (mWarningSmoke) SafeDelete(mWarningSmoke);
}


//-----------------------------------------------------
// GAME OBJECT CLASS MUTATORS
//-----------------------------------------------------
void CGameObject::SetGridPos(SPointData pos)
{

}

void CGameObject::SetWorldPos(DX::XMFLOAT3 pos)
{
	if (mpObjModel)
	{
		mpObjModel->SetPosition(pos.x, pos.y, pos.z);
	}
	mWorldPos = pos;
}

void CGameObject::SetOrientation(float orientation)
{

}

void CGameObject::ChangeRelativeOrientation(float amount)
{

}
