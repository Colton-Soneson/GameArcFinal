#pragma once

#include <string>
#include <trackable.h>

using namespace std;

/*
	every event listener registers for the type of events 
	subject only has to fire events
	we use EventTypes for user to register what events they are interested in
*/

enum EventType
{
	INVALID_EVENT_TYPE = -1,
	MOVE_EVENT,
	ESCAPE_EVENT,
	SPACE_EVENT,
	ENTER_EVENT,
	F_KEY_EVENT,
	W_KEY_EVENT,
	A_KEY_EVENT,
	S_KEY_EVENT,
	D_KEY_EVENT,
	UP_ARROW_EVENT,
	DOWN_ARROW_EVENT,
	LEFT_ARROW_EVENT,
	RIGHT_ARROW_EVENT,
	UP_RIGHT_EVENT,
	UP_LEFT_EVENT,
	DOWN_RIGHT_EVENT,
	DOWN_LEFT_EVENT,
	NUM_EVENT_TYPES
};

const string EVENT_NAMES[NUM_EVENT_TYPES] =	{	"Move Event",
												"Escape Event",
												"Space Event",
												"Enter Event",
												"F Key Event",
												"W Key Event",
												"A Key Event",
												"S Key Event",
												"D Key Event",
												"Up Arrow Event",
												"Down Arrow Event",
												"Left Arrow Event",
												"Right Arrow Event",
												"Up Right Arrow Event",
												"Up Left Arrow Event",
												"Down Right Arrow Event",
												"Down Left Arrow Event"
											};

class Event:public Trackable
{
public:
	Event( EventType type );
	virtual ~Event();

	EventType getType() const { return mType; };
	const string& getEventName() const;

private:
	//everyone has an event type
	EventType mType;

};