//-----------------------------------------------------
// FILE: Worker.h
//-----------------------------------------------------

#ifndef _WORKER_H_
#define _WORKER_H_


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "GroundUnit.h"
#include "Minerals.h"


//-----------------------------------------------------
// WORKER CLASS - CHILD OF GROUND UNIT
//-----------------------------------------------------
class CWorker : public CGroundUnit
{
private:
	// DATA
	//---------------------------
	bool mHarvesting = false;
	CMinerals* mpActiveMineral = nullptr;			// Stores a pointer to the mineral which is being harvested by this worker unit
	IModel* mpMdlHarvest = nullptr;


public:
	static IMesh* mspMshWorker;
	static IMesh* mspMshWorkerLaser;

	// CONSTRUCTORS & DESTRUCTOR
	//---------------------------
	CWorker();
	virtual ~CWorker();


	// ACCESSORS
	//---------------------------
	inline CMinerals* GetMineral()
	{
		return mpActiveMineral;
	}


	// MUTATORS
	//---------------------------
	inline void SetMineral(CMinerals* pMineral)
	{
		// If there was an active mineral before
		if (mpActiveMineral)
		{
			// Set its usage to false
			mpActiveMineral->SetUsage(false);
		}

		mpActiveMineral = pMineral;
		mHarvesting = false;
	}


	// METHODS
	//---------------------------
	//bool RepairBuilding(CStructure* structure);
	bool IsHarvestingMineral();
	bool RepairUnit(CGroundUnit* unit);
	void UnloadIModel();
	void LoadIModel();


	// OVERRIDE METHODS
	//---------------------------
	virtual bool Attack(CGameObject* pTarget, float hitMod, float damageMod);
	void SetTargetTexture();
	void SetNormalTexture();
	bool Update();


private:
	virtual bool Destroy();
	IModel* CreateModel(DX::XMFLOAT3 pos) override;
};

#endif /* _WORKER_H_ */
