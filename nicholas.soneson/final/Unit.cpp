#include "Unit.h"
#include "Game.h"

Unit::Unit(Vector2D location, vector<Animation*> animList)
{
	mLocation = location;
	mCurrentAnimation = 0;
	mpAnimList = animList;
	setBoundedZone();
}

Unit::~Unit()
{
	delete mBoundedZone;

	for (vector<Animation*>::iterator i = mpAnimList.begin(); i != mpAnimList.end(); i++)
	{
		delete (*i);
	}
	mpAnimList.clear();
}

void Unit::setAnimation(int animationNumber) 
{
	mCurrentAnimation = animationNumber;
}

void Unit::drawUnit() //draw the current Animation's current Sprite
{
	//Game::getInstance()->getSystem()->getGraphicsSystem()->draw(mpAnimList[mCurrentAnimation]->getCurrentSprite(), mLocation); //draw the current Sprite
	Game::getInstance()->getSystem()->getGraphicsSystem()->currentGraphicsBufferDraw(mLocation.getX(), mLocation.getY(), mpAnimList[mCurrentAnimation]->getCurrentSprite(), 1.0);
}

void Unit::updateUnit(double gameSpeed) //adjust state of Unit
{
	mpAnimList[mCurrentAnimation]->update(gameSpeed); //go to next Sprite in the Animation
	setBoundedZone();
}

void Unit::setBoundedZone()
{
	int xLoc = mLocation.getX();
	int yLoc = mLocation.getY();

	int height = mpAnimList[mCurrentAnimation]->getCurrentSprite()->getHeight();
	int width = mpAnimList[mCurrentAnimation]->getCurrentSprite()->getWidth();

	if (mBoundedZone == nullptr)
	{
		mBoundedZone = new BoundedZone(xLoc + width, yLoc + height, xLoc, yLoc);
	}
	else
	{
		mBoundedZone->updateBoundedZone(xLoc, yLoc, width, height);
	}
}


void Unit::modifyAnimationSpeed(double speedModifier)
{
	//Modify the Animation speed for all Animations in mpAnimList
	for (vector<Animation*>::iterator i = mpAnimList.begin(); i != mpAnimList.end(); i++)
	{
		//(*i)->adjustTiming(speedModifier);
		(*i)->adjustTimingAnimation(speedModifier);
	}
}