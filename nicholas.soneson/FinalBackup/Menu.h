#pragma once
#include "Color.h"

enum MenuItem
{
	MENU_START,
	MENU_LOAD,
	MENU_OPTIONS,
	MENU_EXIT,
	MENU_OPTIONS_DIFFICULTY,
	MENU_OPTIONS_SOUND,
	MENU_OPTIONS_SELECT_LANGUAGE,
	MENU_OPTIONS_POWERUPS,
	MENU_OPTIONS_GO_BACK
};

class Menu
{
public:

	const int  MAX_MAIN_NUM_ITEMS = 4;
	const int  MAX_OPTIONS_NUM_ITEMS = 5;

	const int MAX_LANGUAGES_NUM_ITEMS = 3;
	const int MAX_SOUND_NUM_ITEMS = 2;
	const int MAX_DIFFICULTY_NUM_ITEMS = 2;
	const int MAX_POWERUPS_NUM_ITEMS = 2;

	const int SPACING_ONE = 30;


	Menu();
	~Menu() { cleanup(); };

	void cleanup();

	void draw();
	void moveUp();
	void moveDown();

	void adjustState();

	MenuItem getCurrentMainMenuItem() { return (MenuItem)mMainSelectedItemIndex; };
	MenuItem getCurrentOptionsMenuItem() { return (MenuItem)(mOptionsSelectedItemIndex + MAX_MAIN_NUM_ITEMS); };
	bool getCurrentMenu() { return mCurrentMenu; };

	void toggleCurrentMenu() { mCurrentMenu = !mCurrentMenu; };
	bool getPlayerEnters() { return mPlayerEnters; };
	void setPlayerEnters(bool active) { mPlayerEnters = active; };

	void setCurrentSoundState();
	void setCurrentDifficultyState();
	void setCurrentPowerUpsState();
	void setCurrentLanguage();

	int getCurrentSoundState() { return mCurrentSoundState; };
	int getCurrentDifficultyState() { return mCurrentDifficultyState; };
	int getCurrentPowerUpsState() { return mCurrentPowerUpsState; };
	int getCurrentLanguage() { return mCurrentLanguage; };

	void reloadLanguage();

private:
	
	int mMainSelectedItemIndex;
	int mOptionsSelectedItemIndex;

	bool mCurrentMenu; //true is main menu, false is options menu
	int mCurrentSoundState;
	int mCurrentDifficultyState;
	int mCurrentPowerUpsState;
	int mCurrentLanguage;

	//int mMenuCount[2];

	string mMenuItems[4];
	string mOptionsItems[5];
	string mLanguagesItems[3];
	string mDifficultyItems[2];
	string mSoundItems[2];
	string mPowerUpsItems[2];


	Color* mSelectedColor; //red
	Color* mInactiveColor;

	Color* mOptionsSelectedColor;
	Color* mOptionsInactiveColor;

	bool mPlayerEnters;	//basically its set true by the handler in game.cpp, then back to false at the end of adjust state
};
