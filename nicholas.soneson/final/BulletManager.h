#pragma once

#include <string>
#include "Vector2D.h"
#include <vector>
#include <Trackable.h>
#include "Animation.h"

#include "BoundedZone.h"	//make sure this isnt circular

using namespace std;

//using namespace std;

class Bullet;

typedef Vector2D BulletVectorLoc;

class BulletManager : public Trackable
{
public:
	BulletManager() {};
	~BulletManager() { cleanup(); };

	void cleanup();	//the "clear all" function

	enum CollisionType
	{
		ENEMY,
		TUMBLEWEED,
		WALL,
		PLAYER_HIT,
		NUM_TYPES
	};

	Bullet* createAndManageBullet(vector<Animation*> animations, Vector2D loc, const float scale, const float speed, EightDirectional setDir, bool enemyOwnership);
	void deleteBullet(const BulletVectorLoc& loc);
	void deleteBullet(Bullet* pBullet);
	void deleteAndRemoveBullet(Bullet* pBullet); //to be called by Bullet, for deleting and removing the Bullet from mBulletList

	//have these just so we can tell ALL Units to be affected
	void animationAdjustments(double animAdjustTime);
	void animationState();
	Bullet* getLastPlacedBullet();

	bool BulletExists();

	Bullet* searchBullet(const BulletVectorLoc& loc);	//this should check the vector2d position with all vector2d position

	void checkBZCollision(BoundedZone* zone);
	void checkForPlayerCollision();
	void checkCollision(CollisionType collisionType);

	void updateBullet(double frameRate);

	Bullet* getCurrentBullet() { return mpCurrentBullet; };

	vector<Bullet*>* getBulletVector() { return &mListOfBullets; };	//might have to be pointer not sure 


private:
	vector<Bullet*> mListOfBullets;
	Bullet* mpCurrentBullet;

};
