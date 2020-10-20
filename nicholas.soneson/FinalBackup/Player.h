#pragma once
#include "Unit.h"
#include "Directions.h"
#include "Powerup.h"

class Player : public Unit
{
public:
	Player(Vector2D location, vector<Animation*> animList);

	void updatePlayer(double gameSpeed);
	void handlePowerup(); //applies the effects of the powerup
	void movePlayer(Direction direction); //move the player
	void checkIfInPlayZone(); //check that player is still in the play zone (and move them back if they aren't)
	void checkCollision(BoundedZone* objZone); //check collision with walls
	void checkPowerupCollision(); //check for collision with powerups

	Powerup::PowerupType getActivePowerupType() { return mActivePowerup; };
	void setActivePowerupTypeByInt(int type) { mActivePowerup = (Powerup::PowerupType)type; };
	int getHealth() { return mHealth; };
	int getPlayerDamage() { return mPlayerDamage; };
	bool getBodyArmor() { return mBodyArmor; };

	void shot() override; //handle Player being shot
private:
	int mMoveSpeed;
	int mStartingMoveSpeed;
	int mTmpMoveSpeed;

	int mHealth;
	Powerup::PowerupType mActivePowerup;

	double mPowerupTimer;
	double mTargetTime;

	bool mBodyArmor = false;
	int mPlayerDamage; //how much damage Player's shots deal to enemies
};
