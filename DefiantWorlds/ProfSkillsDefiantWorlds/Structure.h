//-----------------------------------------------------
// FILE: Structure.h
//-----------------------------------------------------

#ifndef _STRUCTURE_H_
#define _STRUCTURE_H_


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "GameObject.h"
#include "Grid.h"


//-----------------------------------------------------
// STRUCTURE CLASS - CHILD OF GAME OBJECT
//-----------------------------------------------------
class CStructure : public CGameObject
{
protected:
	// DATA
	//---------------------------
	float mHealth;
	float mBuildTime;
	float mRepairSpeed;
	float mCurBuildTimeLeft;			// Time left until structure is built
	int   mBuildCost;
	//CParticleEmitter* mDestroyParticleFX;
	EObjectStates mState;

	SPointData mStructureBL;		// Amount of grid squares relative to the centre to find the bottom left grid square
	SPointData mStructureTR;		// Same as above, but for top right grid square


public:
	// CONSTRUCTORS & DESTRUCTOR
	//---------------------------
	CStructure();
	virtual ~CStructure();


	// ACCESSORS
	//---------------------------
	inline float GetHealth()
	{
		return mHealth;
	}

	inline float GetBuildTime()
	{
		return mBuildTime;
	}

	inline float GetRepairSpeed()
	{
		return mRepairSpeed;
	}

	inline float GetBuildTimeLeft()
	{
		return mCurBuildTimeLeft;
	}

	inline int GetBuildCost()
	{
		return mBuildCost;
	}

	inline EObjectStates GetState()
	{
		return mState;
	}

	inline SPointData GetBLPosition()
	{
		return mStructureBL;
	}

	inline SPointData GetTRPosition()
	{
		return mStructureTR;
	}


	// MUTATORS
	//---------------------------
	bool TakeDamage(float amount);
	bool Repair(float amount);


	// METHODS
	//---------------------------
	void CreateStructure(CGrid* pGrid);
	bool TestStructureArea(CGrid* pGrid, CTile* pTile);
	bool Build();


	// VIRTUAL METHODS
	//---------------------------
	virtual void UnloadIModel() = 0;
	virtual bool Destroy() = 0;
};

#endif /* _STRUCTURE_H_ */
