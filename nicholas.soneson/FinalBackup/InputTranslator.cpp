#include "InputTranslator.h"
#include "EventSystem.h"
#include "Event.h"

#include "MoveEvent.h"

#include "GameEvent.h"

int InputTranslator::msID = 0;

InputTranslator::InputTranslator()
	:EventListener(EventSystem::getInstance())
	, mID(msID)
{
	msID++; //increment the static ID (so each event has a unique ID)
}

InputTranslator::~InputTranslator()
{
	cleanupInputTranslator();
}

void InputTranslator::initInputTranslator()
{
	//Add InputTranslator as a listener for all the following events
	EventSystem::getInstance()->addListener(MOVE_EVENT, this);
	EventSystem::getInstance()->addListener(ESCAPE_EVENT, this);
	EventSystem::getInstance()->addListener(SPACE_EVENT, this);
	EventSystem::getInstance()->addListener(ENTER_EVENT, this);
	EventSystem::getInstance()->addListener(F_KEY_EVENT, this);
	EventSystem::getInstance()->addListener(S_KEY_EVENT, this);
	EventSystem::getInstance()->addListener(W_KEY_EVENT, this);
	EventSystem::getInstance()->addListener(A_KEY_EVENT, this);
	EventSystem::getInstance()->addListener(D_KEY_EVENT, this);
	EventSystem::getInstance()->addListener(UP_ARROW_EVENT, this);
	EventSystem::getInstance()->addListener(DOWN_ARROW_EVENT, this);
	EventSystem::getInstance()->addListener(LEFT_ARROW_EVENT, this);
	EventSystem::getInstance()->addListener(RIGHT_ARROW_EVENT, this);
	EventSystem::getInstance()->addListener(UP_RIGHT_EVENT, this);
	EventSystem::getInstance()->addListener(UP_LEFT_EVENT, this);
	EventSystem::getInstance()->addListener(DOWN_RIGHT_EVENT, this);
	EventSystem::getInstance()->addListener(DOWN_LEFT_EVENT, this);
}

void InputTranslator::cleanupInputTranslator()
{
	//Nothing to cleanup
}

void InputTranslator::handleEvent(const Event &theEvent)
{
	//Misc
	if (theEvent.getType() == ESCAPE_EVENT)
	{
		EventSystem::getInstance()->fireEvent((EventType)EXIT_APP_EVENT);
	}
	if (theEvent.getType() == SPACE_EVENT)
	{
		//
	}
	if (theEvent.getType() == F_KEY_EVENT)
	{
		//
	}
	if (theEvent.getType() == ENTER_EVENT)
	{
		EventSystem::getInstance()->fireEvent((EventType)MENU_SELECT_EVENT);
	}
	

	//Player Movement
	if (theEvent.getType() == W_KEY_EVENT)
	{
		EventSystem::getInstance()->fireEvent((EventType)PLAYER_MOVE_UP_EVENT);
	}
	if (theEvent.getType() == S_KEY_EVENT)
	{
		EventSystem::getInstance()->fireEvent((EventType)PLAYER_MOVE_DOWN_EVENT);
	}
	if (theEvent.getType() == A_KEY_EVENT)
	{
		EventSystem::getInstance()->fireEvent((EventType)PLAYER_MOVE_LEFT_EVENT);
	}
	if (theEvent.getType() == D_KEY_EVENT)
	{
		EventSystem::getInstance()->fireEvent((EventType)PLAYER_MOVE_RIGHT_EVENT);
	}

	//player shooting
	if (theEvent.getType() == UP_ARROW_EVENT)
	{
		EventSystem::getInstance()->fireEvent((EventType)PLAYER_SHOOT_UP_EVENT);
	}
	if (theEvent.getType() == DOWN_ARROW_EVENT)
	{
		EventSystem::getInstance()->fireEvent((EventType)PLAYER_SHOOT_DOWN_EVENT);
	}
	if (theEvent.getType() == LEFT_ARROW_EVENT)
	{
		EventSystem::getInstance()->fireEvent((EventType)PLAYER_SHOOT_LEFT_EVENT);
	}
	if (theEvent.getType() == RIGHT_ARROW_EVENT)
	{
		EventSystem::getInstance()->fireEvent((EventType)PLAYER_SHOOT_RIGHT_EVENT);
	}

	if (theEvent.getType() == UP_RIGHT_EVENT)
	{
		EventSystem::getInstance()->fireEvent((EventType)PLAYER_SHOOT_UP_RIGHT_EVENT);
	}
	if (theEvent.getType() == UP_LEFT_EVENT)
	{
		EventSystem::getInstance()->fireEvent((EventType)PLAYER_SHOOT_UP_LEFT_EVENT);
	}
	if (theEvent.getType() == DOWN_RIGHT_EVENT)
	{
		EventSystem::getInstance()->fireEvent((EventType)PLAYER_SHOOT_DOWN_RIGHT_EVENT);
	}
	if (theEvent.getType() == DOWN_LEFT_EVENT)
	{
		EventSystem::getInstance()->fireEvent((EventType)PLAYER_SHOOT_DOWN_LEFT_EVENT);
	}
}