#pragma once

//SFML
#include <SFML/Graphics.hpp>

#include "Trackable.h"


using namespace std;


class Font : public Trackable
{
public:
	
	friend class GraphicsSystem;
	
	Font(const string& filename, int size);
	~Font();

	//accessors
	int getSize() { return mSize; }

private:
	int mSize; //size for the font
	string mFontFilename;
	//ALLEGRO_FONT* mCourFont;

	sf::Font mCourFont;
};