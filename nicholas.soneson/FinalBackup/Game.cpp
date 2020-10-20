#include "Game.h"

Game* Game::mpInstance = nullptr;

void Game::cleanupInstance()
{
	delete mpInstance;
}

Game::Game()
	:EventListener(EventSystem::getInstance())
{
	mpDataLoader = new DataLoader("GAME_DATA.txt");
	mpSaveSystem = new SaveSystem("SAVEGAME_DATA.txt");
	mpLanguageSelect = new LanguageSelect("Languages\\LanguageKeys.txt");
	mpLanguageSelect->loadLanguageFromFile("Languages\\English.txt");
	mGameSpeed = mpDataLoader->getGameSpeed(); 
	mBackgroundLoc = Vector2D(0, 0);
};

Game::~Game()
{
	cleanupGame();
	
	mBackgroundLoc = NULL;
	mGameSpeed = NULL;
}

void Game::initGame()
{

	mpFont = new Font((mpDataLoader->getAssetPath() + mpDataLoader->getFontFile()), 24);

	createSystem();
	createManagers();
	createGraphicsBuffers();
	createBackground();

	//Set up InputTranslator
	createInputTranslator();

	//Add what to listen for
	makeListener();

	displayMenu();

	//startGame();
}

void Game::cleanupGame()
{
	delete mpPlayer;
	delete mpCurrentLevel;
	delete mpMenu;

	//Delete Background
	delete mpBackground;

	//Cleanup Managers
	Game::getInstance()->mpUnitManager->clear();
	Game::getInstance()->mpGraphicsBufferManager->clear();

	//Delete Managers
	delete mpTumbleweedManager;
	delete mpEnemyManager;
	delete mpUnitManager;
	delete mpGraphicsBufferManager;
	delete mpBulletManager;
	delete mpPowerupManager;
	delete mpUserInterface;
	delete mpScoreSystem;
	delete mpInputTranslator;
	delete mpSystem;

	delete mpFont;
}

void Game::displayMenu()
{
	Game::getInstance()->getSystem()->getInputSystem()->setPressWithRelease(true);

	while (mInMenu && mpSystem->getGraphicsSystem()->getWindow()->isOpen() && mKeepLooping)
	{
		if (mpMenu == nullptr)
		{
			mpMenu = new Menu();
		}

		getUserInput();

		mpMenu->adjustState();

		mpMenu->draw();

		mpSystem->getGraphicsSystem()->Flip();

		//SFML this is the close window, we need to poll for this event otherwise the window app will crash in 5 seconds
		sf::Event event;
		while (mpSystem->getGraphicsSystem()->getWindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				mpSystem->getGraphicsSystem()->getWindow()->close();
		}

		//SFML clear the screen
		mpSystem->getGraphicsSystem()->getWindow()->clear();
	}
}

void Game::startGameFromBeginning()
{

	//Initialize the Player
	initPlayer();

	//Set the current level to the first level
	createFirstLevel();

	//play area
	mpPlayArea = new BoundedZone(mpDataLoader->getPlayZoneHigh(), mpDataLoader->getPlayZoneHigh(), mpDataLoader->getPlayZoneLow(), mpDataLoader->getPlayZoneLow());
}

void Game::startGameFromLoad()
{
	cout << "before load Game state";

	mpSaveSystem->loadGameState();

	//play area
	mpPlayArea = new BoundedZone(mpDataLoader->getPlayZoneHigh(), mpDataLoader->getPlayZoneHigh(), mpDataLoader->getPlayZoneLow(), mpDataLoader->getPlayZoneLow());

	
}


void Game::createSystem()
{
	if (mpSystem == nullptr)
	{
		Game::getInstance()->mpSystem = new System(mpDataLoader->getDisplayWidth(), mpDataLoader->getDisplayHeight());
		mpSystem->init();
	}
	
}

