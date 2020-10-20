#include "UserInterface.h"
#include "Game.h"

UserInterface::UserInterface()
{
	mpFont = Game::getInstance()->getFont();
	mpColorWhite = new Color(255, 255, 255);
}

UserInterface::~UserInterface()
{
	delete mpColorWhite;
}

void UserInterface::updateUI()
{
	//Reset stringstreams
	mEnemyHealth.str("");
	mActivePowerup.str("");
	mPlayerHealth.str("");
	mScore.str("");
	mBodyArmor.str("");
	mEndState.str("");

	//Player Health
	mPlayerHealth << Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(16) << ": " << Game::getInstance()->getPlayer()->getHealth();

	if (Game::getInstance()->getPlayer()->getHealth() < 0)
	{
		mEndState << Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(20);
	}

	if (Game::getInstance()->getEnemyManager()->checkIfAllEnemiesKilled() == true && Game::getInstance()->getCurrentLevel()->getNextLevelPath() == "$ENDGAME$" && Game::getInstance()->getPlayer()->getHealth() >= 0)
	{
		mEndState << Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(21) << "		" << Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(14) << ": " << Game::getInstance()->getScoreSystem()->getScore();
	}


	//Enemy Health
	for (int i = 0; i < Game::getInstance()->getEnemyManager()->getNumEnemies(); i++)
	{
		int health = Game::getInstance()->getEnemyManager()->getEnemy(i)->getHealth();
		mEnemyHealth << Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(17) << " " << i + 1 << ": " << health << "\t";
	}

	//Active Powerup
	if (Game::getInstance()->getPowerupManager()->getSpawnPowerups())
	{
		string powerup;
		switch (Game::getInstance()->getPlayer()->getActivePowerupType())
		{
		case Powerup::BOOTS:
			powerup = "Boots (SPD+)";
			break;
		case Powerup::BODY_ARMOR:
			powerup = "Body Armor";
			break;
		case Powerup::LARGE_BULLETS:
			powerup = "BigBullet (DMG+)";
			break;
		case Powerup::GUN:
			powerup = "Gun (SHT SPD+)";
			break;
		case Powerup::EXTRA_LIFE:
			powerup = "Extra Life";
			break;
		case Powerup::NUM_POWERUPS:
			powerup = Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(8);
			break;
		}
		mActivePowerup << Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(15) << ": " << powerup;
	}

	//Score
	mScore << Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(14) << ": "<< Game::getInstance()->getScoreSystem()->getScore();

	//Body Armor
	string armorState = Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(8); //"off"
	if (Game::getInstance()->getPlayer()->getBodyArmor())
		armorState = Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(7); //"on"

	mBodyArmor << "Armor: " << armorState;
}

void UserInterface::drawUI()
{
	//Player Health
	int playerXLoc = Game::getInstance()->getDataLoader()->getSpriteCutX() / 4;
	int playerYLoc = Game::getInstance()->getDataLoader()->getSpriteCutY() / 4;
	Game::getInstance()->getSystem()->getGraphicsSystem()->currentWriteText(playerXLoc, playerYLoc, *mpFont, *mpColorWhite, mPlayerHealth.str());

	//Enemy Health
	int enemyXLoc = Game::getInstance()->getDataLoader()->getSpriteCutX();
	int enemyYLoc = Game::getInstance()->getDataLoader()->getDisplayHeight() - (Game::getInstance()->getDataLoader()->getSpriteCutY() / 2) - (mpFont->getSize() / 2);
	Game::getInstance()->getSystem()->getGraphicsSystem()->currentWriteText(enemyXLoc, enemyYLoc, *mpFont, *mpColorWhite, mEnemyHealth.str());

	//Active Powerup
	if (Game::getInstance()->getPowerupManager()->getSpawnPowerups())
	{
		int powerupXLoc = (Game::getInstance()->getDataLoader()->getDisplayWidth() / 4);
		int powerupYLoc = (Game::getInstance()->getDataLoader()->getSpriteCutY() / 4);
		Game::getInstance()->getSystem()->getGraphicsSystem()->currentWriteText(powerupXLoc, powerupYLoc, *mpFont, *mpColorWhite, mActivePowerup.str());
	}

	//Score
	int scoreXLoc = (Game::getInstance()->getDataLoader()->getDisplayWidth() / 8) * 6;
	int scoreYLoc = (Game::getInstance()->getDataLoader()->getSpriteCutY() / 4);
	Game::getInstance()->getSystem()->getGraphicsSystem()->currentWriteText(scoreXLoc, scoreYLoc, *mpFont, *mpColorWhite, mScore.str());

	//Body Armor
	int armorXLoc = (Game::getInstance()->getDataLoader()->getDisplayWidth()) - (mpFont->getSize() * mBodyArmor.str().length());
	int armorYLoc = Game::getInstance()->getDataLoader()->getDisplayHeight() - (Game::getInstance()->getDataLoader()->getSpriteCutY() / 2) - (mpFont->getSize() / 2);
	Game::getInstance()->getSystem()->getGraphicsSystem()->currentWriteText(armorXLoc, armorYLoc, *mpFont, *mpColorWhite, mBodyArmor.str());

	int finishXLoc = (Game::getInstance()->getDataLoader()->getDisplayWidth() / 2);
	int finishYLoc = (Game::getInstance()->getDataLoader()->getDisplayHeight() / 2);
	Game::getInstance()->getSystem()->getGraphicsSystem()->currentWriteText(finishXLoc, finishYLoc, *mpFont, *mpColorWhite, mEndState.str());
}
