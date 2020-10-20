#pragma once

#include "GraphicsBuffer.h"
#include "Font.h"
#include "Sprite.h"

#include "Vector2D.h"

//SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Trackable.h"


using namespace std;

class GraphicsSystem : public Trackable
{
public:
	
	//i think we need this to access the display for mouse pos
	//friend class InputSystem;

	//Constructor/Destructor
	GraphicsSystem(int widthOfDisplay, int heightOfDisplay);				
	~GraphicsSystem();

	void init();	//initialize stuff
	void cleanup();	//cleanup stuff

	void CreateDisplay();
	void Rest(double restTime);

	//Accessors
	int getHeight() { return mHeight; }
	int getWidth() { return mWidth; }
	//GraphicsBuffer getGraphicsBuffer() { return mBBGraphicsBuffer; }

	//Flip
	void Flip();

	//could be static or non-static
	void currentGraphicsBufferDraw(int tarLocX, int tarLocY, Sprite* imageSprite, float scale);		//might want both of these to be same thing
	void givenGraphicsBufferDraw(GraphicsBuffer& backBuffer, int tarLocX, int tarLocY, Sprite* imageSprite, float scale);
	void currentWriteText(int tarLocX, int tarLocY, Font givenFont, Color givenCol, string givenText);
	void givenWriteText(GraphicsBuffer& backBuffer, int tarLocX, int tarLocY, Font givenFont, Color givenCol, string givenText);
	void saveBuffer(GraphicsBuffer bufferToSave, const string& filename);		

	//my functions
	void saveBackBuffer(const string& filename);

	sf::RenderWindow* getWindow() { return &mWindow; }


private:
	int mHeight;
	int mWidth;

	int mTarLocX;
	int mTarLocY;

	sf::RenderWindow mWindow;
	//ALLEGRO_DISPLAY* mDisplay;		
	//ALLEGRO_BITMAP* mBackBuffer;
	
	//inline ALLEGRO_BITMAP* getBackBuffer() { return al_get_backbuffer(mDisplay); }

};