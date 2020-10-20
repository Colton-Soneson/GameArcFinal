#pragma once

#include "Vector2D.h"
#include "Trackable.h"
#include "Tumbleweed.h"


typedef Vector2D TumbleweedVectorLoc;

class TumbleweedManager : public Trackable
{
public:
	TumbleweedManager() {};
	~TumbleweedManager() { cleanup(); };

	void cleanup();	//the "clear all" function

	Tumbleweed* createAndManageTumbleweed(vector<Animation*> animations, const float scale, const float speed);
	void deleteTumbleweed(const TumbleweedVectorLoc& loc);
	void deleteTumbleweed(Tumbleweed* pTumbleweed);

	//have these just so we can tell ALL Units to be affected
	//void animationAdjustments(double animAdjustTime);
	//void animationState();
	Tumbleweed* getLastPlacedTumbleweed();

	bool TumbleweedExists();

	Tumbleweed* searchTumbleweed(const TumbleweedVectorLoc& loc);	//this should check the vector2d position with all vector2d position
	void removeMarkedDelete(); //remove all tumbleweeds that have been marked for deletion
	void checkBZCollision(BoundedZone* zone);
	void checkForPlayerCollision();

	void updateTumbleweed(double frameRate);

	Tumbleweed* getCurrentTumbleweed() { return mpCurrentTumbleweed; };
	vector<Tumbleweed*>* getTumbleweedVector() { return &mListOfTumbleweeds; };	//might have to be pointer not sure 
	Tumbleweed* getTumbleweed(int pos) { return mListOfTumbleweeds[pos]; };
	int getTotalNum() { return mListOfTumbleweeds.size(); };

	void tumbleWeedShot(Tumbleweed* tumbleweedPointer); //remove a shot tumbleweed from mListOfTumbleweeds
private:
	vector<Tumbleweed*> mListOfTumbleweeds;
	Tumbleweed* mpCurrentTumbleweed;

};
