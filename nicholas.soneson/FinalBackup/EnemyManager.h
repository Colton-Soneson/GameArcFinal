#pragma once
#include "Enemy.h"

class EnemyManager : public Trackable
{
	friend class Game;

public:

	Enemy* getEnemy(int position) { return mEnemyList[position]; };
	vector<Enemy*>* getEnemyList() { return &mEnemyList; };
	int getNumEnemies() { return mEnemyList.size(); };

	bool checkIfAllEnemiesKilled();

	void createEnemy(Vector2D location, int spriteCutX, int spriteCutY); //create and manage a new Enemy
	void clear(); //delete all Enemies

	void update(double gameSpeed); //update all Enemies in mEnemyList
	void draw(); //draw all Enemies in mEnemyList

	void removeDeadEnemies();

	void adjustEnemyDirection(Enemy* enemy);

	void setDifficulty(bool hardMode); //modify enemies based on difficulty

private:

	//Private so only Game can make an EnemyManager
	EnemyManager();
	~EnemyManager();

	vector<Enemy*> mEnemyList; //holds all Enemies
};
