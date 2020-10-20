#pragma once

#include "Vector2D.h"
#include "Animation.h"

#include "Unit.h"


class Tumbleweed : public Unit
{
public:
	Tumbleweed(vector<Animation*> animations, Vector2D startingLocation, float scale, float speed, bool direction);

	void update(double deltaTime); //at minimum will call animation's update
	void shot() override;

	float getSpeedOfTumbleweed() { return mSpeedOfTumbleweed; };
	float getScaledSprite() { return mScaledSprite; };
	bool getDeleteFlag() { return mMarkForDelete; };
	bool getDirection() { return mDirection; };

	void setDeleteFlag(bool active) { mMarkForDelete = active; };
	void setDirection(bool active) { mDirection = active; };

	Vector2D getGameEntityLocation() { return mGameEntityLocation; };

private:

	float mScaledSprite; //the scale for which the draw

	float mSpeedOfTumbleweed;

	bool mDirection; //true = go right
	bool mMarkForDelete = false;

	Vector2D mGameEntityLocation;
};