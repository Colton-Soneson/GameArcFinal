#include "Player.h"
#include "Game.h"

Player::Player(Vector2D location, vector<Animation*> animList)
{
	setLocation(location);
	setAnimationList(animList);
	setAnimation(0);

	mStartingMoveSpeed = Game::getInstance()->getDataLoader()->getPlayerMoveSpeed();
	mMoveSpeed = mStartingMoveSpeed;
	mTmpMoveSpeed = mMoveSpeed;

	mHealth = Game::getInstance()->getDataLoader()->getPlayerHealth();
	mPlayerDamage = Game::getInstance()->getDataLoader()->getPlayerDamage();
	
	mTargetTime = Game::getInstance()->getDataLoader()->getActivePowerupTimer();
	mPowerupTimer = mTargetTime;

	mActivePowerup = Powerup::NUM_POWERUPS;
}

void Player::movePlayer(Direction direction)
{
	Vector2D location = getLocation();
	float locationX = location.getX();
	float locationY = location.getY();

	//Vertical
	if (direction == UP)
	{
		location.setY(locationY -= mMoveSpeed);
	}
	if (direction == DOWN)
	{
		location.setY(locationY += mMoveSpeed);
	}

	//Horizontal
	if (direction == LEFT)
	{
		location.setX(locationX -= mMoveSpeed);
	}
	if (direction == RIGHT)
	{
		location.setX(locationX += mMoveSpeed);
	}
	setLocation(location); //update the players location

	checkIfInPlayZone();
	vector<Unit*> unitList = Game::getInstance()->getUnitManager()->getUnitList();
	for (unsigned int i = 0; i < unitList.size(); i++)
	{
		checkCollision(unitList[i]->getBoundedZone());
	}

	checkPowerupCollision();
}

void Player::checkIfInPlayZone()
{
	BoundedZone* boundedZone = Game::getInstance()->getCurrentLevel()->getPlayableZone();

	Vector2D location = getLocation();
	float locationX = location.getX();
	float locationY = location.getY();
 	
	if (getBoundedZone()->getAxisX().getY() + mMoveSpeed >= boundedZone->getAxisX().getY()) //Right
	{
		//cout << "\nZONE HALT RIGHT";
		location.setX(locationX - mMoveSpeed);
		setLocation(location);
		mMoveSpeed = 0;
	}
	else if (getBoundedZone()->getAxisX().getX() - mMoveSpeed <= boundedZone->getAxisX().getX()) //Left
	{
		//cout << "\nZONE HALT LEFT";
		location.setX(locationX + mMoveSpeed);
		setLocation(location);
		mMoveSpeed = 0;
	}
	else if (getBoundedZone()->getAxisY().getX() - mMoveSpeed <= boundedZone->getAxisY().getX()) //Top
	{
		//cout << "\nZONE HALT UP";
		location.setY(locationY + mMoveSpeed);
		setLocation(location);
		mMoveSpeed = 0;
	}
	else if (getBoundedZone()->getAxisY().getY() + mMoveSpeed >= boundedZone->getAxisY().getY()) //Bottom
	{
		//cout << "\nZONE HALT DOWN";
		location.setY(locationY - mMoveSpeed);
		setLocation(location);
		mMoveSpeed = 0;
	}
	else
	{
		mMoveSpeed = mTmpMoveSpeed;
	}
}

void Player::checkCollision(BoundedZone* objZone)
{
	Vector2D location = getLocation();
	float locationX = location.getX();
	float locationY = location.getY();
	
	if (objZone->getAxisY().getX() <= getBoundedZone()->getAxisY().getY() && objZone->getAxisY().getY() >= getBoundedZone()->getAxisY().getX() &&
		 objZone->getAxisX().getX() <= getBoundedZone()->getAxisX().getY() + mMoveSpeed && objZone->getAxisX().getY() >= getBoundedZone()->getAxisX().getX() + mMoveSpeed
		) //collision on right side of Player
	{
		//cout << " COLLISION ON RIGHT";
		location.setX(locationX - (mMoveSpeed));
		setLocation(location);
		mMoveSpeed = 0;
	}
	else if (objZone->getAxisY().getX() <= getBoundedZone()->getAxisY().getY() && objZone->getAxisY().getY() >= getBoundedZone()->getAxisY().getX() &&
		objZone->getAxisX().getX() <= getBoundedZone()->getAxisX().getY() - mMoveSpeed && objZone->getAxisX().getY() >= getBoundedZone()->getAxisX().getX() - mMoveSpeed
		) //collision on left side of Player
	{
		//cout << " COLLISION ON LEFT";
		location.setX(locationX + (mMoveSpeed));
		setLocation(location);
		mMoveSpeed = 0;
	}
	else if (objZone->getAxisY().getX() <= getBoundedZone()->getAxisY().getY() - mMoveSpeed && objZone->getAxisY().getY() >= getBoundedZone()->getAxisY().getX() - mMoveSpeed &&
		objZone->getAxisX().getX() <= getBoundedZone()->getAxisX().getY() && objZone->getAxisX().getY() >= getBoundedZone()->getAxisX().getX()
		) //collision on top side of Player
	{
		//cout << " COLLISION ON TOP";
		location.setY(locationY + (mMoveSpeed));
		setLocation(location);
		mMoveSpeed = 0;
	}
	else if (objZone->getAxisY().getX() <= getBoundedZone()->getAxisY().getY() + mMoveSpeed && objZone->getAxisY().getY() >= getBoundedZone()->getAxisY().getX() + mMoveSpeed &&
		objZone->getAxisX().getX() <= getBoundedZone()->getAxisX().getY() && objZone->getAxisX().getY() >= getBoundedZone()->getAxisX().getX()
		) //collision on bottom side of Player
	{
		//cout << " COLLISION ON BOTTOM";
		location.setY(locationY - (mMoveSpeed));
		setLocation(location);
		mMoveSpeed = 0;
	}
	else
	{
		mMoveSpeed = mTmpMoveSpeed;
	}
}

