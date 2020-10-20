#pragma once

#include "Color.h"
#include "Trackable.h"

//SFML
#include <SFML/Graphics.hpp>


using namespace std;


class GraphicsBuffer : public Trackable
{
public:
	
	//SFML hopefully a win
	friend class Sprite;

	//old
	friend class GraphicsSystem;	
	friend class GraphicsBufferManager;

	//accessors
	int getHeight() { return mHeight; }
	int getWidth() { return mWidth; }

	sf::Texture getTexture() { return mTexture; }
	

private:	

	//constructors
	GraphicsBuffer(const string& filename);
	GraphicsBuffer(int width, int height, Color col);
	GraphicsBuffer(sf::Texture &bitmap);					//dont do this, make a clone function instead that manually sets everything
	GraphicsBuffer();
	~GraphicsBuffer();

	int mHeight;
	int mWidth;
	int mCol;
	//ALLEGRO_BITMAP* mBitmap;	

	sf::Texture mTexture;

	//CREATE A PRIVATE FUNCTION FOR A GRAPHICS BUFFER DESTRUCTOR WHICH TAKES IN THE DISPLAY BITMAP (WHICH IT DOESN"T OWN), TO CHECK THIS PASS 
	//IN A BOOL THAT STATES WEATHER OR NOT THE GRAPHICS BUFFER IS A DISPLAY BITMAP
};