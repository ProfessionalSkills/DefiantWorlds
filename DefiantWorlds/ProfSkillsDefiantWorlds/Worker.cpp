//-----------------------------------------------------
// FILE: Worker.cpp
//-----------------------------------------------------


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "Worker.h"


//-----------------------------------------------------
// WORKER CLASS CONSTRUCTORS & DESTRUCTOR
//-----------------------------------------------------
CWorker::CWorker()
{

}

CWorker::~CWorker()
{

}


//-----------------------------------------------------
// WORKER CLASS METHODS
//-----------------------------------------------------
//bool RepairBuilding(CStructure* structure)

//bool CollectResources(CResources* resource)

bool RepairUnit(CGroundUnit* unit)
{
	return false;
}


//-----------------------------------------------------
// WORKER CLASS OVERRIDE METHODS
//-----------------------------------------------------
bool CWorker::Attack(CGameAgent* target)
{
	return false;
}

//CWorker::void MoveTo(CTile* dest)


bool CWorker::Move(float delta)
{
	return false;
}

bool CWorker::Destroy()
{
	return false;
}