void Player::checkPowerupCollision()
{
	if (Game::getInstance()->getPowerupManager()->powerupPresent()) //check that there is a powerup first
	{
		BoundedZone* objZone = Game::getInstance()->getPowerupManager()->getPowerup()->getBoundedZone();

		if (objZone->getAxisY().getX() <= getBoundedZone()->getAxisY().getY() && objZone->getAxisY().getY() >= getBoundedZone()->getAxisY().getX() &&
			objZone->getAxisX().getX() <= getBoundedZone()->getAxisX().getY() && objZone->getAxisX().getY() >= getBoundedZone()->getAxisX().getX()
			)
		{
			Powerup::PowerupType type = Game::getInstance()->getPowerupManager()->getPowerup()->getPowerupType();

			cout << "\nCOLLIDED WITH POWERUP: " << type;
			Game::getInstance()->getPowerupManager()->removePowerup();

			//Apply the appropriate effect 
			switch (type)
			{
			case Powerup::BOOTS:
				mActivePowerup = Powerup::BOOTS;
				mMoveSpeed = Game::getInstance()->getDataLoader()->getBootsMoveSpeed();
				mTmpMoveSpeed = mMoveSpeed;
				break;
			case Powerup::BODY_ARMOR:
				mActivePowerup = Powerup::BODY_ARMOR;
				mBodyArmor = true;
				break;
			case Powerup::LARGE_BULLETS:
				mActivePowerup = Powerup::LARGE_BULLETS;
				mPlayerDamage = Game::getInstance()->getDataLoader()->getLargeBulletDamage();
				break;
			case Powerup::GUN:
				mActivePowerup = Powerup::GUN;
				//float fastDelay = ;
				Game::getInstance()->getDataLoader()->setBulletDelay(Game::getInstance()->getDataLoader()->getFastBulletDelay());
				break;
			case Powerup::EXTRA_LIFE:
				mActivePowerup = Powerup::EXTRA_LIFE;
				mHealth++;
				break;
			/*case Powerup::SHOTGUN:
				mActivePowerup = Powerup::SHOTGUN;
				break;*/
			}
		}
	}
}

void Player::updatePlayer(double gameSpeed)
{
	handlePowerup();
	updateUnit(gameSpeed);
}

void Player::handlePowerup()
{
	if (mActivePowerup != Powerup::NUM_POWERUPS) //only count down timer when a powerup is set
		mPowerupTimer -= Game::getInstance()->getDataLoader()->getGameSpeed();

	if (mPowerupTimer <= 0)
	{
		//Reset whatever stat was affected (Bodyarmor is removed when shot, Extra Lives don't get removed until killed)
		switch (mActivePowerup)
		{
		case Powerup::BOOTS:
			mMoveSpeed = mStartingMoveSpeed;
			mTmpMoveSpeed = mMoveSpeed;
			break;
		case Powerup::LARGE_BULLETS:
			//FILL IN;
			mPlayerDamage = Game::getInstance()->getDataLoader()->getPlayerDamage();
			break;
		case Powerup::GUN:
			//float normalDelay = Game::getInstance()->getDataLoader()->getNormalBulletDelay();
			Game::getInstance()->getDataLoader()->setBulletDelay(Game::getInstance()->getDataLoader()->getNormalBulletDelay());
			break;
		/*case Powerup::SHOTGUN:
			break;*/
		}

		//Reset
		mActivePowerup = Powerup::NUM_POWERUPS;
		mPowerupTimer = mTargetTime;
	}
}

void Player::shot()
{
	if (mBodyArmor == true)
	{
		mBodyArmor = false;
	}
	else
	{
		mHealth--;
	}
}
