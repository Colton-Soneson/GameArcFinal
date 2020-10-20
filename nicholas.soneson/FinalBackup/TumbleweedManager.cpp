#include "TumbleweedManager.h"
#include "Tumbleweed.h"

void TumbleweedManager::checkForPlayerCollision()
{
	for (vector<Tumbleweed*>::iterator i = mListOfTumbleweeds.begin(); i != mListOfTumbleweeds.end();)
	{
		//this gets the middle top of the Tumbleweed
		Vector2D TumbleweedMid((*i)->getLocation().getX() + ((*i)->getAnimation()->getCurrentSprite()->getWidth() * 0.5), (*i)->getLocation().getY());

		/*
		bool TumbleweedCollided = Game::getInstance()->getCentipedeManager()->checkCentipedeContact(TumbleweedMid);


		if (TumbleweedCollided)
		{
			deleteTumbleweed((*i));
			i = mListOfTumbleweeds.erase(i);
		}
		else
		{
			i++;
		}
		*/
	}
}

void TumbleweedManager::checkBZCollision(BoundedZone* zone)
{
	for (vector<Tumbleweed*>::iterator i = mListOfTumbleweeds.begin(); i != mListOfTumbleweeds.end();)
	{
		//this gets the middle top of the Tumbleweed
		int TumbleweedLeft = (*i)->getLocation().getX();
		int TumbleweedRight = (*i)->getLocation().getX() + (*i)->getAnimation()->getCurrentSprite()->getWidth();

		//cout << "tumbleRight = " << TumbleweedRight << "\t tumbleleft = " << TumbleweedLeft << endl;
		//cout << "tumble right >  " << zone->getAxisX().getY() << "\t tumbleleft < " << zone->getAxisX().getX() <<  " then leave" << endl;

		//this is the lowest part (top of screen) of the y axis zone given.
		if (TumbleweedLeft <= zone->getAxisX().getX() || TumbleweedRight >= zone->getAxisX().getY())
		{
			deleteTumbleweed((*i));
			i = mListOfTumbleweeds.erase(i);
		}
		else
		{
			i++;
		}

	}
}

Tumbleweed* TumbleweedManager::getLastPlacedTumbleweed()
{
	return mListOfTumbleweeds.back();	//Ben nicholas told me to use .back rather than get a reference to last position because that crashed after you deleted some
}

void TumbleweedManager::cleanup()
{
	for (vector<Tumbleweed*>::iterator i = mListOfTumbleweeds.begin(); i != mListOfTumbleweeds.end(); i++)
	{
		//removal of all Tumbleweeds, depending on how many, may take a second
		delete (*i);
	}
	mListOfTumbleweeds.clear();
}

bool TumbleweedManager::TumbleweedExists()
{
	bool thereIsATumbleweed = false;

	/*for (vector<Tumbleweed*>::iterator i = mListOfTumbleweeds.begin(); i != mListOfTumbleweeds.end(); i++)
	{
		//if it returns a value for i, then there are Tumbleweeds present in the list
		if ((*i))
		{
			thereIsATumbleweed = true;
		}
	}*/
	if (!mListOfTumbleweeds.empty())
	{
		thereIsATumbleweed = true;
	}

	return thereIsATumbleweed;
}

Tumbleweed* TumbleweedManager::createAndManageTumbleweed(vector<Animation*> animations, const float scale, const float speed)
{

	float direction = rand() % 4;	//this is just a way to get a 50 / 50 direction chance
	bool setDir = false;
	if (direction <= 1)
	{
		setDir = true;
	}

	Vector2D loc;

	if (!setDir)
	{
		loc.setX(51);
	}
	else
	{
		loc.setX(799);
	}

	int yPos = (rand() % 800) + 100;
	loc.setY(yPos);

	mpCurrentTumbleweed = new Tumbleweed(animations, loc, scale, speed, setDir);
	mListOfTumbleweeds.push_back(mpCurrentTumbleweed);

	//this last Tumbleweed return is basically what the dean head is going to act on
	return mpCurrentTumbleweed;
}

void TumbleweedManager::updateTumbleweed(double frameRate)
{
	removeMarkedDelete(); //remove any tumbleweeds that have been marked for deletion
	for (vector<Tumbleweed*>::iterator i = mListOfTumbleweeds.begin(); i != mListOfTumbleweeds.end(); i++)
	{
		//updates animation for every Tumbleweed
		(*i)->update(frameRate);
	}
}

void TumbleweedManager::deleteTumbleweed(const TumbleweedVectorLoc& loc)
{
	Vector2D searchedTumbleweedLoc;

	for (vector<Tumbleweed*>::iterator i = mListOfTumbleweeds.begin(); i != mListOfTumbleweeds.end();)
	{
		searchedTumbleweedLoc.setX((*i)->getLocation().getX());
		searchedTumbleweedLoc.setY((*i)->getLocation().getY());

		//looks ugly, but this searches for the boxed value of the animation, and cross checks it with the click location
		if (searchedTumbleweedLoc.getX() <= loc.getX() && searchedTumbleweedLoc.getX() + (*i)->getAnimation()->getCurrentSprite()->getWidth()
			>= loc.getX() && searchedTumbleweedLoc.getY() <= loc.getY() && searchedTumbleweedLoc.getY() + (*i)->getAnimation()->getCurrentSprite()->getHeight() >= loc.getY())
		{
			deleteTumbleweed((*i));
			i = mListOfTumbleweeds.erase(i);
		}
		else
		{
			i++;
		}
	}
}

void TumbleweedManager::deleteTumbleweed(Tumbleweed* pTumbleweed)
{
	delete pTumbleweed;
}

Tumbleweed* TumbleweedManager::searchTumbleweed(const TumbleweedVectorLoc& loc)
{
	Vector2D searchedTumbleweedLoc;
	Tumbleweed* sTumbleweed = NULL;

	for (vector<Tumbleweed*>::iterator i = mListOfTumbleweeds.begin(); i != mListOfTumbleweeds.end(); i++)
	{
		searchedTumbleweedLoc.setX((*i)->getLocation().getX());
		searchedTumbleweedLoc.setY((*i)->getLocation().getY());

		//like the delete Tumbleweed check
		if (searchedTumbleweedLoc.getX() <= loc.getX() && searchedTumbleweedLoc.getX() + (*i)->getAnimation()->getCurrentSprite()->getWidth()
			>= loc.getX() && searchedTumbleweedLoc.getY() <= loc.getY() && searchedTumbleweedLoc.getY() + (*i)->getAnimation()->getCurrentSprite()->getHeight() >= loc.getY())
		{
			sTumbleweed = (*i);
		}
	}

	return sTumbleweed;

}

void TumbleweedManager::removeMarkedDelete()
{
	for (vector<Tumbleweed*>::iterator i = mListOfTumbleweeds.begin(); i != mListOfTumbleweeds.end();)
	{
		if ((*i)->getDeleteFlag())
		{
			deleteTumbleweed((*i));
			i = mListOfTumbleweeds.erase(i);
		}
		else
		{
			i++;
		}
	}
}
