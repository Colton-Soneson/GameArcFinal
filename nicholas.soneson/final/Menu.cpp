#include "Menu.h"
#include "Game.h"

Menu::Menu()
{
	mMainSelectedItemIndex = 0;
	mOptionsSelectedItemIndex = 0;
	mCurrentMenu = true;

	mCurrentSoundState = 0;
	mCurrentDifficultyState = 0;
	mCurrentPowerUpsState = 0;
	mCurrentLanguage = 0;

	reloadLanguage();

	mSelectedColor = new Color(255, 0, 0); //red
	mInactiveColor = new Color(255, 255, 255); //white

	mOptionsSelectedColor = new Color(255, 0, 0); //red
	mOptionsInactiveColor = new Color(255, 255, 255); //white
}

void Menu::cleanup()
{
	delete mSelectedColor;
	delete mInactiveColor;

	delete mOptionsInactiveColor;
	delete mOptionsSelectedColor;
}

void Menu::reloadLanguage()
{
	//main menu
	mMenuItems[0] = Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(0);	//PLAY
	mMenuItems[1] = Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(1);	//LOAD
	mMenuItems[2] = Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(2);	//OPTIONS
	mMenuItems[3] = Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(3);	//QUIT

	//options
	mOptionsItems[0] = Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(4);		//DIFFICULTY
	mOptionsItems[1] = Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(9);		//SOUND
	mOptionsItems[2] = Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(10);	//SELECT LANGUAGE
	mOptionsItems[3] = Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(13);	//POWERUPS
	mOptionsItems[4] = Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(18);	//GO BACK

	//difficulty
	mDifficultyItems[0] = Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(5);	//EASY
	mDifficultyItems[1] = Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(6);	//HARD

	//language
	mLanguagesItems[0] = Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(11);	//ENGLISH
	mLanguagesItems[1] = Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(12);	//SPANISH
	mLanguagesItems[2] = Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(19);	//TEELANG


	//sound
	mSoundItems[0] = Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(7);	//ON
	mSoundItems[1] = Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(8);	//OFF

	//powerups
	mPowerUpsItems[0] = Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(7);	//ON
	mPowerUpsItems[1] = Game::getInstance()->getLanguageSystem()->getWordAtKeysIndex(8);	//OFF
}

void Menu::setCurrentSoundState()
{
	if (mCurrentSoundState == MAX_SOUND_NUM_ITEMS - 1)
	{
		mCurrentSoundState = 0;
	}
	else
	{
		mCurrentSoundState++;
	}
}
void Menu::setCurrentDifficultyState()
{
	if (mCurrentDifficultyState == MAX_DIFFICULTY_NUM_ITEMS - 1)
	{
		mCurrentDifficultyState = 0;
	}
	else
	{
		mCurrentDifficultyState++;
	}
}
void Menu::setCurrentPowerUpsState()
{
	if (mCurrentPowerUpsState == MAX_POWERUPS_NUM_ITEMS - 1)
	{
		mCurrentPowerUpsState = 0;
	}
	else
	{
		mCurrentPowerUpsState++;
	}
}
void Menu::setCurrentLanguage()
{
	if (mCurrentLanguage == MAX_LANGUAGES_NUM_ITEMS - 1)
	{
		mCurrentLanguage = 0;
	}
	else
	{
		mCurrentLanguage++;
	}
}

