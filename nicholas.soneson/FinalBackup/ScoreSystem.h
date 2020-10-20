#pragma once
#include "Trackable.h"

class ScoreSystem : public Trackable
{
public:
	ScoreSystem() { mScore = 0; };
	~ScoreSystem() {};

	int getScore() { return mScore; };
	void setScore(int score) { mScore = score; };
	void addToScore(int score) { mScore += score; };
private:
	int mScore; //current score for the game
};
