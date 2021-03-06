//-----------------------------------------------------
// FILE: AirUnit.h
//-----------------------------------------------------

#ifndef _AIR_UNIT_H_
#define _AIR_UNIT_H_


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "GameAgent.h"


//-----------------------------------------------------
// AIR UNIT CLASS - CHILD OF GAME AGENT
//-----------------------------------------------------
class CAirUnit : public CGameAgent
{
protected:
	// DATA
	//---------------------------
	float mYaw = 0.0f;

public:
	// CONSTRUCTORS & DESTRUCTOR
	//---------------------------
	CAirUnit();
	virtual ~CAirUnit();


	// OVERRIDE METHODS
	//---------------------------
	virtual bool Attack(CGameObject* target, float hitMod, float damageMod) = 0;
	//virtual void MoveTo(CTile* dest);
	virtual void Move();
	virtual bool Update();
	bool LookingAt(DX::XMFLOAT3 targetPosition);
	virtual void UnloadIModel() = 0;
	virtual void LoadIModel() = 0;

	void LoadModel(float x, float y, float z)
	{

	}

	virtual void SetTargetTexture()
	{

	}

	virtual void SetNormalTexture()
	{

	}

	void Spawn(CGrid* pGrid, SPointData pCentre);
	void DetermineAirspace();


private:
	virtual IModel* CreateModel(DX::XMFLOAT3 pos) = 0;
};

#endif /* _AIR_UNIT_H_ */
