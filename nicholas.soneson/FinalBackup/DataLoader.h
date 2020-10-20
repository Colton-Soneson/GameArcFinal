#pragma once
#include <string>
#include <fstream>

using namespace std;

class DataLoader
{
public:
	DataLoader(const string& dataFile);
	~DataLoader() {};

	void loadData(const string& dataFile); //load the data form the given file

	//Game Data
	double getGameSpeed() { return mGameSpeed; };

	//Display Data
	int getDisplayWidth() { return mDisplayWidth; };
	int getDisplayHeight() { return mDisplayHeight; };
	int getPlayZoneLow() { return mPlayZoneLow; };
	int getPlayZoneHigh() { return mPlayZoneHigh; };

	//File Data
	string getLevelsPath() { return mLevelsPath; };
	string getAssetPath() { return mAssetPath; };

	string getBackgroundFile() { return mBackgroundFile; };
	string getPlayerFile() { return mPlayerFile; };
	string getWallFile() { return mWallFile; };
	string getEnemyFile() { return mEnemyFile; };
	string getTumbleweedFile() { return mTumbleweedFile; };
	string getBulletFile() { return mBulletFile; };
	string getFontFile() { return mFontFile; };
	string getPowerupFile() { return mPowerupFile; };

	//Sprite Data
	int getSpriteRows() { return mSpriteRows; };
	int getSpriteColumns() { return mSpriteColumns; };
	int getSpriteCutX() { return mSpriteCutX; };
	int getSpriteCutY() { return mSpriteCutY; };
	int getTumbleSpriteRows() { return mTumbleweedRows; };
	int getTumbleSpriteColumns() { return mTumbleweedColumns; };

	//Tumbleweed Data
	float getTumbleSpeed() { return mTumbleSpeed; };
	float getTumbleSpawnRate() { return mTumbleSpawnRate; };

	//Shooting Data
	void setBulletDelay(float delay) { mBulletDelay = delay; };

	float getNormalBulletDelay() { return mNormalBulletDelay; };
	float getBulletDelay() { return mBulletDelay; };
	float getBulletSpeed() { return mBulletSpeed; };
	int getBulletRows() { return mBulletRows; };
	int getBulletColumns() { return mBulletColumns; };
	int getBulletCutX() { return mBulletCutX; };
	int getBulletCutY() { return mBulletCutY; };

	//Player Data
	int getPlayerHealth() { return mPlayerHealth; };
	int getPlayerMoveSpeed() { return mPlayerMoveSpeed; };
	int getPlayerDamage() { return mPlayerDamage; };
	double getActivePowerupTimer() { return mActivePowerupTimer; };

	//Enemy Data
	int getEnemyHealth() { return mEnemyHealth; };
	int getNormalEnemyHealth() { return mNormalEnemyHealth; };
	double getEnemyShotDelay() { return mEnemyShotDelay; };
	double getNormalEnemyShotDelay() { return mNormalEnemyShotDelay; };
	int getEnemyMoveSpeed() { return mEnemyMoveSpeed; };
	int getNormalEnemyMoveSpeed() { return mNormalEnemyMoveSpeed; };
	void setEnemyHealth(int health) { mEnemyHealth = health; };
	void setEnemyShotDelay(double delay) { mEnemyShotDelay = delay; };
	void setEnemyMoveSpeed(int speed) { mEnemyMoveSpeed = speed; };

	//Powerup Data
	double getPowerupTimer() { return mPowerupTimer; };
	int getBootsMoveSpeed() { return mPowerupBootsSpeed; };
	int getLargeBulletDamage() { return mLargeBulletDamage; };
	float getFastBulletDelay() { return mFastBulletDelay; };

	//Score Data
	int getTumbleweedScore() { return mTumbleweedScore; };
	int getEnemyShotScore() { return mEnemyShotScore; };
	int getEnemyKilledScore() { return mEnemyKilledScore; };

private:
	//Game Data
	double mGameSpeed;

	//Display Data
	int mDisplayWidth;
	int mDisplayHeight;
	int mPlayZoneLow;
	int mPlayZoneHigh;

	//File Data
	string mLevelsPath;
	string mAssetPath;

	string mBackgroundFile;
	string mPlayerFile;
	string mWallFile;
	string mEnemyFile;
	string mTumbleweedFile;
	string mBulletFile;
	string mFontFile;
	string mPowerupFile;

	//Sprite Data
	int mSpriteRows;
	int mSpriteColumns;
	int mSpriteCutX;
	int mSpriteCutY;
	int mTumbleweedRows;
	int mTumbleweedColumns;

	//Tumbleweed Data
	float mTumbleSpeed;
	float mTumbleSpawnRate;

	//Shooting Data
	float mNormalBulletDelay;
	float mBulletDelay;
	float mBulletSpeed;
	int mBulletRows;
	int mBulletColumns;
	int mBulletCutX;
	int mBulletCutY;

	//Player Data
	int mPlayerHealth;
	int mPlayerMoveSpeed;
	int mPlayerDamage;
	double mActivePowerupTimer;

	//Enemy Data ("Normal" is for resetting if user toggles difficulty back to Easy)
	int mEnemyHealth;
	int mNormalEnemyHealth;
	double mEnemyShotDelay;
	double mNormalEnemyShotDelay;
	int mNormalEnemyMoveSpeed;
	int mEnemyMoveSpeed;

	//Powerup Data
	double mPowerupTimer;
	int mPowerupBootsSpeed;
	int mLargeBulletDamage;
	float mFastBulletDelay;

	//Score Data
	int mTumbleweedScore;
	int mEnemyShotScore;
	int mEnemyKilledScore;
};
