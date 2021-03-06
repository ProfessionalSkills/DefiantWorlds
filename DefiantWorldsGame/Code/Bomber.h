//-----------------------------------------------------
// FILE: Bomber.h
//-----------------------------------------------------

#ifndef _BOMBER_H_
#define _BOMBER_H_


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "AirUnit.h"


//-----------------------------------------------------
// BOMBER CLASS - CHILD OF AIR UNIT
//-----------------------------------------------------
class CBomber : public CAirUnit
{
private:
	// DATA
	//---------------------------


public:
	static IMesh* mspMshBomber;
	static IMesh* mspMshBomb;
	static ALuint alAttackSound;
	static ALuint alAttackSource;

	// CONSTRUCTORS & DESTRUCTOR
	//---------------------------
	CBomber();
	virtual ~CBomber();


	// ACCESSORS
	//---------------------------



	// MUTATORS
	//---------------------------



	// METHODS
	//---------------------------
	void UnloadIModel();
	void LoadIModel();


	// OVERRIDE METHODS
	//---------------------------
	bool Attack(CGameObject* pTarget, float hitMod, float damageMod);
	bool Update();

	void SetTargetTexture();
	void SetNormalTexture();


private:
	IModel* CreateModel(DX::XMFLOAT3 pos) override;
};

#endif /* _BOMBER_H_ */
