#include "Tumbleweed.h"
#include "Game.h"

Tumbleweed::Tumbleweed(vector<Animation*> animations, Vector2D startingLocation, float scale, float speed, bool direction)
{
	//Sets first animation as start up, as well as uses vector's copy constructor
	/*mCurrAnimTracker = 0;
	mpCurrentAnimation = animations.at(mCurrAnimTracker);
	mAnimations = animations;

	//starting location is typically upper left hand until changed
	mGameEntityLocation.setX(startingLocation.getX());
	mGameEntityLocation.setY(startingLocation.getY());*/
	setLocation(startingLocation);
	setAnimationList(animations);
	setAnimation(0);

	//incase we want to scale the sprite later on
	mScaledSprite = scale;

	mSpeedOfTumbleweed = speed;

	mDirection = direction;

	mGameEntityLocation = startingLocation;
}

void Tumbleweed::update(double deltaTime)
{
	//change the "frame" of the animation
	//mpCurrentAnimation->update(deltaTime);
	updateUnit(deltaTime);

	float locX = getLocation().getX();
	float locY = getLocation().getY();
	if (mDirection)
	{
		//mGameEntityLocation.setX(mGameEntityLocation.getX() - mSpeedOfTumbleweed);
		Vector2D newLoc ((locX - mSpeedOfTumbleweed), locY);
		setLocation(newLoc);
	}
	else
	{
		//mGameEntityLocation.setX(mGameEntityLocation.getX() + mSpeedOfTumbleweed);
		Vector2D newLoc((locX + mSpeedOfTumbleweed), locY);
		setLocation(newLoc);
	}

	//Draw the changed frame
	drawUnit();
}

void Tumbleweed::shot()
{
	mMarkForDelete = true;

	int score = Game::getInstance()->getDataLoader()->getTumbleweedScore();
	Game::getInstance()->getScoreSystem()->addToScore(score);
}

