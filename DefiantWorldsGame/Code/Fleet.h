
//-----------------------------------------------------
// FILE: Fleet.h
//-----------------------------------------------------
#pragma once
//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "Common.h"
#include "SpaceUnit.h"
#include "Randomiser.h"
#include <map>
//-----------------------------------------------------
// FLEET CLASS
//-----------------------------------------------------
class CRTSPlayer;
enum Tactics {None, Targeted, Rapid};
class CFleet
{
private:
	// DATA
	vector <CGameAgent*> mpFleet;//contains the ships that are being sent to attack
	CFleet* mpEnemyFleet;
	int mSize;
	int mNumSpaceFighter;
	int mNumMothership;
	int mNumTransport;
	int mUnitsLostValue;

	// PARTICLES
	std::map<CExplosion*, float> M_Explosions;
	std::map<CExplosion*, float>::iterator mpParticleIt;
	const float mExplosionTime;
	const float mExplosionNumParticle;

	CRTSPlayer* mpPlayer;

	// FLEET SHIP MODIFIERS
	//---------------------------
	float mDamegMod;//modifys the ships damage acording to the chosen tactics
	float mHitMod;//modifys the ships hit chance according to the choosen tactics

	// FLEET STATUS VALUES
	float mFleetCurrentHealth;
	float mFleetMaxHealth;

	// TACTICS
	//---------------------------
	Tactics mFleetTactics;
	int mTargetedFireVariance;
	CRandomiser* mTarget;
	//used for track fleet accuracy, only used for output in spcae state
	int mHits;
	int mShotsFired;
	int mFleetSectionFiring;
	const int mNumFleetSections;
	float mSpecialAttackCooldownTimer;
	const float mSpecialAttackCooldownTime;
	const float mSpecialAttackCost;

	// POSITIONING
	//---------------------------
	const int mFleetRowSize;//maximum size of a row of ships
	const int mFleetRowSeperation;//distance between each row of ships
	const int mFleetZAdjust;//used to adjust the z depth of the fleet ships, gives depth to the fleet
	const float mFleetYCyleHeight;
	float mFleetYAdjust;//used to bring the fleet up and centralize them
	float mFleetYHeighCycle;//used bu the fleet idle function to change the y height
	int mFleetWidth;//number of ships that can be in a row. specifcally, the number of ships beyond the centre ship in a given direction
	int YSwitch(int x);


	// SCENE
	//---------------------------
	const float mSceneStartX;
	const float mSceneDuration;
	float mSceneTimeElapsed;
	void SetShipPositions();

	// SOUND
	//---------------------------
	CSound* mGenSound;

public:
	// CONSTRUCTORS & DESTRUCTOR
	//---------------------------
	CFleet();
	~CFleet();

	// METHODS
	//---------------------------
	void UpdateCondition();//gets rid of dead ships and checks to see if the fleet has been defeated
	void Fight();//attacks another fleet
	void LoadShipModels(float xPos);
	void UnloadShieldModels();
	void UnloadLazers(); 
	void MoveFleet();
	void IdleFleet();//makes the shapes move slightly, to make the sceene more animated
	void ChargeFleetLazers();//used to slow down space lazer firing
	//scene functions
	void SetShipPositions(float xPos);
	//special attacks, used by the fleet
	bool SpecialAttackLazerBarrage(CRTSPlayer* player);
	bool SpecialAttackMassHeal(CRTSPlayer* player);

	//particle effects
	//deletes the explosions and clears the explosion list
	inline void CleanUpExplosions()
	{
		for (auto x : M_Explosions)
		{
			mpParticleIt = M_Explosions.find(x.first);
			delete x.first;
		}
		M_Explosions.clear();
	}

	void UpdateExplosions();

	//transistion scenes
	bool SceneSpaceFight();

	// ACCESSORS
	//---------------------------
	CGameAgent*GetShip(int i);//returns ship at the choosen postion
	int GetSize();//returns the size of the fleet
	int GetRows();//returns the number of rows of ships
	string GetTacticsName();

	float GetFleetTotalHealth();
	float GetFleetAvargeHealth();
	float GetFleetMaxHealth();
	inline int GetShotsFired()
	{
		return mShotsFired;
	}
	inline int GetHits()
	{
		return mHits;
	}
	inline float GetHitPercentage()
	{
		if (mShotsFired!=0) return ((float)mHits / (float)mShotsFired)*100.0f;
		else return 0;
	}
	inline float GetCooldownTimer()
	{
		return mSpecialAttackCooldownTimer;
	}



	// MUTATORS
	//---------------------------
	void SetEnemy(CFleet* myEnemy);//sets the fleet that this one will attack
	vector <CGameAgent*>* LaunchFleet(vector <CGameAgent*>* possibleShips);//gets ships a player has, then adds a number of them to the fleet to attack
	void ReturnFleet(CRTSPlayer* Player,bool victory);
	void SetTactic(Tactics tactics);
	bool ManFleet(CGameAgent* UnitToLoad);
};

