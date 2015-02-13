//-----------------------------------------------------
// FILE: SpaceUnit.h
//-----------------------------------------------------

#ifndef _SPACE_UNIT_H_
#define _SPACE_UNIT_H_


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "GameAgent.h"
#include "Randomiser.h"


//-----------------------------------------------------
// SPACE UNIT CLASS - CHILD OF GAME AGENT
//-----------------------------------------------------
class CSpaceUnit : public CGameAgent
{
private:
	// DATA
	//---------------------------
	float mHitChance;

public:
	// CONSTRUCTORS & DESTRUCTOR
	//---------------------------
	CSpaceUnit();
	virtual ~CSpaceUnit();


	// ACCESSORS
	//---------------------------
	


	// MUTATORS
	//---------------------------
	


	// METHODS
	//---------------------------
	

	// OVERRIDE METHODS
	//---------------------------
	virtual bool Attack(CGameAgent* target,float hitMod, float damageMod);
	//virtual void MoveTo(CTile* dest);
	virtual bool Move();

private:
	virtual bool Destroy();
};

#endif /* _SPACE_UNIT_H_ */
