//-----------------------------------------------------
// FILE: SettingsManager.h
//-----------------------------------------------------

#ifndef _SETTINGS_MANAGER_H_
#define _SETTINGS_MANAGER_H_

#include <fstream>


class CSettingsManager
{
public:
	// CONSTRUCTORS & DESTRUCTOR
	//---------------------------
	CSettingsManager();
	~CSettingsManager();


	// ACCESSORS
	//---------------------------
	inline float GetMusicVolume()
	{
		return mMusicVolume;
	}

	inline float GetEffectsVolume()
	{
		return mEffectsVolume;
	}

	inline int GetAIDifficulty()
	{
		return mAIDifficulty;
	}

	inline int GetStartingResourcesIndex()
	{
		return mStartingResources;
	}

	inline bool IsGameBeingLoaded()
	{
		return mLoadingGame;
	}

	inline void GetLoadFileName(std::string& loadFileName)
	{
		loadFileName = mLoadFileName;
	}

	inline int GetMineralDepositsIndex()
	{
		return mMineralDeposits;
	}

	inline int GetMineralDepositsValue()
	{
		return mMineralDepositsList[mMineralDeposits];
	}

	int GetStartingResourcesAmount();


	// MUTATORS
	//---------------------------
	inline void SetMusicVolume(float newVolume)
	{
		mMusicVolume = newVolume;
	}

	inline void SetEffectsVolume(float newVolume)
	{
		mEffectsVolume = newVolume;
	}

	inline void SetAIDifficulty(int difficulty)
	{
		mAIDifficulty = difficulty;
	}

	inline void SetStartingResources(int amount)
	{
		mStartingResources = amount;
	}

	inline void SetIfLoadingGame(bool loading)
	{
		mLoadingGame = loading;
	}

	inline void SetLoadFile(std::string& loadFileName)
	{
		mLoadFileName = loadFileName;
	}

	inline void SetMineralDepositsIndex(int index)
	{
		mMineralDeposits = index;
	}


	// METHODS
	//---------------------------
	void SaveSettings(std::ofstream& outFile);
	void LoadSettings(std::ifstream& inFile);


private:
	// SETTINGS DATA
	//---------------------------
	bool mLoadingGame = false;				// Used to identify whether or not the player is loading a game from file
	std::string mLoadFileName = "";

	float mMusicVolume = 0.8f;
	float mEffectsVolume = 0.6f;

	int mAIDifficulty = 1;
	int mStartingResources = 1;
	int mMineralDeposits = 1;				// The index of the chosen amount of mineral depositis to spawn
	int mMineralDepositsList[3];			// The selectable values of the mineral deposits
};


#endif /* _SETTINGS_MANAGER_H_ */
