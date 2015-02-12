//-----------------------------------------------------
// FILE: ProductionStructure.h
//-----------------------------------------------------

#ifndef _PRODUCTION_STRUCTURE_H_
#define _PRODUCTION_STRUCTURE_H_


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "Structure.h"
#include "GameAgent.h"


//-----------------------------------------------------
// CONSTANTS
//-----------------------------------------------------
const int MAX_QUEUE_SIZE = 5;


//-----------------------------------------------------
// PRODUCTION STRUCTURE CLASS - CHILD OF STRUCTURE
//-----------------------------------------------------
class CProductionStructure : public CStructure
{
protected:
	// DATA
	//---------------------------
	std::list<EGameAgentsTypes> mRespectiveAgentsList;
	std::queue<CGameAgent*> mpProductionQueue;


public:
	// CONSTRUCTORS & DESTRUCTOR
	//---------------------------
	CProductionStructure();
	virtual ~CProductionStructure();


	// ACCESSORS
	//---------------------------



	// MUTATORS
	//---------------------------



	// METHODS
	//---------------------------
	bool AddToQueue(CGameAgent* agent);
	bool RemoveFromQueue();
	bool UpdateProduction();
	CGameAgent* CreateAgent();		// Called when agent at front of production queue is finished

	void Update() override;
	void DisplayInfo(IFont* font) override;


	// OVERRIDE METHODS
	//---------------------------
	virtual void SetBuiltModel();
	virtual void UnloadIModel();
	virtual bool Destroy();
};

#endif /* _PRODUCTION_STRUCTURE_H_ */
