#include "System.h"

using namespace std;


System::System(int widthOfDisplay, int heightOfDisplay)
{
	mpGraphicsSystem = new GraphicsSystem(widthOfDisplay, heightOfDisplay);
	mpInputSystem = new InputSystem();
	mpSoundSystem = new SoundSystem();
}

System::~System()
{
	cleanup();
}

void System::init()
{
	mpGraphicsSystem->init();
	mpGraphicsSystem->CreateDisplay();

	mpInputSystem->init();
}

void System::cleanup()
{
	delete mpInputSystem;
	
	delete mpGraphicsSystem;
	
	delete mpSoundSystem;
}
