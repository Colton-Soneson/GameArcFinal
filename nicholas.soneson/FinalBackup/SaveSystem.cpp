#include "SaveSystem.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Tumbleweed.h"
#include "Game.h"
#include "Level.h"
#include "Menu.h"
#include "Animation.h"
#include "Powerup.h"

#include "InputSystem.h"

using namespace std;

SaveSystem::SaveSystem(const string& dataFile)
{
	mFileName = dataFile;
	//mpInputFile = new ifstream(mFileName);
	//mpOutputFile = new ofstream(mFileName);
}

void SaveSystem::saveGameState()
{

	//mpOutputFile->open;
	mpOutputFile = new ofstream(mFileName);
	

	saveLevel();
	savePlayer();
	saveEnemy();
	saveScore();
	savePowerUps();
	saveTumbleweeds();
	saveBullets();

	mpOutputFile->close();

	mpOutputFile = nullptr;
}

void SaveSystem::loadGameState()
{

	mpInputFile = new ifstream(mFileName);

	if (mpInputFile->peek() != std::ifstream::traits_type::eof())
	{
		// Essentially, only load if the file isnt empty

		loadLevel();
		loadPlayer();
		loadEnemy();
		loadScore();
		loadPowerUps();
		loadTumbleweeds();
		loadBullets();

	}
	else
	{
		//SET UP A BOOL THAT STATES THAT THERE ARE NO SAVES TO LOAD FROM!!
		cout << endl << "CANT LOAD ANYTHING DOING NOTHING";
	}
	

	mpInputFile->close();

	mpInputFile = nullptr; //THIS MIGHT MESS THE SAVE STUFF UP
}

void SaveSystem::saveLevel()
{
	//I only need this to rebuild the level
	*mpOutputFile << Game::getInstance()->getCurrentLevel()->getLevelsPath() << "\n";
	*mpOutputFile << Game::getInstance()->getCurrentLevel()->getLevelFileName() << "\n";
}

void SaveSystem::saveBullets()
{
	//this is for the load in for loop length
	

	*mpOutputFile << Game::getInstance()->getBulletManager()->getBulletVector()->size() << "\n";
	
	for (vector<Bullet*>::iterator i = Game::getInstance()->getBulletManager()->getBulletVector()->begin();
		i != Game::getInstance()->getBulletManager()->getBulletVector()->end(); 
		i++)
	{
		*mpOutputFile << (*i)->getGameEntityLocation().getX() << "\n";
		*mpOutputFile << (*i)->getGameEntityLocation().getY() << "\n";
		*mpOutputFile << (*i)->getCurrentDirection() << "\n";
		*mpOutputFile << (*i)->getSpeedOfBullet() << "\n";
		*mpOutputFile << (*i)->getOwnership() << "\n";

	}
	
}

void SaveSystem::saveEnemy()
{
	*mpOutputFile << Game::getInstance()->getEnemyManager()->getEnemyList()->size() << "\n";

	for (vector<Enemy*>::iterator i = Game::getInstance()->getEnemyManager()->getEnemyList()->begin();
		i != Game::getInstance()->getEnemyManager()->getEnemyList()->end();
		i++)
	{
		*mpOutputFile << (*i)->getLocation().getX() << "\n";
		*mpOutputFile << (*i)->getLocation().getY() << "\n";
		*mpOutputFile << (*i)->getHealth() << "\n";
		*mpOutputFile << (*i)->getCutX() << "\n";
		*mpOutputFile << (*i)->getCutY() << "\n";
		*mpOutputFile << (*i)->getWalkingDirection() << "\n";

	}
}

void SaveSystem::savePlayer()
{
	*mpOutputFile << Game::getInstance()->getPlayer()->getLocation().getX() << "\n";
	*mpOutputFile << Game::getInstance()->getPlayer()->getLocation().getY() << "\n";
	*mpOutputFile << Game::getInstance()->getPlayer()->getActivePowerupType() << "\n";
}