void Game::createInputTranslator()
{
	mpInputTranslator = new InputTranslator();
	mpInputTranslator->initInputTranslator();
}

void Game::createManagers()
{
	Game::getInstance()->mpGraphicsBufferManager = new GraphicsBufferManager();
	Game::getInstance()->mpUnitManager = new UnitManager();
	Game::getInstance()->mpEnemyManager = new EnemyManager();
	Game::getInstance()->mpTumbleweedManager = new TumbleweedManager();
	Game::getInstance()->mpBulletManager = new BulletManager();
	Game::getInstance()->mpPowerupManager = new PowerupManager();
	Game::getInstance()->mpUserInterface = new UserInterface();
	Game::getInstance()->mpScoreSystem = new ScoreSystem();
}

void Game::createGraphicsBuffers()
{
	Game::getInstance()->mpGraphicsBufferManager->createAndManage("background", (mpDataLoader->getAssetPath() + mpDataLoader->getBackgroundFile()));
	Game::getInstance()->mpGraphicsBufferManager->createAndManage("player", (mpDataLoader->getAssetPath() + mpDataLoader->getPlayerFile()));
	Game::getInstance()->mpGraphicsBufferManager->createAndManage("enemy", (mpDataLoader->getAssetPath() + mpDataLoader->getEnemyFile()));
	Game::getInstance()->mpGraphicsBufferManager->createAndManage("wall", (mpDataLoader->getAssetPath() + mpDataLoader->getWallFile()));
	Game::getInstance()->mpGraphicsBufferManager->createAndManage("tumble", (mpDataLoader->getAssetPath() + mpDataLoader->getTumbleweedFile()));
	Game::getInstance()->mpGraphicsBufferManager->createAndManage("bullet", (mpDataLoader->getAssetPath() + mpDataLoader->getBulletFile()));
	Game::getInstance()->mpGraphicsBufferManager->createAndManage("powerup", (mpDataLoader->getAssetPath() + mpDataLoader->getPowerupFile()));


	//mpShotBuffer = new OurSoundBuffer("assets/shot.wav");
	//mpShotSound = new OurSound(mpShotBuffer);

	mpSystem->getSoundSystem()->setSoundBuffer("assets/shot.wav");
}

void Game::createBackground()
{
	Vector2D upperLeft(0, 0); //Upper left of screen
	GraphicsBuffer* backgroundBuffer = Game::getInstance()->mpGraphicsBufferManager->getBuffer("background");
	//Sprite* backgroundSprite = new Sprite(backgroundBuffer, upperLeft, backgroundBuffer->getWidth(), backgroundBuffer->getHeight());
	Sprite* backgroundSprite = new Sprite(backgroundBuffer, upperLeft.getX(), upperLeft.getY(), backgroundBuffer->getWidth(), backgroundBuffer->getHeight());
	Game::getInstance()->setBackground(backgroundSprite);
}

void Game::makeListener()
{
	EventSystem::getInstance()->addListener((EventType)EXIT_APP_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)MENU_SELECT_EVENT, this);	//Enter
	
	EventSystem::getInstance()->addListener((EventType)PLAYER_MOVE_UP_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)PLAYER_MOVE_DOWN_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)PLAYER_MOVE_LEFT_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)PLAYER_MOVE_RIGHT_EVENT, this);

	EventSystem::getInstance()->addListener((EventType)PLAYER_SHOOT_UP_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)PLAYER_SHOOT_DOWN_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)PLAYER_SHOOT_LEFT_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)PLAYER_SHOOT_RIGHT_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)PLAYER_SHOOT_UP_RIGHT_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)PLAYER_SHOOT_UP_LEFT_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)PLAYER_SHOOT_DOWN_RIGHT_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)PLAYER_SHOOT_DOWN_LEFT_EVENT, this);
}

