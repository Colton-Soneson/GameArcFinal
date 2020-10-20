#pragma once
#include "Powerup.h"

class PowerupManager : public Trackable
{
public:
	PowerupManager();
	~PowerupManager();

	void update(double gameSpeed);
	void draw() { if (mCurrentPowerup != nullptr && mSpawnPowerups) { mCurrentPowerup->drawUnit(); } };

	void randomizePowerup(); //randomly will create a Powerup
	void placePowerup(); //randomly place a Powerup
	bool checkForFreeArea(Vector2D location); //find a free area to place a Powerup

	void togglePowerupSpawn() { mSpawnPowerups = !mSpawnPowerups; };
	void setPowerupSpawn(bool active) { mSpawnPowerups = active; };
	bool getSpawnPowerups() { return mSpawnPowerups; }; //whether or not powerups should spawn

	Powerup* getPowerup() { return mCurrentPowerup; };
	bool powerupPresent(); //returns true if there is a Powerup placed
	void removePowerup(); //remove the powerup when collided with
private:
	Powerup* mCurrentPowerup;

	double mTargetTime; //what mTimeUntilNextPlacement gets reset to
	double mTimeUntilNextPlacement; //how long until another powerup is spawned

	bool mSpawnPowerups = true;
	//bool mPowerupPlaced = false;
};