void Menu::draw()
{
	int xLoc = Game::getInstance()->getDataLoader()->getDisplayWidth() / 2;
	int xLocOpt = Game::getInstance()->getDataLoader()->getDisplayWidth() / 24;
	int xLocOptionsOne = (Game::getInstance()->getDataLoader()->getDisplayWidth() / 6) + (Game::getInstance()->getDataLoader()->getDisplayWidth() / 6);
	int xLocOptionsTwo = (Game::getInstance()->getDataLoader()->getDisplayWidth() / 6) +  (Game::getInstance()->getDataLoader()->getDisplayWidth() / 3);
	int xLocOptionsThree = (Game::getInstance()->getDataLoader()->getDisplayWidth() / 6) +  (Game::getInstance()->getDataLoader()->getDisplayWidth() / 2);
	int yLoc;

	Font* font = Game::getInstance()->getFont();
	Color* color;
	Color* subColor;

	//Draw each MenuItem
	if (mCurrentMenu)
	{
		for (int i = 0; i < MAX_MAIN_NUM_ITEMS; i++)
		{
			yLoc = Game::getInstance()->getDataLoader()->getDisplayHeight() / (MAX_MAIN_NUM_ITEMS + 1) * (i + 1);

			if (i == mMainSelectedItemIndex) //use "selected" color if the current menu item is the currently selected one
			{
				color = mSelectedColor;
			}
			else
			{
				color = mInactiveColor;
			}

			Game::getInstance()->getSystem()->getGraphicsSystem()->currentWriteText(
				xLoc, yLoc, *font, *color, mMenuItems[i]);
		}
	}
	else
	{

		//options menu
		for (int i = 0; i < MAX_OPTIONS_NUM_ITEMS; i++)
		{
			yLoc = Game::getInstance()->getDataLoader()->getDisplayHeight() / (MAX_OPTIONS_NUM_ITEMS + 1) * (i + 1);

			if (i == mOptionsSelectedItemIndex) //use "selected" color if the current menu item is the currently selected one
			{
				color = mSelectedColor;
			}
			else
			{
				color = mInactiveColor;
			}

			Game::getInstance()->getSystem()->getGraphicsSystem()->currentWriteText(
				xLocOpt, yLoc, *font, *color, mOptionsItems[i]);

			//-------------MINOR MENU--------------------
			if (i == 0)
			{
				for (int k = 0; k < MAX_DIFFICULTY_NUM_ITEMS; k++)
				{
					yLoc = Game::getInstance()->getDataLoader()->getDisplayHeight() / (MAX_OPTIONS_NUM_ITEMS + 1) * (i + 1);

					if (k == mCurrentDifficultyState) //use "selected" color if the current menu item is the currently selected one
					{
						subColor = mSelectedColor;
					}
					else
					{
						subColor = mInactiveColor;
					}

					if (k == 0)
					{
						Game::getInstance()->getSystem()->getGraphicsSystem()->currentWriteText(
							xLocOptionsOne, yLoc, *font, *subColor, mDifficultyItems[k]);
					}

					if (k == 1)
					{
						Game::getInstance()->getSystem()->getGraphicsSystem()->currentWriteText(
							xLocOptionsTwo, yLoc, *font, *subColor, mDifficultyItems[k]);
					}
				}
			}
			else if (i == 1)
			{
				for (int k = 0; k < MAX_SOUND_NUM_ITEMS; k++)
				{
					yLoc = Game::getInstance()->getDataLoader()->getDisplayHeight() / (MAX_OPTIONS_NUM_ITEMS + 1) * (i + 1);

					if (k == mCurrentSoundState) //use "selected" color if the current menu item is the currently selected one
					{
						subColor = mSelectedColor;
					}
					else
					{
						subColor = mInactiveColor;
					}

					if (k == 0)
					{
						Game::getInstance()->getSystem()->getGraphicsSystem()->currentWriteText(
							xLocOptionsOne, yLoc, *font, *subColor, mSoundItems[k]);
					}

					if (k == 1)
					{
						Game::getInstance()->getSystem()->getGraphicsSystem()->currentWriteText(
							xLocOptionsTwo, yLoc, *font, *subColor, mSoundItems[k]);
					}

				}
			}
			else if (i == 2)
			{
				for (int k = 0; k < MAX_LANGUAGES_NUM_ITEMS; k++)
				{
					yLoc = Game::getInstance()->getDataLoader()->getDisplayHeight() / (MAX_OPTIONS_NUM_ITEMS + 1) * (i + 1);

					if (k == mCurrentLanguage) //use "selected" color if the current menu item is the currently selected one
					{
						subColor = mSelectedColor;
					}
					else
					{
						subColor = mInactiveColor;
					}

					if (k == 0)
					{
						Game::getInstance()->getSystem()->getGraphicsSystem()->currentWriteText(
							xLocOptionsOne, yLoc, *font, *subColor, mLanguagesItems[k]);
					}

					if (k == 1)
					{
						Game::getInstance()->getSystem()->getGraphicsSystem()->currentWriteText(
							xLocOptionsTwo, yLoc, *font, *subColor, mLanguagesItems[k]);
					}

					if (k == 2)
					{
						Game::getInstance()->getSystem()->getGraphicsSystem()->currentWriteText(
							xLocOptionsThree, yLoc, *font, *subColor, mLanguagesItems[k]);
					}
				}
			}
			else if (i == 3)
			{
				for (int k = 0; k < MAX_POWERUPS_NUM_ITEMS; k++)
				{
					yLoc = Game::getInstance()->getDataLoader()->getDisplayHeight() / (MAX_OPTIONS_NUM_ITEMS + 1) * (i + 1);

					if (k == mCurrentPowerUpsState) //use "selected" color if the current menu item is the currently selected one
					{
						subColor = mSelectedColor;
					}
					else
					{
						subColor = mInactiveColor;
					}

					if (k == 0)
					{
						Game::getInstance()->getSystem()->getGraphicsSystem()->currentWriteText(
							xLocOptionsOne, yLoc, *font, *subColor, mPowerUpsItems[k]);
					}

					if (k == 1)
					{
						Game::getInstance()->getSystem()->getGraphicsSystem()->currentWriteText(
							xLocOptionsTwo, yLoc, *font, *subColor, mPowerUpsItems[k]);
					}
				}
			}
			else if (i == 4)
			{
				//do nothing
			}
			else
			{
				cout << "menu funk " << i << endl;
			}


		}

		
	}
	
}

