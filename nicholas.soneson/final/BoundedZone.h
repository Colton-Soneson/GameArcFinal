#pragma once

#include "Vector2D.h"
#include "Trackable.h"

using namespace std;

class BoundedZone : public Trackable
{
public:
	BoundedZone(int maxX, int maxY, int minX, int minY);
	~BoundedZone() {};

	void updateBoundedZone(int xLoc, int yLoc, int spriteWidth, int spriteHeight);

	Vector2D getAxisX() { return mXAxis; }
	Vector2D getAxisY() { return mYAxis; }

private:
	Vector2D mXAxis;
	Vector2D mYAxis;
};