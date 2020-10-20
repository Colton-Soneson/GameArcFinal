#include "BulletManager.h"
#include "Bullet.h"


using namespace std;



void BulletManager::animationAdjustments(double animAdjustTime)
{
	for (vector<Bullet*>::iterator i = mListOfBullets.begin(); i != mListOfBullets.end(); i++)
	{
		(*i)->getCurrentAnim()->adjustTimingAnimation(animAdjustTime);
	}
}

void BulletManager::animationState()
{
	for (vector<Bullet*>::iterator i = mListOfBullets.begin(); i != mListOfBullets.end(); i++)
	{
		//goes through and changes all active animations states
		(*i)->getCurrentAnim()->changeAnimationState();
	}
}

void BulletManager::checkForPlayerCollision()
{
	for (vector<Bullet*>::iterator i = mListOfBullets.begin(); i != mListOfBullets.end();)
	{
		//this gets the middle top of the Bullet
		Vector2D BulletMid((*i)->getGameEntityLocation().getX() + ((*i)->getCurrentAnim()->getCurrentSprite()->getWidth() * 0.5), (*i)->getGameEntityLocation().getY());

		/*
		bool BulletCollided = Game::getInstance()->getCentipedeManager()->checkCentipedeContact(BulletMid);


		if (BulletCollided)
		{
			deleteBullet((*i));
			i = mListOfBullets.erase(i);
		}
		else
		{
			i++;
		}
		*/
	}
}

void BulletManager::checkBZCollision(BoundedZone* zone)
{
	for (vector<Bullet*>::iterator i = mListOfBullets.begin(); i != mListOfBullets.end();)
	{
		//this gets the middle top of the Bullet
		//int BulletLeft = (*i)->getGameEntityLocation().getX();
		//int BulletRight = (*i)->getGameEntityLocation().getX() + (*i)->getCurrentAnim()->getCurrentSprite()->getWidth();

		//cout << "tumbleRight = " << BulletRight << "\t tumbleleft = " << BulletLeft << endl;
		//cout << "tumble right >  " << zone->getAxisX().getY() << "\t tumbleleft < " << zone->getAxisX().getX() <<  " then leave" << endl;

		int locX = (*i)->getGameEntityLocation().getX() + ((*i)->getCurrentAnim()->getCurrentSprite()->getWidth() * 0.5);
		int locY = (*i)->getGameEntityLocation().getY() + ((*i)->getCurrentAnim()->getCurrentSprite()->getHeight() * 0.5);
		Vector2D bulletMid(locX, locY);

		//this is the lowest part (top of screen) of the y axis zone given.
		if (bulletMid.getX() <= zone->getAxisX().getX() || bulletMid.getX() >= zone->getAxisX().getY() || 
			bulletMid.getY() <= zone->getAxisY().getX() || bulletMid.getY() >= zone->getAxisY().getY())
		{
			//cout << "\n---BULLET COLLISION---";
			deleteBullet((*i));
			i = mListOfBullets.erase(i);
		}
		else
		{
			i++;
		}

	}
}

void BulletManager::checkCollision(CollisionType collisionType)
{
	int numUnits;
	string debugLine;

	if (collisionType == ENEMY)
	{
		numUnits = Game::getInstance()->getEnemyManager()->getNumEnemies();
		debugLine = "\n---BULLET-ENEMY COLLISION---";
	}
	else if (collisionType == TUMBLEWEED)
	{
		numUnits = Game::getInstance()->getTumbleweedManager()->getTotalNum();
		debugLine = "\n---BULLET-TUMBLEWEED COLLISION---";
	}
	else if (collisionType == WALL)
	{
		numUnits = Game::getInstance()->getUnitManager()->getNumUnits();
		debugLine = "\n---BULLET-WALL COLLISION---";
	}
	else if (collisionType == PLAYER_HIT)
	{
		numUnits = Game::getInstance()->getUnitManager()->getNumUnits();
		debugLine = "\n---PLAYER_HIT COLLISION---";
	}

	for (int i = 0; i < numUnits; i++)
	{
		Unit* unit = nullptr;
		if (collisionType == ENEMY)
		{
			unit = Game::getInstance()->getEnemyManager()->getEnemy(i);
		}
		else if (collisionType == TUMBLEWEED)
		{
			unit = Game::getInstance()->getTumbleweedManager()->getTumbleweed(i);
		}
		else if (collisionType == WALL)
		{
			unit = Game::getInstance()->getUnitManager()->getUnit(i);
		}
		else if (collisionType == PLAYER_HIT)
		{
			unit = Game::getInstance()->getPlayer();
		}

		BoundedZone* unitBZ = unit->getBoundedZone();
		
		for (vector<Bullet*>::iterator j = mListOfBullets.begin(); j != mListOfBullets.end();)
		{
			int locX = (*j)->getGameEntityLocation().getX() + ((*j)->getCurrentAnim()->getCurrentSprite()->getWidth() * 0.5);
			int locY = (*j)->getGameEntityLocation().getY() + ((*j)->getCurrentAnim()->getCurrentSprite()->getHeight() * 0.5);
			Vector2D bulletMid(locX, locY);

			//Check if the Bullet has entered the Unit's BoundingZone
			if (unitBZ->getAxisY().getX() <= bulletMid.getY() && unitBZ->getAxisY().getY() >= bulletMid.getY() &&
				unitBZ->getAxisX().getX() <= bulletMid.getX() && unitBZ->getAxisX().getY() >= bulletMid.getX()
				)
			{

				if ((collisionType == ENEMY || collisionType == TUMBLEWEED) && (*j)->getEnemyOwnership() == false)	//the player shot at enemy
				{
					cout << debugLine;
					unit->shot(); //enemy or tumbleweed is shot
					deleteBullet((*j));
					j = mListOfBullets.erase(j);
				}
				else if ((collisionType == ENEMY || collisionType == TUMBLEWEED) && (*j)->getEnemyOwnership() == true)	//the enemy is trying not to shoot itself or other enemies
				{
					j++;
				}
				else if ((collisionType == PLAYER_HIT) && (*j)->getEnemyOwnership() == false)	//the player is trying not to shoot itself
				{
					j++;
				}
				else if ((collisionType == PLAYER_HIT) && (*j)->getEnemyOwnership() == true)	//the player got shot
				{
					cout << debugLine;
					unit->shot(); //player is shot
					deleteBullet((*j));
					j = mListOfBullets.erase(j);
				}
				else
				{
					cout << debugLine;
					deleteBullet((*j));
					j = mListOfBullets.erase(j);
				}
			}
			else
			{
				j++;
			}
		}
	}
}

