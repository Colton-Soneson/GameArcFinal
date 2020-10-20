#pragma once

#include "Game.h"

#include "Vector2D.h"
#include "Animation.h"

#include "Trackable.h"

using namespace std;


class Bullet : public Trackable
{
	//animation
	//location

	friend class BulletManager;

public:

	void update(double deltaTime); //at minimum will call animation's update
	void drawAnimCurrentSprite();

	//void  checkWallCollision();

	void setAnimation();	//the switch between the two animations

	void setEntityLocationX(int xVal);
	void setEntityLocationY(int yVal);

	void toggleOwnership() { mOwnedByEnemy = !mOwnedByEnemy; };
	bool getEnemyOwnership() { return mOwnedByEnemy; }

	Vector2D getGameEntityLocation() { return mGameEntityLocation; };

	Animation* getCurrentAnim() { return mpCurrentAnimation; }

	EightDirectional getCurrentDirection() { return mDirection; };
	float getSpeedOfBullet() { return mSpeedOfBullet; };

	bool getOwnership() { return mOwnedByEnemy; };

private:
	Bullet(vector<Animation*> animations, Vector2D startingLocation, float scale, float speed, EightDirectional direction, bool enemyOwnership);
	~Bullet();


	Vector2D mGameEntityLocation;

	Animation* mpCurrentAnimation;
	int mCurrAnimTracker;

	float mScaledSprite; //the scale for which the draw

	vector<Animation*> mAnimations; //mAnimations(mSmurfAnim, mDeanAnim)

	float mSpeedOfBullet;

	EightDirectional mDirection; 

	bool mOwnedByEnemy;
};