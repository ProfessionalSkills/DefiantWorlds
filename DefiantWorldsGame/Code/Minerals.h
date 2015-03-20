//-----------------------------------------------------
// FILE: Minerals.h
//-----------------------------------------------------

#ifndef _MINERALS_H_
#define _MINERALS_H_


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "GameObject.h"


//-----------------------------------------------------
// MINERALS CLASS - CHILD OF GAME OBJECT
//-----------------------------------------------------
class CMinerals : public CGameObject
{
private:
	// DATA
	//---------------------------
	int mAmount;


public:
	static IMesh* mspMshMineral;


	// CONSTRUCTORS & DESTRUCTOR
	//---------------------------
	CMinerals();
	virtual ~CMinerals();


	// ACCESSORS
	//---------------------------
	inline int GetResourceAmount()
	{
		return mAmount;
	}


	// MUTATORS
	//---------------------------


	// METHODS
	//---------------------------
	void CreateResource(DX::XMFLOAT3 pos);
	void LoadIModel();
	void UnloadIModel();
};

#endif /* _MINERALS_H_ */