void Menu::adjustState() //this is called before the draw function
{
	//if mMainSelectedItemIndex == x && mPlayerEnters == true
		//then do that items function

	/*
	if (mMainSelectedItemIndex == 0 && mPlayerEnters == true)
	{
		Game::getInstance()->toggleMenuState();

		Game::getInstance()->startGameFromBeginning();
	}

	if (mMainSelectedItemIndex == 1 && mPlayerEnters == true)
	{
		Game::getInstance()->toggleMenuState();

		Game::getInstance()->startGameFromLoad();
	}
	*/

	//after all is done, set mPlayerEnters = false
	mPlayerEnters = false;
	
	//cout << endl << mPlayerEnters;
}

void Menu::moveUp()
{
	if (mCurrentMenu)
	{
		if (mMainSelectedItemIndex == 0)
		{
			mMainSelectedItemIndex = MAX_MAIN_NUM_ITEMS - 1;
		}
		else
		{
			mMainSelectedItemIndex--;
		}
	}
	else
	{
		if (mOptionsSelectedItemIndex == 0)
		{
			mOptionsSelectedItemIndex = MAX_OPTIONS_NUM_ITEMS - 1;
		}
		else
		{
			mOptionsSelectedItemIndex--;
		}
	}
}

void Menu::moveDown()
{
	if (mCurrentMenu)
	{
		if (mMainSelectedItemIndex == MAX_MAIN_NUM_ITEMS - 1)
		{
			mMainSelectedItemIndex = 0;
		}
		else
		{
			mMainSelectedItemIndex++;
		}
	}
	else
	{
		if (mOptionsSelectedItemIndex == MAX_OPTIONS_NUM_ITEMS - 1)
		{
			mOptionsSelectedItemIndex = 0;
		}
		else
		{
			mOptionsSelectedItemIndex++;
		}
	}
}
