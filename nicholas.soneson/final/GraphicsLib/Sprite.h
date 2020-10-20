#pragma once


#include "Trackable.h"

//SFML
#include <SFML/Graphics.hpp>

using namespace std;

class Sprite : public Trackable
{
public:


	friend class GraphicsSystem;
	friend class GraphicsBuffer;

	Sprite(GraphicsBuffer* buffer, int sourceLocX, int sourceLocY, int width, int height);
	~Sprite();

	//accessors
	int getSourceLocX() { return mSourceLocX; }
	int getSourceLocY() { return mSourceLocY; }

	int getHeight() { return mHeight; }
	int getWidth() { return mWidth; }
	GraphicsBuffer* getBuffer() { return mGraphicsBuffer; }

private:
	int mHeight;
	int mWidth;
	int mSourceLocX;
	int mSourceLocY;
	GraphicsBuffer* mGraphicsBuffer;

	int* mSourceLocation;	//Im not sure what to do for this

	sf::Sprite mSprite;
};