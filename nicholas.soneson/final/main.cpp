/*
	I, Ben Nicholas, certify that all the following code is my own, original work unless credited.
	Received help from Colton Soneson regarding Event handling (InputTranslator and InputSystem).
*/

#include <iostream>
#include <cassert>
#include <string>
#include <time.h>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include "Game.h"
#include "Unit.h"

using namespace std;

int main()
{
	{
		srand (time(NULL));
		//Create EventSystem instance
		EventSystem::initInstance();
		EventSystem* eventSystem = EventSystem::getInstance();

		//Create the Game Instance
		Game::initInstance();
		Game* ptr = Game::getInstance();

		//Initialize the Game
		ptr->initGame();

		//Run the Game Loop
		ptr->gameLoop();

		//Cleanup the instances when done
		Game::cleanupInstance();
		eventSystem->cleanupInstance();
	}

	MemoryTracker::getInstance()->reportAllocations(cout);
	system("pause");

	return 0;
}