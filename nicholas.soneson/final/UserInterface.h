#pragma once
#include "Trackable.h"
#include "Font.h"
#include "Color.h"
#include <sstream>

class UserInterface : public Trackable
{
public:
	UserInterface();
	~UserInterface();

	void updateUI();
	void drawUI();
private:
	Font* mpFont;
	Color* mpColorWhite;

	stringstream mEnemyHealth;
	stringstream mActivePowerup;
	stringstream mPlayerHealth;
	stringstream mScore;
	stringstream mBodyArmor;
	stringstream mEndState;
};