void SaveSystem::saveScore()
{
	*mpOutputFile << Game::getInstance()->getScoreSystem()->getScore() << "\n";
}

void SaveSystem::savePowerUps()
{
	if (Game::getInstance()->getPowerupManager()->powerupPresent())
	{
		*mpOutputFile << Game::getInstance()->getPowerupManager()->getPowerup()->getLocation().getX() << "\n";
		*mpOutputFile << Game::getInstance()->getPowerupManager()->getPowerup()->getLocation().getY() << "\n";
		*mpOutputFile << Game::getInstance()->getPowerupManager()->getPowerup()->getPowerupType() << "\n";
	}
}

void SaveSystem::saveTumbleweeds()
{
	//how many there are on screen
	*mpOutputFile << Game::getInstance()->getTumbleweedManager()->getTumbleweedVector()->size() << "\n";

	for (vector<Tumbleweed*>::iterator i = Game::getInstance()->getTumbleweedManager()->getTumbleweedVector()->begin();
		i != Game::getInstance()->getTumbleweedManager()->getTumbleweedVector()->end();
		i++)
	{
		*mpOutputFile << (*i)->getGameEntityLocation().getX() << "\n";
		*mpOutputFile << (*i)->getGameEntityLocation().getY() << "\n";
		*mpOutputFile << (*i)->getScaledSprite() << "\n";
		*mpOutputFile << (*i)->getSpeedOfTumbleweed() << "\n";
		*mpOutputFile << (*i)->getDeleteFlag() << "\n";
		*mpOutputFile << (*i)->getDirection() << "\n";

	}
}

//-------------------------------------------------------------------

void SaveSystem::loadLevel()
{
	Game::getInstance()->initPlayer();

	string levelPath;
	string levelData;
	*mpInputFile >> levelPath;
	*mpInputFile >> levelData;

	cout << endl << "LOADING levels";

	Game::getInstance()->setCurrentLevel(new Level(levelPath));
	Game::getInstance()->getCurrentLevel()->initLevelData(levelData);	//this is the problem, so far its not liking the getLevel then init
}

void SaveSystem::loadBullets()
{
	cout << endl << "LOADING Bullets";

	int vectorLength;
	*mpInputFile >> vectorLength;

	Game::getInstance()->getBulletManager()->cleanup();

	int xLoc;
	int yLoc;
	Vector2D tmp;

	int direction;
	EightDirectional eDirection;
	float speed;
	bool ownership;


	for (int i = 0; i < vectorLength; i++)
	{
		*mpInputFile >> xLoc;
		*mpInputFile >> yLoc;
		tmp.setX(xLoc);
		tmp.setY(yLoc);

		*mpInputFile >> direction;
		eDirection = (EightDirectional)direction;

		*mpInputFile >> speed;
		*mpInputFile >> ownership;

		Animation* newBulletAnim = new Animation(Game::getInstance()->getDataLoader()->getBulletCutX(), 
													Game::getInstance()->getDataLoader()->getBulletCutY(), 
														Game::getInstance()->getDataLoader()->getBulletRows(), 
															Game::getInstance()->getDataLoader()->getBulletColumns(), 
																Game::getInstance()->getGraphicsBufferManager()->getBuffer("bullet"));
		vector<Animation*> animations;
		animations.push_back(newBulletAnim);

		//Game::getInstance()->getBulletManager()->createAndManageBullet(animations, tmp, 1.0, speed, eDirection, ownership);
	}
}

