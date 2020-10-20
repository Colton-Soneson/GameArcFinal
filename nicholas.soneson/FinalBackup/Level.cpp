#include "Level.h"
#include "Game.h"
#include "Enemy.h"

Level::~Level()
{
	delete mpBoundedZone;
	delete mpPlayableZone;
}

void Level::initLevelData(const string& levelDataFile)
{
	mLevelFileName = levelDataFile;

	ifstream file(mLevelsPath + levelDataFile);

	//Build the level (place walls)
	string levelLayout;
	file >> levelLayout;
	buildLevel(levelLayout);

	//Set Bounded Zone
	int maxX, maxY, minX, minY;
	file >> maxX >> maxY >> minX >> minY;
	mpBoundedZone = new BoundedZone(maxX, maxY, minX, minY);

	//Set Playable Zone
	file >> maxX >> maxY >> minX >> minY;
	mpPlayableZone = new BoundedZone(maxX, maxY, minX, minY);

	//Store the next level's data file
	file >> mNextLevelData;
}

void Level::buildLevel(const string& levelLayoutFile)
{
	ifstream file(mLevelsPath + levelLayoutFile);

	string row;

	int spriteRows = Game::getInstance()->getDataLoader()->getSpriteRows();
	int spriteColumns = Game::getInstance()->getDataLoader()->getSpriteColumns();
	int spriteCutX = Game::getInstance()->getDataLoader()->getSpriteCutX();
	int spriteCutY = Game::getInstance()->getDataLoader()->getSpriteCutY();

	//const int SPRITE_SIZE = 50;
	const int MAX_NUM_WALLS = (Game::getInstance()->getDataLoader()->getDisplayWidth() - (spriteCutX * 2)) / spriteCutX; //16; leave 1 sprite width on each side for HUD

	int x = spriteCutX; //start at SPRITE_SIZE so there is blank space for HUD on either side
	int y = spriteCutY;
	Vector2D location;

	while (!file.eof())
	{
		getline(file, row);

		//Check the line, character by character
		for (int i = 0; i < MAX_NUM_WALLS; i++)
		{
			char tmp = row[i];

			//Set the location to place a wall
			location.setX((float)x);
			location.setY((float)y);

			if (tmp == '0')
			{
				//Don't place a wall
			}
			else if (tmp == '1')
			{
				//Make "Animation"
				GraphicsBuffer* wallBuffer = Game::getInstance()->getGraphicsBufferManager()->getBuffer("wall");
				//Animation* wallAnimation = new Animation(1, 1, wallBuffer);
				Animation* wallAnimation = new Animation(spriteCutX, spriteCutY, spriteRows, spriteColumns, wallBuffer);
				wallAnimation->changeAnimationState();

				vector<Animation*>animList;
				animList.push_back(wallAnimation);

				//Make the Wall Unit
				Game::getInstance()->getUnitManager()->createUnit(location, animList);
			}
			else if (tmp == 'P')
			{
				//set Player start location
				Game::getInstance()->getPlayer()->setLocation(location);
			}
			else if (tmp == 'E')
			{
				//set Enemy start location
				Game::getInstance()->getEnemyManager()->createEnemy(location, spriteCutX, spriteCutY);
			}

			x += spriteCutX;
		}

		//Reset for the next line and move down a row
		y += spriteCutY;
		x = spriteCutX;
	}

	file.close();
}