#include "DataLoader.h"

DataLoader::DataLoader(const string& dataFile)
{
	loadData(dataFile);
}

void DataLoader::loadData(const string& dataFile)
{
	ifstream file(dataFile);

	while (!file.eof())
	{
		//Game Data
		file >> mGameSpeed;

		//Display Data
		file >> mDisplayWidth;
		file >> mDisplayHeight;
		file >> mPlayZoneLow;
		file >> mPlayZoneHigh;

		//File Data
		file >> mLevelsPath;
		file >> mAssetPath;

		file >> mBackgroundFile;
		file >> mPlayerFile;
		file >> mWallFile;
		file >> mEnemyFile;
		file >> mTumbleweedFile;
		file >> mBulletFile;
		file >> mFontFile;
		file >> mPowerupFile;

		//Sprite Data
		file >> mSpriteRows;
		file >> mSpriteColumns;
		file >> mSpriteCutX;
		file >> mSpriteCutY;
		file >> mTumbleweedRows;
		file >> mTumbleweedColumns;

		//Tumbleweed Data
		file >> mTumbleSpeed;
		file >> mTumbleSpawnRate;

		//Shooting Data
		file >> mNormalBulletDelay;
		mBulletDelay = mNormalBulletDelay;

		file >> mBulletSpeed;
		file >> mBulletRows;
		file >> mBulletColumns;
		file >> mBulletCutX;
		file >> mBulletCutY;

		//Player Data
		file >> mPlayerHealth;
		file >> mPlayerMoveSpeed;
		file >> mPlayerDamage;
		file >> mActivePowerupTimer;

		//Enemy Data
		file >> mNormalEnemyHealth;
		mEnemyHealth = mNormalEnemyHealth;
		file >> mNormalEnemyShotDelay;
		mEnemyShotDelay = mNormalEnemyShotDelay;
		file >> mNormalEnemyMoveSpeed;
		mEnemyMoveSpeed = mNormalEnemyMoveSpeed;

		//Powerup Data
		file >> mPowerupTimer;
		file >> mPowerupBootsSpeed;
		file >> mLargeBulletDamage;
		file >> mFastBulletDelay;

		//Score Data
		file >> mTumbleweedScore;
		file >> mEnemyShotScore;
		file >> mEnemyKilledScore;

		//Language Data
		file >> mLanguagePath;
		file >> mEnglishFile;
		file >> mSpanishoFile;
		file >> mTLangFile;

		//Audio Data
		file >> mAudioPath;
		file >> mShotSoundFile;

		//Level Data
		file >> mFirstLevel;
	}
}
