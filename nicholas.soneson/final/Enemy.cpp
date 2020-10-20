#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(Vector2D location, int spriteCutX, int spriteCutY)
{
	mCutX = spriteCutX;
	mCutY = spriteCutY;
	mHealth = Game::getInstance()->getDataLoader()->getEnemyHealth();
	mWaitForShot = Game::getInstance()->getDataLoader()->getEnemyShotDelay();

	setLocation(location);
	setAnimationList(createAnimation());
	setAnimation(0);
	
	if (rand() % 4 > 2)
	{
		mWalkingDirection = true;
	}
	else
	{
		mWalkingDirection = false;
	}
}

vector<Animation*> Enemy::createAnimation()
{
	int spriteRows = Game::getInstance()->getDataLoader()->getSpriteRows();
	int spriteColumns = Game::getInstance()->getDataLoader()->getSpriteColumns();

	//Make Animations
	GraphicsBuffer* enemyBuffer = Game::getInstance()->getGraphicsBufferManager()->getBuffer("enemy");
	//Animation* enemyAnimation = new Animation(SPR_COLUMNS, SPR_ROWS, enemyBuffer);
	Animation* enemyAnimation = new Animation(mCutX, mCutY, spriteRows, spriteColumns, enemyBuffer);

	vector<Animation*>animList;
	animList.push_back(enemyAnimation);

	return animList;
}

void Enemy::shot()
{
	mHealth -= Game::getInstance()->getPlayer()->getPlayerDamage();

	int score = Game::getInstance()->getDataLoader()->getEnemyShotScore();
	Game::getInstance()->getScoreSystem()->addToScore(score);
}


void Enemy::shootingHandler(EightDirectional direction)
{

	mWaitForShot -= Game::getInstance()->getDataLoader()->getGameSpeed();

	if (mWaitForShot <= 0.0)
	{
		//OurSoundBuffer ShotBuffer("assets/shot.wav");
		//OurSound ShotSound(ShotBuffer);
		//Game::getInstance()->getSystem()->getSoundSystem()->playSingleSound("assets/shot.wav");
		Game::getInstance()->getSystem()->getSoundSystem()->playSingleSound();	 //this only works once setSoundBuffer() has been set

		//shoot
		Animation* newBulletAnim = new Animation(Game::getInstance()->getDataLoader()->getBulletCutX(), 
													Game::getInstance()->getDataLoader()->getBulletCutY(), 
														Game::getInstance()->getDataLoader()->getBulletRows(), 
															Game::getInstance()->getDataLoader()->getBulletColumns(), 
																Game::getInstance()->getGraphicsBufferManager()->getBuffer("bullet"));
		vector<Animation*> animations;
		animations.push_back(newBulletAnim);
		int locX = getLocation().getX() + (getAnimation()->getCurrentSprite()->getWidth() * 0.5);
		int locY = getLocation().getY() + (getAnimation()->getCurrentSprite()->getHeight() * 0.5);
		Vector2D playerMid(locX, locY);
		Game::getInstance()->getBulletManager()->createAndManageBullet(animations, playerMid, 1.0, Game::getInstance()->getDataLoader()->getBulletSpeed(), direction, true);

		//reset timer
		mWaitForShot = Game::getInstance()->getDataLoader()->getEnemyShotDelay();
	}
}

void Enemy::adjustMovementPosition(int movePace)
{

	float xMov;

	if (mWalkingDirection)
	{
		xMov = getLocation().getX() + movePace;
	}
	else 
	{
		xMov = getLocation().getX() - movePace;
	}

	Vector2D tmp(xMov, getLocation().getY());
	setLocation(tmp);
}
