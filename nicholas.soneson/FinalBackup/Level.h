#pragma once
#include "BoundedZone.h"
#include "Trackable.h"

#include <string>
#include <fstream>

using namespace std;

class Level : public Trackable
{
public:
	Level(const string& levelPath) { mLevelsPath = levelPath; };
	~Level();

	void initLevelData(const string& fileName); //loads level data (bounding zone)
	void buildLevel(const string& fileName); //places Walls

	BoundedZone* getBoundedZone() { return mpBoundedZone; };
	BoundedZone* getPlayableZone() { return mpPlayableZone; };

	string getLevelsPath() { return mLevelsPath; };
	string getNextLevelPath() { return mNextLevelData; };
	string getLevelFileName() { return mLevelFileName; };

private:
	BoundedZone* mpBoundedZone;
	BoundedZone* mpPlayableZone;
	string mLevelFileName;
	string mLevelsPath;
	string mNextLevelData;
};