void Game::initPlayer()
{
	//Make Animations
	GraphicsBuffer* playerBuffer = Game::getInstance()->mpGraphicsBufferManager->getBuffer("player");
	//Animation* playerAnimation = new Animation(SPR_COLUMNS, SPR_ROWS, playerBuffer);
	Animation* playerAnimation = new Animation(mpDataLoader->getSpriteCutX(), mpDataLoader->getSpriteCutY(), mpDataLoader->getSpriteRows(), mpDataLoader->getSpriteColumns(), playerBuffer);
	//smurfAnimation->toggleAnimation();

	vector<Animation*>animList;
	animList.push_back(playerAnimation);

	//Make the Unit
	Vector2D tmp(500, 500);
	Game::getInstance()->mpPlayer = new Player(tmp, animList);
}

void Game::createFirstLevel()
{
	mpCurrentLevel = new Level(mpDataLoader->getLevelsPath());
	mpCurrentLevel->initLevelData("LEVEL_1_DATA.txt");
}

void Game::gameLoop()
{
	const string TRACKER_NAME = "loop";

	PerformanceTracker tracker;
	Timer theTimer;

	//InputSystem: go back to no release to active again
	Game::getInstance()->getSystem()->getInputSystem()->setPressWithRelease(false);
	
	while (mpSystem->getGraphicsSystem()->getWindow()->isOpen() && mKeepLooping)
	{
		Game::getInstance()->getSystem()->getInputSystem()->setPressWithRelease(false);


		tracker.clearTracker(TRACKER_NAME); //zero-out the tracker
		tracker.startTracking(TRACKER_NAME); //start tracking

		theTimer.start();
	
		//Get user input
		getUserInput();

		//Draw the current game state
		drawCurrentGameState();

		theTimer.sleepUntilElapsed(mGameSpeed); //sleep until stopwatch is at 16.7ms (time should be member variable in case framerate changes)
		tracker.stopTracking(TRACKER_NAME); //stop tracking

		//cout << "loop time: " << tracker.getElapsedTime(TRACKER_NAME) << endl; //output time to console 

		//SFML this is the close window, we need to poll for this event otherwise the window app will crash in 5 seconds
		sf::Event event;
		while (mpSystem->getGraphicsSystem()->getWindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				cout << endl << "Saving from Close" << endl;
				mpSaveSystem->saveGameState();
				mpSystem->getGraphicsSystem()->getWindow()->close();
			}
		}

		//SFML clear the screen
		mpSystem->getGraphicsSystem()->getWindow()->clear();
	}
}

void Game::getUserInput() //Store user inputs 
{
	mpSystem->getInputSystem()->update(mpSystem->getGraphicsSystem()->getWindow());
}

void Game::drawCurrentGameState()
{
	checkForEndState();

	mpSystem->getGraphicsSystem()->currentGraphicsBufferDraw(mBackgroundLoc.getX(), mBackgroundLoc.getY(), mpBackground, 1.0);

	tumbleSpawnHandler(mpDataLoader->getTumbleSpawnRate());
	Game::getInstance()->mpTumbleweedManager->checkBZCollision(mpPlayArea);
	Game::getInstance()->mpBulletManager->checkBZCollision(mpPlayArea);

	//Update each Unit
	Game::getInstance()->mpUnitManager->update(mGameSpeed);
	Game::getInstance()->mpEnemyManager->update(mGameSpeed);
	Game::getInstance()->mpTumbleweedManager->updateTumbleweed(mGameSpeed);
	Game::getInstance()->mpBulletManager->updateBullet(mGameSpeed);
	Game::getInstance()->mpPowerupManager->update(mGameSpeed);



	if (Game::getInstance()->mpPlayer != nullptr)
	{
		Game::getInstance()->mpPlayer->updatePlayer(mGameSpeed);
	}
	Game::getInstance()->mpUserInterface->updateUI();

	//Draw Background
	//mpSystem->getGraphicsSystem()->draw(mpBackground, mBackgroundLoc, 1.0);

	//Draw each Unit
	Game::getInstance()->mpUnitManager->draw();
	Game::getInstance()->mpEnemyManager->draw();
	if (Game::getInstance()->mpPlayer != nullptr)
	{
		Game::getInstance()->mpPlayer->drawUnit();
	}
	Game::getInstance()->mpPowerupManager->draw();
	Game::getInstance()->mpUserInterface->drawUI();

	//Refresh the display to see changes
	mpSystem->getGraphicsSystem()->Flip();
}