Bullet* BulletManager::getLastPlacedBullet()
{
	return mListOfBullets.back();	//Ben nicholas told me to use .back rather than get a reference to last position because that crashed after you deleted some
}

void BulletManager::cleanup()
{
	for (vector<Bullet*>::iterator i = mListOfBullets.begin(); i != mListOfBullets.end(); i++)
	{
		//removal of all Bullets, depending on how many, may take a second
		delete (*i);
	}
	mListOfBullets.clear();
}

bool BulletManager::BulletExists()
{
	/*bool thereIsABullet = false;

	for (vector<Bullet*>::iterator i = mListOfBullets.begin(); i != mListOfBullets.end(); i++)
	{
		//if it returns a value for i, then there are Bullets present in the list
		if ((*i))
		{
			thereIsABullet = true;
		}
	}

	return thereIsABullet;*/
	bool thereIsABullet = false;
	if (mListOfBullets.empty())
	{
		thereIsABullet =  true;
	}
	return thereIsABullet;
}

Bullet* BulletManager::createAndManageBullet(vector<Animation*> animations, Vector2D loc, const float scale, const float speed, EightDirectional setDir, bool enemyOwnership)
{


	mpCurrentBullet = new Bullet(animations, loc, scale, speed, setDir, enemyOwnership);
	mListOfBullets.push_back(mpCurrentBullet);

	//this last Bullet return is basically what the dean head is going to act on
	return mpCurrentBullet;
}

void BulletManager::updateBullet(double frameRate)
{
	
	for (vector<Bullet*>::iterator i = mListOfBullets.begin(); i != mListOfBullets.end(); i++)
	{
		//updates animation for every Bullet
		(*i)->update(frameRate);
	}
	/*checkEnemyCollision();
	checkTumbleweedCollision();
	checkWallCollision();*/

	for (int i = 0; i < NUM_TYPES; i++)
	{
		checkCollision((CollisionType)i);
	}
}

void BulletManager::deleteBullet(const BulletVectorLoc& loc)
{
	Vector2D searchedBulletLoc;

	for (vector<Bullet*>::iterator i = mListOfBullets.begin(); i != mListOfBullets.end();)
	{
		searchedBulletLoc.setX((*i)->getGameEntityLocation().getX());
		searchedBulletLoc.setY((*i)->getGameEntityLocation().getY());

		//looks ugly, but this searches for the boxed value of the animation, and cross checks it with the click location
		if (searchedBulletLoc.getX() <= loc.getX() && searchedBulletLoc.getX() + (*i)->getCurrentAnim()->getCurrentSprite()->getWidth()
			>= loc.getX() && searchedBulletLoc.getY() <= loc.getY() && searchedBulletLoc.getY() + (*i)->getCurrentAnim()->getCurrentSprite()->getHeight() >= loc.getY())
		{
			deleteBullet((*i));
			i = mListOfBullets.erase(i);
		}
		else
		{
			i++;
		}
	}
}

void BulletManager::deleteBullet(Bullet* pBullet)
{
	delete pBullet;
}

void BulletManager::deleteAndRemoveBullet(Bullet* pBullet)
{
	for (vector<Bullet*>::iterator i = mListOfBullets.begin(); i != mListOfBullets.end();)
	{
		if (pBullet == *i)
		{
			deleteBullet((*i));
			i = mListOfBullets.erase(i);
		}
		else
		{
			i++;
		}
	}
}

Bullet* BulletManager::searchBullet(const BulletVectorLoc& loc)
{
	Vector2D searchedBulletLoc;
	Bullet* sBullet = NULL;

	for (vector<Bullet*>::iterator i = mListOfBullets.begin(); i != mListOfBullets.end(); i++)
	{
		searchedBulletLoc.setX((*i)->getGameEntityLocation().getX());
		searchedBulletLoc.setY((*i)->getGameEntityLocation().getY());

		//like the delete Bullet check
		if (searchedBulletLoc.getX() <= loc.getX() && searchedBulletLoc.getX() + (*i)->getCurrentAnim()->getCurrentSprite()->getWidth()
			>= loc.getX() && searchedBulletLoc.getY() <= loc.getY() && searchedBulletLoc.getY() + (*i)->getCurrentAnim()->getCurrentSprite()->getHeight() >= loc.getY())
		{
			sBullet = (*i);
		}
	}

	return sBullet;

}

