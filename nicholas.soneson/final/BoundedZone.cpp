#include "BoundedZone.h"

using namespace std;

BoundedZone::BoundedZone(int maxX, int maxY, int minX, int minY)
{
	mXAxis.setX(minX);
	mXAxis.setY(maxX);

	mYAxis.setX(minY);
	mYAxis.setY(maxY);
}

void BoundedZone::updateBoundedZone(int xLoc, int yLoc, int spriteWidth, int spriteHeight)
{
	int maxX = (xLoc + spriteWidth);
	int maxY = (yLoc + spriteHeight);
	int minX = xLoc;
	int minY = yLoc;

	mXAxis.setX(minX);
	mXAxis.setY(maxX);

	mYAxis.setX(minY);
	mYAxis.setY(maxY);
}
