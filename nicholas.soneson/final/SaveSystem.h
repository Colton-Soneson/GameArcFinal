#pragma once
#include <string>
#include <fstream>

using namespace std;

class SaveSystem
{
public:
	SaveSystem(const string& dataFile);
	~SaveSystem() {};

	void saveGameState();

	void saveBullets();
	void saveEnemy();
	void savePlayer();
	void saveTumbleweeds();
	void savePowerUps();
	void saveScore();
	void saveLevel();

	
	void loadGameState();

	void loadBullets();
	void loadEnemy();
	void loadPlayer();
	void loadTumbleweeds();
	void loadPowerUps();
	void loadScore();
	void loadLevel();

private:

	string mFileName;
	ofstream* mpOutputFile;
	ifstream* mpInputFile;

	int mAmountOfBullets;
	int mAmountOfTumbleweeds;
	int mAmountOfPowerUps;
};
