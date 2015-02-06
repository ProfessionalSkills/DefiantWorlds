//-----------------------------------------------------
// FILE: ProductionStructure.h
//-----------------------------------------------------

#ifndef _PRODUCTION_STRUCTURE_H_
#define _PRODUCTION_STRUCTURE_H_


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "Structure.h"


//-----------------------------------------------------
// CONSTANTS
//-----------------------------------------------------
const int MAX_QUEUE_SIZE = 5;


//-----------------------------------------------------
// PRODUCTION STRUCTURE CLASS - CHILD OF STRUCTURE
//-----------------------------------------------------
class CProductionStructure : public CStructure
{
private:
	// DATA
	//---------------------------
	std::list<EGameAgentsList> mRespectiveAgentsList;
	//std::queue<CGameAgents*> mpProductionQueue;


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
	//bool AddToQueue(CGameAgent* agent);
	bool RemoveFromQueue();
	bool UpdateProduction(float delta);
	//CGameAgent* CreateAgent();		// Called when agent at front of production queue is finished



	// OVERRIDE METHODS
	//---------------------------
private:
	virtual bool Destroy();
};

#endif /* _PRODUCTION_STRUCTURE_H_ */
