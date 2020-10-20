#include "UnitManager.h"

UnitManager::UnitManager()
{
	//Nothing needed
}

UnitManager::~UnitManager()
{
	clear();
}

void UnitManager::addUnit(Unit* unit)
{
	mUnitList.push_back(unit);
}

void UnitManager::createUnit(Vector2D location, vector<Animation*> animList)
{
	Unit* unit = new Unit(location, animList);
	addUnit(unit);
}

void UnitManager::deleteUnit(Vector2D mousePos)
{

	//Find the Unit with the given location and erase it from mUnitList
	for (vector<Unit*>::iterator i = mUnitList.begin(); i != mUnitList.end();)
	{
		int spriteWidth = (*i)->getAnimation()->getCurrentSprite()->getWidth();
		int spriteHeight = (*i)->getAnimation()->getCurrentSprite()->getHeight();

		//Need to check in area since the chances of clicking the exact pixel are so low
		if  ( (*i)->getLocation().getX() <= mousePos.getX() && (*i)->getLocation().getX() + spriteWidth >= mousePos.getX() &&
			  (*i)->getLocation().getY() <= mousePos.getY() && (*i)->getLocation().getY() + spriteHeight >= mousePos.getY()
			)
		{
			delete (*i);
			i = mUnitList.erase(i);
		}
		else
		{
			i++;
		}
	}
}

void UnitManager::clear()
{
	//Delete all Units in mUnitList
	for (vector<Unit*>::iterator i = mUnitList.begin(); i != mUnitList.end(); i++)
	{
		delete (*i);
	}
	mUnitList.clear();
}

void UnitManager::update(double gameSpeed)
{
	//Update all Units in mUnitList
	for (vector<Unit*>::iterator i = mUnitList.begin(); i != mUnitList.end(); i++)
	{
		(*i)->updateUnit(gameSpeed);
	}
}

void UnitManager::draw()
{
	//Draw all Units in mUnitList
	for (vector<Unit*>::iterator i = mUnitList.begin(); i != mUnitList.end(); i++)
	{
		(*i)->drawUnit();
	}
}

bool UnitManager::unitExists()
{
	bool exists = false;

	if (mUnitList.size() > 0)
	{
		exists = true;
	}

	return exists;
}
