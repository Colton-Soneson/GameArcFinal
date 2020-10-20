#pragma once
#include "Unit.h"

class UnitManager : public Trackable
{
	friend class Game;

public:

	Unit* getUnit(int position) { return mUnitList[position]; };
	vector<Unit*> getUnitList() { return mUnitList; };
	int getNumUnits() { return mUnitList.size(); };
	Unit* getLastUnit() { return mUnitList.back(); };

	void addUnit(Unit* unit); //add a premade Unit to the list
	void createUnit(Vector2D location, vector<Animation*> animList); //create a Unit and add it to the list
	void deleteUnit(Vector2D mousePos); //delete Unit that is at the given location

	void clear(); //delete all Units

	void update(double gameSpeed); //update all Units in mUnitList
	void draw(); //draw all Units in mUnitList

	bool unitExists(); //return whether there any Units created

private:

	//Private so only Game can make a UnitManager
	UnitManager();
	~UnitManager();

	vector<Unit*> mUnitList; //holds all Units that need to be updated within gameLoop()
};