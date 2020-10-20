#include "PowerupManager.h"
#include "Game.h"

PowerupManager::PowerupManager()
{
	mTargetTime = Game::getInstance()->getDataLoader()->getPowerupTimer();
	mTimeUntilNextPlacement = mTargetTime;
}

PowerupManager::~PowerupManager()
{
	if (mCurrentPowerup != nullptr)
	{
		delete mCurrentPowerup;
	}
}

void PowerupManager::update(double gameSpeed)
{
	if (mSpawnPowerups)
	{
		mTimeUntilNextPlacement -= gameSpeed;

		if (mTimeUntilNextPlacement <= 0.0)
		{
			randomizePowerup();
			placePowerup();

			mTimeUntilNextPlacement = mTargetTime;
		}

		if (mCurrentPowerup != nullptr)
		{
			mCurrentPowerup->updateUnit(gameSpeed);
		}
	}
}

void PowerupManager::randomizePowerup()
{
	int randomType = rand() % Powerup::NUM_POWERUPS; //randomly choose a type

	if (mCurrentPowerup != nullptr)
	{
		delete mCurrentPowerup;
	}

	mCurrentPowerup = new Powerup((Powerup::PowerupType)randomType);	//REMEMBER TO CHANGE THIS BACK TO RANDOMTYPE
}

void PowerupManager::placePowerup()
{
	Vector2D randLocation;

	int itemWidth = mCurrentPowerup->getAnimation()->getCurrentSprite()->getWidth();
	int itemHeight = mCurrentPowerup->getAnimation()->getCurrentSprite()->getHeight();

	//Keep trying to find a free location
	do
	{
		int maxX = (int)Game::getInstance()->getCurrentLevel()->getPlayableZone()->getAxisX().getY() - (itemWidth * 2);
		int minX = (int)Game::getInstance()->getCurrentLevel()->getPlayableZone()->getAxisX().getX();
		int maxY = (int)Game::getInstance()->getCurrentLevel()->getPlayableZone()->getAxisY().getY() - (itemHeight * 2);
		int minY = (int)Game::getInstance()->getCurrentLevel()->getPlayableZone()->getAxisY().getX();

		//Create a random location
		int randX = rand() % maxX + minX;
		int randY = rand() % (maxY) + minY;
		randLocation.setX(randX);
		randLocation.setY(randY);
	} while (checkForFreeArea(randLocation) == false);

	mCurrentPowerup->setLocation(randLocation);
}

bool PowerupManager::checkForFreeArea(Vector2D location)
{
	bool areaIsFree = true;

	//Compare the location of all obstacles to the proposed spawn location
	for (int i = 0; i < Game::getInstance()->getUnitManager()->getNumUnits(); i++)
	{
		int unitWidth = Game::getInstance()->getUnitManager()->getUnit(i)->getAnimation()->getCurrentSprite()->getWidth();
		int unitHeight = Game::getInstance()->getUnitManager()->getUnit(i)->getAnimation()->getCurrentSprite()->getHeight();
		Vector2D unitLoc = Game::getInstance()->getUnitManager()->getUnit(i)->getLocation();

		if (unitLoc.getX() <= location.getX() + unitWidth && unitLoc.getX() + unitWidth >= location.getX() &&
			unitLoc.getY() <= location.getY() + unitHeight && unitLoc.getY() + unitHeight >= location.getY()
			)
		{
			areaIsFree = false;
			break;
		}
	}

	return areaIsFree;
}

bool PowerupManager::powerupPresent()
{
	bool present = false;
	if (mCurrentPowerup != nullptr)
	{
		present = true;
	}
	return present;
}

void PowerupManager::removePowerup()
{
	delete mCurrentPowerup;
	mCurrentPowerup = nullptr;
}
