#include "Animation.h"


using namespace std;

Animation::Animation(int spriteCutWidth, int spriteCutHeight, int spriteAmountX, int spriteAmountY, GraphicsBuffer* buffer)
{
	//time parameters for update loop
	mTargetTime = 100.0;	
	mTimeUntilNextFrame = mTargetTime;

	//Buffer to split from
	//mpAnimBuffer = new GraphicsBuffer(path);
	mpAnimBuffer = buffer;


	//tracks what "frame" we are in the animation
	mCurrentSpriteInLOS = 0;
	mCurrentSpriteMax = 0;
	mShouldAnimation = true;

	//buffer splitting
	for (int i = 0; i < spriteAmountX; i++)
	{
		for (int j = 0; j < spriteAmountY; j++)
		{

			mpCurrentSprite = new Sprite(mpAnimBuffer, (spriteCutWidth * j), (spriteCutHeight * i), spriteCutWidth, spriteCutHeight);

			mCurrentSpriteMax++;

			addSprite(mpCurrentSprite);

			
		}
	}

	
}

Animation::~Animation()
{
	//deletes the buffer for the SpriteSheet
	//delete mpAnimBuffer;
	
	//deletes all pointers in vector, including the mCurrentSprite technically
	for (vector<Sprite*>::iterator i = mListOfSprites.begin(); i != mListOfSprites.end(); i++)
	{
		delete(*i);
	}
	mListOfSprites.clear();
	
}


void Animation::addSprite(Sprite* givenSprite)
{
	mListOfSprites.push_back(givenSprite);
}

void Animation::adjustTimingAnimation(double adjustment)
{
	mTargetTime += adjustment;
	//cout << "\nTarget Time: " << mTargetTime;
}


void Animation::update(double deltaTime)
{

	//just set to true for now, probably have stop upon exit condition

	mTimeUntilNextFrame -= deltaTime;


	if (mTimeUntilNextFrame <= 0.0)
	{
		//change animation
		if (mShouldAnimation)
		{
			mpCurrentSprite = mListOfSprites.at(mCurrentSpriteInLOS);
			mCurrentSpriteInLOS++;

			//cout << "\ncurrent sprite = " << mCurrentSpriteInLOS;

			if (mCurrentSpriteInLOS == mCurrentSpriteMax)
			{
				mCurrentSpriteInLOS = 0;
			}
		}

		mTimeUntilNextFrame = mTargetTime;
	}
	
}