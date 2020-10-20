#pragma once
#include "Unit.h"

class Powerup : public Unit
{
public:
	enum PowerupType
	{
		BOOTS,
		BODY_ARMOR,
		LARGE_BULLETS,
		GUN,
		EXTRA_LIFE,
		NUM_POWERUPS //total number of powerups, but also used if no powerup is active
	};

	Powerup(PowerupType type);

	void shot() override {}; //powerup doesn't need to do anything when shot
	void setPowerupTypeByInt(int type) { mPowerupType = (PowerupType)type; };
	PowerupType getPowerupType() { return mPowerupType; };
	vector<Animation*> createAnimation();

private:
	PowerupType mPowerupType;
};