void Game::handleEvent(const Event &theEvent)
{
	//------------MOVEMENT--------------
	
	if (!mInMenu)
	{

		if (theEvent.getType() == PLAYER_MOVE_UP_EVENT)
		{
			//cout << "\n---UP---";
			Game::getInstance()->mpPlayer->movePlayer(UP);
		}
		if (theEvent.getType() == PLAYER_MOVE_DOWN_EVENT)
		{
			//cout << "\n---DOWN---";
			Game::getInstance()->mpPlayer->movePlayer(DOWN);
		}
		if (theEvent.getType() == PLAYER_MOVE_LEFT_EVENT)
		{
			//cout << "\n---LEFT---";
			Game::getInstance()->mpPlayer->movePlayer(LEFT);
		}
		if (theEvent.getType() == PLAYER_MOVE_RIGHT_EVENT)
		{
			//cout << "\n---RIGHT---";
			Game::getInstance()->mpPlayer->movePlayer(RIGHT);
		}


		//-----------SHOOTING-------------
		if (theEvent.getType() == PLAYER_SHOOT_UP_EVENT)
		{
			shootingHandler(E_TOP);
		}
		if (theEvent.getType() == PLAYER_SHOOT_DOWN_EVENT)
		{
			shootingHandler(E_DOWN);
		}
		if (theEvent.getType() == PLAYER_SHOOT_LEFT_EVENT)
		{
			shootingHandler(E_LEFT);
		}
		if (theEvent.getType() == PLAYER_SHOOT_RIGHT_EVENT)
		{
			shootingHandler(E_RIGHT);
		}

		if (theEvent.getType() == PLAYER_SHOOT_UP_RIGHT_EVENT)
		{
			shootingHandler(E_TOP_RIGHT);
		}
		if (theEvent.getType() == PLAYER_SHOOT_UP_LEFT_EVENT)
		{
			shootingHandler(E_TOP_LEFT);
		}
		if (theEvent.getType() == PLAYER_SHOOT_DOWN_RIGHT_EVENT)
		{
			shootingHandler(E_DOWN_RIGHT);
		}
		if (theEvent.getType() == PLAYER_SHOOT_DOWN_LEFT_EVENT)
		{
			shootingHandler(E_DOWN_LEFT);
		}
	}
	else
	{

		if (theEvent.getType() == PLAYER_SHOOT_UP_EVENT)
		{
			mpMenu->moveUp();
		}
		if (theEvent.getType() == PLAYER_SHOOT_DOWN_EVENT)
		{
			mpMenu->moveDown();
		}
		if (theEvent.getType() == MENU_SELECT_EVENT)
		{
			if (mpMenu->getCurrentMenu())
			{
				MenuItem currentMainSelection = mpMenu->getCurrentMainMenuItem();

				if (currentMainSelection == MENU_START)
				{
					mpMenu->setPlayerEnters(true);
					Game::getInstance()->toggleMenuState();
					Game::getInstance()->startGameFromBeginning();
				}
				else if (currentMainSelection == MENU_LOAD)
				{
					mpMenu->setPlayerEnters(true);
					Game::getInstance()->toggleMenuState();
					Game::getInstance()->startGameFromLoad();
				}
				else if (currentMainSelection == MENU_OPTIONS)
				{
					mpMenu->setPlayerEnters(true);
					mpMenu->toggleCurrentMenu();
				}
				else if (currentMainSelection == MENU_EXIT)
				{
					mKeepLooping = false;
				}
			}
			else
			{
				MenuItem currentOptionsSelection = mpMenu->getCurrentOptionsMenuItem();

				if (currentOptionsSelection == MENU_OPTIONS_DIFFICULTY)
				{
					mpMenu->setPlayerEnters(true);
					mpMenu->setCurrentDifficultyState();

					//bool hardMode = false;

					if (mpMenu->getCurrentDifficultyState() == 0)
					{
						//turn down hardness
						mpEnemyManager->setDifficulty(false);
					}

					if (mpMenu->getCurrentDifficultyState() == 1)
					{
						// turn up hardness
						//hardMode = true;
						mpEnemyManager->setDifficulty(true);
					}
				}
				else if (currentOptionsSelection == MENU_OPTIONS_SOUND)
				{
					mpMenu->setPlayerEnters(true);
					mpMenu->setCurrentSoundState();

					if (mpMenu->getCurrentSoundState() == 0)
					{
						//sound off
						mpSystem->getSoundSystem()->turnSoundOff(false);
						cout << endl << "sound is on";
					}

					if (mpMenu->getCurrentSoundState() == 1)
					{
						//sound on
						mpSystem->getSoundSystem()->turnSoundOff(true);
						cout << endl << "sound is off";
					}

				}
				else if (currentOptionsSelection == MENU_OPTIONS_SELECT_LANGUAGE)
				{
					mpMenu->setPlayerEnters(true);
					mpMenu->setCurrentLanguage();


					if (mpMenu->getCurrentLanguage() == 0)
					{
						//lang one
						mpLanguageSelect->loadLanguageFromFile("Languages\\English.txt");
						mpMenu->reloadLanguage();
						cout << endl << "English Lang Loaded";
					}

					if (mpMenu->getCurrentLanguage() == 1)
					{
						//lang two
						mpLanguageSelect->loadLanguageFromFile("Languages\\Spanish.txt");
						mpMenu->reloadLanguage();
						cout << endl << "Spanish Lang Loaded";
					}

					if (mpMenu->getCurrentLanguage() == 2)
					{
						//lang three
						mpLanguageSelect->loadLanguageFromFile("Languages\\Teelang.txt");
						mpMenu->reloadLanguage();
						cout << endl << "T Lang Loaded";
					}
				}
				else if (currentOptionsSelection == MENU_OPTIONS_POWERUPS)
				{
					mpMenu->setPlayerEnters(true);
					mpMenu->setCurrentPowerUpsState();

					if (mpMenu->getCurrentPowerUpsState()== 0)
					{
						mpPowerupManager->setPowerupSpawn(true);
						cout << endl << "Powers is on";

					}

					if (mpMenu->getCurrentPowerUpsState() == 1)
					{
						mpPowerupManager->setPowerupSpawn(false);
						cout << endl << "Powers is off";

					}

				}
				else if (currentOptionsSelection == MENU_OPTIONS_GO_BACK)
				{
					mpMenu->setPlayerEnters(true);
					mpMenu->toggleCurrentMenu();
				}
			}
		}
	}

	//----------MSC------------
	if (theEvent.getType() == EXIT_APP_EVENT)
	{
		cout << endl << "Saving from ESC" << endl;
		mpSaveSystem->saveGameState();
		mKeepLooping = false;
	}
}


