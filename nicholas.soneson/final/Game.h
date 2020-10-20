#pragma once

#include <map>

#include "System.h"
#include "Timer.h"
#include "PerformanceTracker.h"
#include "Animation.h"
#include "Sound.h"
#include "SoundBuffer.h"
#include "Vector2D.h"
#include "UnitManager.h"
#include "GraphicsBufferManager.h"
#include "InputTranslator.h"
#include "TumbleweedManager.h"
#include "BulletManager.h"

#include "GameEvent.h"
#include "EventSystem.h"
#include "Player.h"
#include "Level.h"
#include "EnemyManager.h"
#include "Menu.h"
#include "DataLoader.h"
#include "SaveSystem.h"
#include "LanguageSelect.h"
#include "PowerupManager.h"
#include "UserInterface.h"
#include "ScoreSystem.h"

class Game : public EventListener
{
public:

	static void initInstance() { mpInstance = new Game; };
	static void cleanupInstance();
	static Game* getInstance() { return mpInstance; };
	
	void initGame();
	void cleanupGame();

	//Initializer helper functions
	void createSystem();  //create System (mpSystem)
	void createInputTranslator(); //create InputTranslator (mpInputTranslator)
	void createManagers(); //create all managers (e.g. UnitManager)
	void createGraphicsBuffers(); //create all GraphicsBuffers
	void createFirstLevel(); //create  mpCurrentLevel and initialize first level
	void createBackground(); //create and set the background

	DataLoader* getDataLoader() { return mpDataLoader; };
	SaveSystem* getSaveSystem() { return mpSaveSystem; };
	LanguageSelect* getLanguageSystem() { return mpLanguageSelect; };

	System* getSystem() { return mpSystem; };
	UnitManager* getUnitManager() { return mpUnitManager; };
	GraphicsBufferManager* getGraphicsBufferManager() { return mpGraphicsBufferManager; };
	EnemyManager* getEnemyManager() { return mpEnemyManager; };
	TumbleweedManager* getTumbleweedManager() { return mpTumbleweedManager; };
	BulletManager* getBulletManager() { return mpBulletManager; };
	PowerupManager* getPowerupManager() { return mpPowerupManager; };
	ScoreSystem* getScoreSystem() { return mpScoreSystem; };

	void handleEvent(const Event &theEvent);
	void makeListener(); //set all the events Game needs to listen for

	void gameLoop(); //get user input, adjust game state, draw current state
	void getUserInput();
	void drawCurrentGameState();

	void setBackground(Sprite* background) { mpBackground = background; };

	Font* getFont() { return mpFont; };

	//Menu
	void toggleMenuState() { mInMenu = !mInMenu; };
	void displayMenu();

	void startGameFromBeginning();
	void startGameFromLoad();

	void checkForEndState();


	//spawning stuff
	bool chanceOfSpawn(float spawnRate);	//returns true to spawn something, the lower the rate the lower the chance of spawn
	void tumbleSpawnHandler(float spawnRate);

	//Player
	void initPlayer();
	Player* getPlayer() { return mpPlayer; };

	//Levels
	Level* getCurrentLevel() { return mpCurrentLevel; };
	void setCurrentLevel(Level* level) { mpCurrentLevel = level; };

	//shooting
	void shootingHandler(EightDirectional direction);

	//play area
	BoundedZone* getPlayArea() { return mpPlayArea; };

private:

	//Make class Static
	static Game* mpInstance;
	Game();
	~Game();

	DataLoader* mpDataLoader;
	SaveSystem* mpSaveSystem;
	LanguageSelect* mpLanguageSelect;

	InputTranslator* mpInputTranslator;

	System* mpSystem;
	UnitManager* mpUnitManager;
	GraphicsBufferManager* mpGraphicsBufferManager;
	TumbleweedManager* mpTumbleweedManager;
	BulletManager* mpBulletManager;
	PowerupManager* mpPowerupManager;
	UserInterface* mpUserInterface;
	ScoreSystem* mpScoreSystem;

	Sprite* mpBackground;
	Vector2D mBackgroundLoc; //(0,0) = default
	
	Vector2D mMousePosition;

	bool mKeepLooping = true;
	double mGameSpeed;
	double mWaitForShot = 100.0; //REMEMBER THIS FOR SHOOTING

	Player* mpPlayer;
	EnemyManager* mpEnemyManager;
	Level* mpCurrentLevel;
	Menu* mpMenu;

	BoundedZone* mpPlayArea;

	Font* mpFont;
	bool mInMenu = true;

	//OurSoundBuffer* mpShotBuffer;
	//OurSound* mpShotSound;

};
