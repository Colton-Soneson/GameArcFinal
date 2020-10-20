#include "Bullet.h"

using namespace std;

Bullet::Bullet(vector<Animation*> animations, Vector2D startingLocation, float scale, float speed, EightDirectional direction, bool enemyOwnership)
{
	//Sets first animation as start up, as well as uses vector's copy constructor
	mCurrAnimTracker = 0;
	mpCurrentAnimation = animations.at(mCurrAnimTracker);
	mAnimations = animations;

	//starting location is typically upper left hand until changed
	mGameEntityLocation.setX(startingLocation.getX());
	mGameEntityLocation.setY(startingLocation.getY());

	//incase we want to scale the sprite later on
	mScaledSprite = scale;

	mSpeedOfBullet = speed;

	mDirection = direction;

	mOwnedByEnemy = enemyOwnership;
}

Bullet::~Bullet()
{
	//all animations are deleted prior, and no pointers need to be deleted
	//here because of it (the original CurrentAnim pointer is already deleted)
	for (vector<Animation*>::iterator i = mAnimations.begin(); i != mAnimations.end(); i++)
	{
		delete (*i);
	}
	mAnimations.clear();

}

void Bullet::update(double deltaTime)
{
	//change the "frame" of the animation
	mpCurrentAnimation->update(deltaTime);

	//Vertical
	if (mDirection == E_TOP)
	{
		mGameEntityLocation.setY(mGameEntityLocation.getY() - mSpeedOfBullet);
	}
	if (mDirection == E_DOWN)
	{
		mGameEntityLocation.setY(mGameEntityLocation.getY() + mSpeedOfBullet);
	}

	//Horizontal
	if (mDirection == E_LEFT)
	{
		mGameEntityLocation.setX(mGameEntityLocation.getX() - mSpeedOfBullet);
	}
	if (mDirection == E_RIGHT)
	{
		mGameEntityLocation.setX(mGameEntityLocation.getX() + mSpeedOfBullet);
	}

	//Diagonals
	if (mDirection == E_TOP_RIGHT)
	{
		mGameEntityLocation.setX(mGameEntityLocation.getX() + mSpeedOfBullet);
		mGameEntityLocation.setY(mGameEntityLocation.getY() - mSpeedOfBullet);
	}
	if (mDirection == E_DOWN_RIGHT)
	{
		mGameEntityLocation.setX(mGameEntityLocation.getX() + mSpeedOfBullet);
		mGameEntityLocation.setY(mGameEntityLocation.getY() + mSpeedOfBullet);
	}
	if (mDirection == E_TOP_LEFT)
	{
		mGameEntityLocation.setX(mGameEntityLocation.getX() - mSpeedOfBullet);
		mGameEntityLocation.setY(mGameEntityLocation.getY() - mSpeedOfBullet);
	}
	if (mDirection == E_DOWN_LEFT)
	{
		mGameEntityLocation.setX(mGameEntityLocation.getX() - mSpeedOfBullet);
		mGameEntityLocation.setY(mGameEntityLocation.getY() + mSpeedOfBullet);
	}

	//Draw the changed frame
	drawAnimCurrentSprite();
}

void Bullet::setAnimation()
{
	//when called, go to the next animation in the list
	mCurrAnimTracker++;

	if (mCurrAnimTracker < (int)(mAnimations.size()))
	{
		mpCurrentAnimation = mAnimations.at(mCurrAnimTracker);
	}
	else
	{
		mCurrAnimTracker = 0;	//reset to first animation position at list end
		mpCurrentAnimation = mAnimations.at(mCurrAnimTracker);
	}
}

void Bullet::drawAnimCurrentSprite()
{
	//get the graphicsSystem, then draw the sprite of the animation
	//gGameObject->getSystem()->getGraphicsSystem()->currentGraphicsBufferDraw(mGameEntityLocation.getX(), mGameEntityLocation.getY(), mpCurrentAnimation->getCurrentSprite(), mScaledSprite);
	Game::getInstance()->getSystem()->getGraphicsSystem()->currentGraphicsBufferDraw(mGameEntityLocation.getX(), mGameEntityLocation.getY(), mpCurrentAnimation->getCurrentSprite(), mScaledSprite);

}

void Bullet::setEntityLocationX(int xVal)
{
	//its int to float, but thats because Vector2D expects it
	mGameEntityLocation.setX(xVal);
}

void Bullet::setEntityLocationY(int yVal)
{
	mGameEntityLocation.setY(yVal);
}

/*void  Bullet::checkWallCollision()
{
	int numUnits = Game::getInstance()->getUnitManager()->getNumUnits();

	for (int i = 0; i < numUnits; i++)
	{
		Unit* unit = Game::getInstance()->getUnitManager()->getUnit(i);
		BoundedZone* unitBZ = unit->getBoundedZone();
		
		int locX = mGameEntityLocation.getX() + (mpCurrentAnimation->getCurrentSprite()->getWidth() * 0.5);
		int locY = mGameEntityLocation.getY() + (mpCurrentAnimation->getCurrentSprite()->getHeight() * 0.5);
		Vector2D bulletMid(locX, locY);

		if (unitBZ->getAxisY().getX() <= bulletMid.getY() && unitBZ->getAxisY().getY() >= bulletMid.getY() &&
			unitBZ->getAxisX().getX() <= bulletMid.getX() && unitBZ->getAxisX().getY() >= bulletMid.getX()
			)
		{
			cout << "\n---BULLET-WALL COLLISION---";
			Game::getInstance()->getBulletManager()->deleteAndRemoveBullet(this);
		}		
	}
}*/