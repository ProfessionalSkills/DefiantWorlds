//-----------------------------------------------------
// FILE: SpaceUnit.cpp
//-----------------------------------------------------


//-----------------------------------------------------
// INCLUDES
//-----------------------------------------------------
#include "SpaceUnit.h"
IMesh* CSpaceUnit::mspMshLazer = nullptr;

//-----------------------------------------------------
// SPACE UNIT CLASS CONSTRUCTORS & DESTRUCTOR
//-----------------------------------------------------
CSpaceUnit::CSpaceUnit() :mChargeTimeMax(3.0f), mChargeTimeMin(1.0f)
{
	mSpeed = 5.0f;
	mpTempShield = nullptr;
	mpTempLazer = nullptr;
	mCargoValue = 0;
	mOrientation = 180.0f;
	mpToHitRoll = new CRandomiser();
	mChargingLazers = true;
	mCharged = false;
	mChargeTime = mChargeTimeMax;
	mFiredLazer = false;
	mGenSound = nullptr;
	mSoundFileLazer = "shoot.wav";
	mSoundFileExplosion = "Spaceship_Explosion";
	mSoundExplosion = nullptr;
	mGenSound = nullptr;
}

CSpaceUnit::~CSpaceUnit()
{
	SafeDelete(mpToHitRoll);
	if (mpTempLazer)
	{
		mpTempLazer->GetMesh()->RemoveModel(mpTempLazer);
		mpTempLazer = nullptr;
	}
	if (mpTempShield)
	{
		mpTempShield->GetMesh()->RemoveModel(mpTempShield);
		mpTempShield = nullptr;
	}
}

//-----------------------------------------------------
// SPACE UNIT CLASS ACCESSOR METHODS
//-----------------------------------------------------


//-----------------------------------------------------
// SPACE UNIT CLASS OVERRIDE METHODS
//-----------------------------------------------------
bool CSpaceUnit::Attack(CGameObject* target, float hitMod, float damageMod)
{
	return false;
}

void CSpaceUnit::Spawn(CGrid* pGrid, SPointData pCentre)
{

}

void CSpaceUnit::Move()
{
	mpObjModel->MoveZ(mSpeed*gFrameTime);
	mWorldPos.z += mSpeed*gFrameTime;
}

void CSpaceUnit::UnloadIModel()
{

}

void CSpaceUnit::LoadIModel()
{

}

void CSpaceUnit::LoadModel(float x, float y, float z)
{

}

bool CSpaceUnit::Update()
{
	return true;
}

float Sq(float x)
{
	return x*x;
}

void CSpaceUnit::FireLazer(CGameObject* target)
{
	//set models position
	DirectX::XMFLOAT4X4 ModelMatrix;
	DirectX::XMFLOAT3 ModelZNormal;

	mpObjModel->GetMatrix(&ModelMatrix.m[0][0]);

	ModelZNormal.x = ModelMatrix.m[2][0] * 6;
	ModelZNormal.y = ModelMatrix.m[2][1] * 6;
	ModelZNormal.z = ModelMatrix.m[2][2] * 6;
	if (mGenSound) mGenSound->PlaySound();

	if (!mpTempLazer)
	{
		mpTempLazer = mspMshLazer->CreateModel(mWorldPos.x + ModelZNormal.x, mWorldPos.y + ModelZNormal.y, mWorldPos.z + ModelZNormal.z);
		if (mWorldPos.x > 0)
		{
			mpTempLazer->SetSkin("tlxadd_lazer - red.tga");
		}
	}
	else
	{
		mpTempLazer->SetPosition(mWorldPos.x + ModelZNormal.x, mWorldPos.y + ModelZNormal.y, mWorldPos.z + ModelZNormal.z);
	}

	mpTempLazer->LookAt(target->GetWorldPos().x, target->GetWorldPos().y, target->GetWorldPos().z);
	float length = sqrtf(Sq(target->GetWorldPos().x - mWorldPos.x) + Sq(target->GetWorldPos().y - mWorldPos.y) + Sq(target->GetWorldPos().z - mWorldPos.z));

	mpTempLazer->ScaleZ(length);
	mpTempLazer->ScaleX(0.2f);
	mpTempLazer->ScaleY(0.2f);
	mChargingLazers = true;
	mFiredLazer = true;
	mCharged = false;
}

void CSpaceUnit::ChargeLazer()
{
	//set models position
	DirectX::XMFLOAT4X4 ModelMatrix;
	DirectX::XMFLOAT3 ModelZNormal;

	mpObjModel->GetMatrix(&ModelMatrix.m[0][0]);

	ModelZNormal.x = ModelMatrix.m[2][0] * 6;
	ModelZNormal.y = ModelMatrix.m[2][1] * 6;
	ModelZNormal.z = ModelMatrix.m[2][2] * 6;

	if (!mpTempLazer)
	{
		mpTempLazer = mspMshLazer->CreateModel(mWorldPos.x + ModelZNormal.x, mWorldPos.y + ModelZNormal.y, mWorldPos.z + ModelZNormal.z);
		if (mWorldPos.x > 0)
		{
			mpTempLazer->SetSkin("tlxadd_lazer - red.tga");
		}
	}
	else
	{
		mpTempLazer->SetPosition(mWorldPos.x + ModelZNormal.x, mWorldPos.y + ModelZNormal.y, mWorldPos.z + ModelZNormal.z);
	}

	if (mChargeTime <= 0&&!mCharged)
	{
		mChargeTime = mChargeTimeMax;
		mChargingLazers = false;
		mCharged = true;
	}
	else if (!mCharged)
	{
		mChargeTime -= gFrameTime;
	}
	
}

void CSpaceUnit::UnloadLazer()
{
	if (mpTempLazer&&mFiredLazer)
	{
		DX::XMFLOAT4X4 tmp;
		mpTempLazer->ResetScale();
		mpTempLazer->GetMatrix(&tmp.m[0][0]);
		mpTempLazer->SetY(-5000);
		mFiredLazer = false;
	}
	else if (mpTempLazer&&!mCharged)
	{
		mpTempLazer->ResetScale();
		mpTempLazer->Scale(1 / (mChargeTime + 1.0f));
	}
}

void CSpaceUnit::SaveAgent(std::ofstream& outFile)
{
	// Save the data for this unit
	outFile << mAgentInfo.mAgentType << " " << mFaction << " " << mState << " " << mHealth << std::endl;
}

void CSpaceUnit::LoadAgent(std::ifstream& inFile)
{
	// Load in the data required and store the data
	int faction;
	int state;
	inFile >> faction >> state >> mHealth;

	mFaction = static_cast<EFactions>(faction);
	mState = static_cast<EObjectStates>(state);
}