void SaveSystem::loadEnemy()
{
	//this is after level is loaded and the enemies are full reset

	//we then parse through the current enemy array
		//delete them all

	//create new enemies with the parameters saved in the file

	cout << endl << "LOADING Enemy";

	int vectorLength;
	*mpInputFile >> vectorLength;

	Game::getInstance()->getEnemyManager()->clear();

	int xLoc;
	int yLoc;
	Vector2D tmp;

	int health;
	int xCut;
	int yCut;

	bool walkDir;
	

	for (int i = 0; i < vectorLength; i++)
	{
		*mpInputFile >> xLoc;
		*mpInputFile >> yLoc;
		tmp.setX(xLoc);
		tmp.setY(yLoc);

		*mpInputFile >> health;

		*mpInputFile >> xCut;
		*mpInputFile >> yCut;

		*mpInputFile >> walkDir;

		Game::getInstance()->getEnemyManager()->createEnemy(tmp, xCut, yCut);

		Game::getInstance()->getEnemyManager()->getEnemyList()->at(i)->setHealth(health);
		Game::getInstance()->getEnemyManager()->getEnemyList()->at(i)->setWalkingDirection(walkDir);
	}
}

void SaveSystem::loadPlayer()
{
	cout << endl << "LOADING player";

	//Game::getInstance()->initPlayer();			//had to do this above load level because load order

	int playerX;
	int playerY;
	int powerType;

	*mpInputFile >> playerX;
	*mpInputFile >> playerY;
	*mpInputFile >> powerType;

	//this whole process may not work
	//Game::getInstance()->getPlayer()->getGameEntityLocation().setX(playerX);
	//Game::getInstance()->getPlayer()->getGameEntityLocation().setY(playerY);

	Vector2D tmp(playerX, playerY);
	Game::getInstance()->getPlayer()->setLocation(tmp);
	Game::getInstance()->getPlayer()->setActivePowerupTypeByInt(powerType);
}

void SaveSystem::loadTumbleweeds()
{

	cout << endl << "LOADING Tumbleweeds";

	int vectorLength;
	*mpInputFile >> vectorLength;

	Game::getInstance()->getTumbleweedManager()->cleanup();

	int xLoc;
	int yLoc;
	Vector2D tmp;

	int scale;
	int speed;
	bool deleteFlag;
	bool dir;


	for (int i = 0; i < vectorLength; i++)
	{
		*mpInputFile >> xLoc;
		*mpInputFile >> yLoc;
		tmp.setX(xLoc);
		tmp.setY(yLoc);

		*mpInputFile >> scale;
		*mpInputFile >> speed;
		*mpInputFile >> deleteFlag;
		*mpInputFile >> dir;

		Animation* newTumbleAnim = new Animation(Game::getInstance()->getDataLoader()->getSpriteCutX(),
			Game::getInstance()->getDataLoader()->getSpriteCutY(),
			Game::getInstance()->getDataLoader()->getTumbleSpriteColumns(),
			Game::getInstance()->getDataLoader()->getTumbleSpriteRows(),
			Game::getInstance()->getGraphicsBufferManager()->getBuffer("tumble"));

		vector<Animation*> animations;
		animations.push_back(newTumbleAnim);

		Game::getInstance()->getTumbleweedManager()->createAndManageTumbleweed(animations, scale, speed);

		Tumbleweed* tmpWeed = Game::getInstance()->getTumbleweedManager()->getTumbleweedVector()->at(i); // .setDirection(dir);
		tmpWeed->setDirection(dir);
		tmpWeed->setDeleteFlag(deleteFlag);

	}

}

void SaveSystem::loadPowerUps()
{
	int xLoc;
	int yLoc;
	int powerType;

	*mpInputFile >> xLoc;
	*mpInputFile >> yLoc;
	*mpInputFile >> powerType;

	Vector2D tmp(xLoc, yLoc);

	Game::getInstance()->getPowerupManager()->randomizePowerup();
	Game::getInstance()->getPowerupManager()->getPowerup()->setLocation(tmp);
	Game::getInstance()->getPowerupManager()->getPowerup()->setPowerupTypeByInt(powerType);
}

void SaveSystem::loadScore()
{
	cout << endl << "LOADING Score";

	int score;
	*mpInputFile >> score;
	Game::getInstance()->getScoreSystem()->setScore(score);
}