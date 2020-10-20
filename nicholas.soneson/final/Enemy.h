#pragma once

#include "Unit.h"

class Enemy : public Unit
{
public:
	Enemy(Vector2D location, int spriteCutX, int spriteCutY);
	
	vector<Animation*> createAnimation();
	
	Vector2D getGameEntityLocation() { return mGameEntityLocation; };
	int getCutX() { return mCutX; };
	int getCutY() { return mCutY; };

	int getHealth() { return mHealth; };
	void setHealth(int health) { mHealth = health; };

	void shot() override; //subtract health if shot (hit by a Bullet)

	void shootingHandler(EightDirectional direction);

	void adjustMovementPosition(int movePace);

	void toggleWalkingDirection() { mWalkingDirection = !mWalkingDirection; };

	bool getWalkingDirection() { return mWalkingDirection; };

	void setWalkingDirection(bool active) { mWalkingDirection = active; };

private:
	int mCutX;
	int mCutY;

	double mWaitForShot;

	int mHealth;

	bool mWalkingDirection; //true is right, false is left

	Vector2D mGameEntityLocation;
};
