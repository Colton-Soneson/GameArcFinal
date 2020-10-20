#pragma once

//SFML
#include <SFML/Graphics.hpp>


#include "Trackable.h"

using namespace std;

struct Color : public Trackable
{
	friend class GraphicsSystem;

	int mRVal;
	int mGVal;
	int mBVal;

	Color(int x, int y, int z)
	{
		mRVal = x;
		mGVal = y;
		mBVal = z;
	}

	~Color() {};

	int getRVal() { return mRVal; }
	int getGVal() { return mGVal; }
	int getBVal() { return mBVal; }

	sf::Color getColor()
	{
		sf::Color col;
		col.r = mRVal;
		col.g = mGVal;
		col.b = mBVal;
		return col;
	}

	/*
	ALLEGRO_COLOR getColor()
	{
		//return al_map_rgb(mRVal, mGVal, mBVal);
	}
	*/

	
};