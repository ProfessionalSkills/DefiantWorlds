//-----------------------------------------------------
// FILE: Tank.h
//-----------------------------------------------------

#ifndef _TANK_H_
#define _TANK_H_


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "GroundUnit.h"


//-----------------------------------------------------
// TANK CLASS - CHILD OF GROUND UNIT
//-----------------------------------------------------
class CTank : public CGroundUnit
{
private:
	// DATA
	//---------------------------


public:
	// CONSTRUCTORS & DESTRUCTOR
	//---------------------------
	CTank();
	virtual ~CTank();


	// ACCESSORS
	//---------------------------



	// MUTATORS
	//---------------------------



	// METHODS
	//---------------------------


	// OVERRIDE METHODS
	//---------------------------
	virtual bool Attack(CGameAgent* target);
	//virtual void MoveTo(CTile* dest);
	virtual bool Move(float delta);

private:
	virtual bool Destroy();
};

#endif /* _TANK_H_ */