void Game::shootingHandler(EightDirectional direction)
{

	mWaitForShot -= mpDataLoader->getGameSpeed();

	if (mWaitForShot <= 0.0)
	{

		//mpSystem->getSoundSystem()->playSingleSound(mpShotSound);
		//mpSystem->getSoundSystem()->playSingleSound("assets/shot.wav");
		//mpSystem->getSoundSystem()->playSingleSound(*mpShotBuffer);

		mpSystem->getSoundSystem()->playSingleSound();


		//shoot
		Animation* newBulletAnim = new Animation(mpDataLoader->getBulletCutX(), mpDataLoader->getBulletCutY(), mpDataLoader->getBulletRows(), mpDataLoader->getBulletColumns(), Game::getInstance()->getGraphicsBufferManager()->getBuffer("bullet"));
		vector<Animation*> animations;
		animations.push_back(newBulletAnim);
		int locX = mpPlayer->getLocation().getX() + (mpPlayer->getAnimation()->getCurrentSprite()->getWidth() * 0.5);
		int locY = mpPlayer->getLocation().getY() + (mpPlayer->getAnimation()->getCurrentSprite()->getHeight() * 0.5);
		Vector2D playerMid(locX, locY);
		Game::getInstance()->getBulletManager()->createAndManageBullet(animations, playerMid, 1.0, mpDataLoader->getBulletSpeed(), direction , false);

		//reset timer
		mWaitForShot = mpDataLoader->getBulletDelay();
	}
}

