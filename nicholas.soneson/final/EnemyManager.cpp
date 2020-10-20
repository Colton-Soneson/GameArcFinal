#include "EnemyManager.h"
#include "Game.h"

EnemyManager::EnemyManager()
{
	//Nothing needed
}

EnemyManager::~EnemyManager()
{
	clear();
}

void EnemyManager::createEnemy(Vector2D location, int spriteCutX, int spriteCutY)
{
	Enemy* enemy = new Enemy(location, spriteCutX, spriteCutY);
	mEnemyList.push_back(enemy);
}

void EnemyManager::clear()
{
	//Delete all Enemies in mEnemyList
	for (vector<Enemy*>::iterator i = mEnemyList.begin(); i != mEnemyList.end(); i++)
	{
		delete (*i);
	}
	mEnemyList.clear();
}

void EnemyManager::adjustEnemyDirection(Enemy* enemy)
{
	if (enemy->getLocation().getX() >= Game::getInstance()->getPlayArea()->getAxisX().getY() - enemy->getAnimation()->getCurrentSprite()->getWidth() ||
		enemy->getLocation().getX() <= Game::getInstance()->getPlayArea()->getAxisX().getX())
	{
		enemy->toggleWalkingDirection();
	}
}

void EnemyManager::update(double gameSpeed)
{
	removeDeadEnemies();
	//Update all Enemies in mEnemyList
	for (vector<Enemy*>::iterator i = mEnemyList.begin(); i != mEnemyList.end(); i++)
	{
		(*i)->updateUnit(gameSpeed);
		(*i)->shootingHandler(E_TOP);
		adjustEnemyDirection((*i));
		(*i)->adjustMovementPosition(Game::getInstance()->getDataLoader()->getEnemyMoveSpeed());
	}
}

void EnemyManager::draw()
{
	//Draw all Enemies in mEnemyList
	for (vector<Enemy*>::iterator i = mEnemyList.begin(); i != mEnemyList.end(); i++)
	{
		(*i)->drawUnit();
	}
}

void EnemyManager::removeDeadEnemies()
{
	for (vector<Enemy*>::iterator i = mEnemyList.begin(); i != mEnemyList.end();)
	{
		//cout << (*i)->getHealth();
		if ((*i)->getHealth() <= 0)
		{
			int score = Game::getInstance()->getDataLoader()->getEnemyKilledScore();
			Game::getInstance()->getScoreSystem()->addToScore(score);

			delete (*i);
			i = mEnemyList.erase(i);
		}
		else
		{
			i++;
		}
	}
}

void EnemyManager::setDifficulty(bool hardMode)
{
	if (hardMode)
	{
		Game::getInstance()->getDataLoader()->setEnemyHealth(Game::getInstance()->getDataLoader()->getNormalEnemyHealth() * 2);
		Game::getInstance()->getDataLoader()->setEnemyShotDelay(Game::getInstance()->getDataLoader()->getNormalEnemyShotDelay() / 2);
		Game::getInstance()->getDataLoader()->setEnemyMoveSpeed(Game::getInstance()->getDataLoader()->getNormalEnemyMoveSpeed() * 2);
	}
	else
	{
		Game::getInstance()->getDataLoader()->setEnemyHealth(Game::getInstance()->getDataLoader()->getNormalEnemyHealth());
		Game::getInstance()->getDataLoader()->setEnemyShotDelay(Game::getInstance()->getDataLoader()->getNormalEnemyShotDelay());
		Game::getInstance()->getDataLoader()->setEnemyMoveSpeed(Game::getInstance()->getDataLoader()->getNormalEnemyMoveSpeed());
	}
}

bool EnemyManager::checkIfAllEnemiesKilled()
{
	bool allKilled = false;
	if (mEnemyList.empty())
	{
		allKilled = true;
	}
	return allKilled;
}

