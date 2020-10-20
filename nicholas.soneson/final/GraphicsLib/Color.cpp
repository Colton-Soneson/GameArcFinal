#include "Color.h"

Color::Color(unsigned char r, unsigned char g, unsigned char b)
{
	//mColor = al_map_rgb(r, g, b); //al_map_rgb() https://www.allegro.cc/manual/5/al_map_rgb
	mRed = r;
	mGreen = g;
	mBlue = b;
}

Color::~Color()
{
	//Nothing to destroy
}