bool Game::chanceOfSpawn(float spawnRate)
{
	bool spawn = false;
	float randomChance = (rand() % 1000) + 0;

	if (randomChance < spawnRate)
	{
		spawn = true;
		//cout << "TUMBLE SPAWN";
	}

	return spawn;
}

void Game::tumbleSpawnHandler(float spawnRate)
{
	if (chanceOfSpawn(spawnRate))
	{
		Animation* newTumbleAnim = new Animation(mpDataLoader->getSpriteCutX(), mpDataLoader->getSpriteCutY(), mpDataLoader->getTumbleSpriteColumns(), mpDataLoader->getTumbleSpriteRows(), Game::getInstance()->getGraphicsBufferManager()->getBuffer("tumble"));
		vector<Animation*> animations;
		animations.push_back(newTumbleAnim);
		Game::getInstance()->getTumbleweedManager()->createAndManageTumbleweed(animations, 1.0, mpDataLoader->getTumbleSpeed());
	}
}

void Game::checkForEndState()
{
	if (mpEnemyManager->checkIfAllEnemiesKilled() == true && mpPlayer->getHealth() >= 0)
	{
		string tmp = mpCurrentLevel->getNextLevelPath();

		if (tmp != "$ENDGAME$")
		{
			//mpPlayer->setActivePowerupTypeByInt(5);
			mpUnitManager->clear();
			mpCurrentLevel = new Level(mpDataLoader->getLevelsPath());
			mpCurrentLevel->initLevelData(tmp);
		}
		else
		{
			static int waitTimer = 300;
			static bool delPlay = false;
			if (delPlay == false)
			{
				mpUnitManager->clear();
				mpEnemyManager->clear();
				delPlay = true;
			}

			if (waitTimer <= 0)
			{
				mKeepLooping = true;
				mInMenu = true;
				mpBulletManager->cleanup();
				mpUnitManager->clear();
				mpEnemyManager->clear();
				mpTumbleweedManager->cleanup();
				mpScoreSystem->setScore(0);
				//delete mpPlayer;
				//delete mpCurrentLevel;
				displayMenu();	//this may not work
			}
			else
			{
				waitTimer--;
			}

		}

	}

	if (Game::getInstance()->getPlayer()->getHealth() < 0)
	{
		static int waitTimer2 = 300;
		static bool delPlay = false;
		if (delPlay == false)
		{
			mpUnitManager->clear();
			mpEnemyManager->clear();
			delPlay = true;
		}


		if (waitTimer2 <= 0)
		{
			
			mKeepLooping = true;
			mInMenu = true;
			mpBulletManager->cleanup();
			mpUnitManager->clear();
			mpEnemyManager->clear();
			mpTumbleweedManager->cleanup();
			mpScoreSystem->setScore(0);
			//delete mpPlayer;
			//delete mpCurrentLevel;
			displayMenu();	//this may not work
		}
		else
		{
			waitTimer2--;
		}
	}
}