#include "GraphicsSystem.h"

using namespace std;

//constructor
GraphicsSystem::GraphicsSystem(int widthOfDisplay, int heightOfDisplay)
{
	mHeight = heightOfDisplay;
	mWidth = widthOfDisplay;

}

//destructor
GraphicsSystem::~GraphicsSystem()
{
	cleanup();
}

//initializes allegro systems
void GraphicsSystem::init()
{
	/*
	if (!al_init())
	{
		cout << "error initting Allegro\n";
		//return 1;
	}
	if (!al_init_image_addon())
	{
		cout << "error - Image Add-on not initted\n";
		//return 1;
	}
	if (!al_init_font_addon())
	{
		cout << "error - Font Add-on not initted\n";
		//return 1;
	}
	if (!al_init_ttf_addon())
	{
		cout << "error - TTF Add-on not initted\n";
		//return 1;
	}
	if (!al_init_primitives_addon())
	{
		cout << "error - primitives Add-on not initted\n";
		//return 1;
	}
	if (!al_install_audio())
	{
		cout << "error - Audio Add-on not initted\n";
		//return 1;
	}
	if (!al_init_acodec_addon())
	{
		cout << "error - Audio Codec Add-on not initted\n";
		//return 1;
	}
	if (!al_reserve_samples(1))
	{
		cout << "error - samples not reserved\n";
		//return 1;
	}
	*/
}

//cleanup allegro systems
void GraphicsSystem::cleanup()
{
	//al_destroy_display(mDisplay);

	/*
	//Shutdown section
	al_shutdown_font_addon();
	al_shutdown_ttf_addon();
	al_shutdown_image_addon();
	al_shutdown_primitives_addon();

	//uninstall
	al_uninstall_audio();
	al_uninstall_system();
	*/
}


void GraphicsSystem::CreateDisplay()
{
	//create the display
	//mDisplay = al_create_display(mWidth, mHeight);
	//assert(mDisplay);

	//set a pointer for backbuffer 
	//mBackBuffer = al_get_backbuffer(mDisplay);

	//mpWindow->setSize(sf::Vector2u(mWidth, mHeight));
	//mpWindow->setTitle("SFML WORKS!");
	//mpWindow->display();
	//sf::RenderWindow window(sf::VideoMode(mWidth, mHeight), "SFML works!");
	//window.display();

	//mpWindow->create(sf::VideoMode(mWidth, mHeight, 32), "SFML WORKS!", sf::Style::Close);
	//mpWindow->display();

	mWindow.create(sf::VideoMode(mWidth, mHeight), "SFML works!");
}


void GraphicsSystem::Rest(double restTime)
{
	//al_rest(restTime);
}

//draws sprite to current buffer
void GraphicsSystem::currentGraphicsBufferDraw(int tarLocX, int tarLocY, Sprite* imageSprite, float scale)
{
	//the width and hieght of the sprite
	int sourceWidth = imageSprite->getWidth();
	int sourceHeight = imageSprite->getHeight();

	//the top left corner of the sprite
	int sourceLocX = imageSprite->getSourceLocX();
	int sourceLocY = imageSprite->getSourceLocY();

	//draw the sprite
	//al_draw_scaled_bitmap(imageSprite->mGraphicsBuffer->mBitmap, sourceLocX, sourceLocY, sourceWidth, sourceHeight, tarLocX, tarLocY, (sourceWidth*scale), (sourceHeight*scale), 0); 

	//----------------SFML-----------------
	imageSprite->mSprite.setScale(sf::Vector2f(scale, scale));
	
	imageSprite->mSprite.setTextureRect(sf::IntRect(sourceLocX, sourceLocY, sourceWidth, sourceHeight));

	imageSprite->mSprite.setPosition(sf::Vector2f((float)tarLocX, (float)tarLocY));
	mWindow.draw(imageSprite->mSprite);
}

//draws sprite to supplied buffer bitmap
void GraphicsSystem::givenGraphicsBufferDraw(GraphicsBuffer& backBuffer, int tarLocX, int tarLocY, Sprite* imageSprite, float scale)
{
	//create a prior bitmap to target
	//ALLEGRO_BITMAP* priorBitmap = al_get_target_bitmap();
	
	//the width and hieght of the sprite
	int sourceWidth = imageSprite->getWidth();
	int sourceHeight = imageSprite->getHeight();

	//the top left corner of the sprite
	int sourceLocX = imageSprite->getSourceLocX();
	int sourceLocY = imageSprite->getSourceLocY();

	//draw the sprite
	//al_draw_scaled_bitmap(imageSprite->mGraphicsBuffer->mBitmap, sourceLocX, sourceLocY, sourceWidth, sourceHeight, tarLocX, tarLocY, (sourceWidth*scale), (sourceHeight*scale), 0);
	
	//set back to prior
	//al_set_target_bitmap(priorBitmap);

}

//writes text to the current buffer
void GraphicsSystem::currentWriteText(int tarLocX, int tarLocY, Font givenFont, Color givenCol, string givenText)
{
	//al_draw_text(givenFont.mCourFont, givenCol.getColor(), tarLocX, tarLocY, ALLEGRO_ALIGN_CENTER, givenText.c_str());

	sf::Text text;

	// select the font
	text.setFont(givenFont.mCourFont); // font is a sf::Font

	// set the string to display
	text.setString(givenText);

	// set the character size
	text.setCharacterSize(givenFont.getSize()); // in pixels, not points!

	// set the color
	text.setFillColor(givenCol.getColor());

	// set the text style
	text.setStyle(sf::Text::Bold);

	// set the location of the text (position)
	sf::Vector2f location((float)tarLocX, (float)tarLocY);
	text.setPosition(location);

	mWindow.draw(text);
}


//writes text to a supplied buffer
void GraphicsSystem::givenWriteText(GraphicsBuffer& backBuffer, int tarLocX, int tarLocY, Font givenFont, Color givenCol, string givenText)
{
	//give pointer to back
	//ALLEGRO_BITMAP* priorBitmap = al_get_target_bitmap();

	//write to graphicsBuffer
	//al_set_target_bitmap(backBuffer.mBitmap);
	//al_draw_text(givenFont.mCourFont, givenCol.getColor(), tarLocX, tarLocY, ALLEGRO_ALIGN_CENTER, givenText.c_str());

	//go back to previous pointer
	//al_set_target_bitmap(priorBitmap);
}


//we have to do a save print out for the red buffer and a save for the backbuffer
void GraphicsSystem::saveBuffer(GraphicsBuffer bufferToSave, const string& filename)
{
	//al_save_bitmap(filename.c_str(), bufferToSave.mBitmap);
}


//saves only the back buffer
void GraphicsSystem::saveBackBuffer(const string& filename)
{
	//al_save_bitmap(filename.c_str(), getBackBuffer());
}

//flips the display
void GraphicsSystem::Flip()
{
	//al_flip_display();

	//sfml
	mWindow.display();
}