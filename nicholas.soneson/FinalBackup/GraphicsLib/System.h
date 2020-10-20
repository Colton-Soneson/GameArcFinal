#pragma once

#include "GraphicsSystem.h"
#include "InputSystem.h"
#include "SoundSystem.h"

using namespace std;


class System : public Trackable
{
	//getting keystates
	//getting mouse states
	//graphics system
public:
	System(int widthOfDisplay, int heightOfDisplay);		
	~System();

	void init();		
	void cleanup();		

	//Vector2D getMousePosition();	//passes the accessible vector
	//int getMouseState();
	//int getKeyState();		//passes out the enum value of the key

	GraphicsSystem* getGraphicsSystem() { return mpGraphicsSystem; }
	InputSystem* getInputSystem() { return mpInputSystem; };
	SoundSystem* getSoundSystem() { return mpSoundSystem; };

private:

	//ALLEGRO_MOUSE_STATE mMouseState;

	//ALLEGRO_KEYBOARD_STATE mKeyboardState;	

	GraphicsSystem* mpGraphicsSystem;

	InputSystem* mpInputSystem;
	
	SoundSystem* mpSoundSystem;

};