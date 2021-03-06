//-----------------------------------------------------
// FILE: Randomiser.cpp
//-----------------------------------------------------


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "Randomiser.h"


//-----------------------------------------------------
// RANDOMISER CLASS CONSTRUCTORS & DESTRUCTOR
//-----------------------------------------------------
CRandomiser::CRandomiser()
{
	// Create seed
	unsigned long seed = static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count());
	mGenerator.seed(seed);
}

CRandomiser::~CRandomiser()
{

}


//-----------------------------------------------------
// RANDOMISER CLASS METHODS
//-----------------------------------------------------
void CRandomiser::SetSeed(float seed1, float seed2)
{
	mGenerator.seed(seed1 * seed2);
}

int CRandomiser::GetRandomInt(int inMin, int inMax)
{
	// Create distribution
	std::uniform_int_distribution<int> distribution(inMin, inMax);

	// Generate
	return distribution(mGenerator);
}

float CRandomiser::GetRandomFloat(double inMin, double inMax)
{
	// Create distribution
	std::uniform_real_distribution<double> distribution(inMin, inMax);

	// Generate
	return static_cast<float>(distribution(mGenerator));
}
