#pragma once

#include "CircularQueue.h"
#include <vector>

#include "System.h"
#include "Trackable.h"



//#include "Sprite.h"
//#include "GraphicsBuffer.h"

using namespace std;


class Animation : public Trackable
{
	//list of sprites
	//current sprite
	
	//update function
public:
	

	Animation(int spriteCutWidth, int spriteCutHeight, int spriteAmountX, int spriteAmountY, GraphicsBuffer* buffer);
	~Animation();

	void addSprite(Sprite* givenSprite);

	Sprite* getCurrentSprite() { return mpCurrentSprite; };

	void adjustTimingAnimation(double adjustment);	//this is SetTargetTime()

	void changeAnimationState() { mShouldAnimation = !mShouldAnimation; };

	void update(double deltaTime);

	

private:
	
	vector<Sprite*> mListOfSprites;		//not sure if its supposed to be a pointer val or not

	double mTargetTime;	//what gets adjusted in AdjustTimingAnimation
	double mTimeUntilNextFrame;

	Sprite* mpCurrentSprite;
	GraphicsBuffer* mpAnimBuffer;

	int mCurrentSpriteInLOS;
	int mCurrentSpriteMax;

	bool mShouldAnimation;

};