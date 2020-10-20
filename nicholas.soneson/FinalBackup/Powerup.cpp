#include "Powerup.h"
#include "Game.h"

Powerup::Powerup(PowerupType type)
{
	mPowerupType = type;
	setAnimationList(createAnimation());
	setAnimation(0);
}

vector<Animation*> Powerup::createAnimation()
{
	GraphicsBuffer* powerupBuffer = Game::getInstance()->getGraphicsBufferManager()->getBuffer("powerup");
	int spriteCutWidth = Game::getInstance()->getDataLoader()->getSpriteCutX();
	int spriteCutHeight = Game::getInstance()->getDataLoader()->getSpriteCutY();

	int spriteRows = Game::getInstance()->getDataLoader()->getSpriteRows();
	int spriteColumns = Game::getInstance()->getDataLoader()->getSpriteColumns();

	Animation* powerupAnimation = new Animation(spriteCutWidth, spriteCutHeight, spriteRows, spriteColumns, powerupBuffer);

	vector<Animation*>animList;
	animList.push_back(powerupAnimation);

	return animList;
}
