#pragma once
#include "Animation.h"
#include "BoundedZone.h"

class Unit : public Trackable
{
public:
	Unit() { mCurrentAnimation = 0; };
	Unit(Vector2D location, vector<Animation*> animList);
	~Unit();

	virtual void shot() {}; //used for how subclasses should handle being shot by a Bullet

	void updateUnit(double gameSpeed); //adjusts state of Unit (call Animation's update())
	void drawUnit(); //draw the current animation's sprite in the location of the unit
	void modifyAnimationSpeed(double speedModifier); //Modify the Animation speed for all Animations in mpAnimList
	void setBoundedZone(); //sets mBoundedZone

	Animation* getAnimation() { return mpAnimList[mCurrentAnimation]; }; //returns current Animation
	Vector2D getLocation() { return mLocation; };
	BoundedZone* getBoundedZone() { return mBoundedZone; };
	//bool getDeleteFlag() { return mMarkForDelete; };

	void setAnimationList(vector<Animation*> animList) { mpAnimList = animList; };
	void setAnimation(int animationNumber); //switch to a new Animation from mpAnimList
	void setLocation(Vector2D location) { mLocation = location; };
	//void markForDelete() { mMarkForDelete = true; };

	vector<Animation*> getUnitAnimList() { return mpAnimList; };

private:
	Vector2D mLocation; // x and y location of the unit
	int mCurrentAnimation; //the currently set Animation for the Unit
	vector<Animation*> mpAnimList; //hold the Unit's different Animations
	BoundedZone* mBoundedZone;
	//bool mMarkForDelete = false;
};
