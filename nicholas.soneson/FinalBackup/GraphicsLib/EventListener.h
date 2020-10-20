#pragma once

#include <Trackable.h>

/*
	This is the observer (listeners are observers)
	there can be multiple event listeners all listening for the same thing happening
	You have to make things a subclass of this listener
*/

class Event;
class EventSystem;

class EventListener:public Trackable
{
public:
	EventListener(EventSystem* pEventSystem);
	virtual ~EventListener();

	//pure virtual functions mean that if you want to make an instance of this class, you have to make this function (forces the subclasses to do it)
	virtual void handleEvent( const Event& theEvent ) = 0;

private:
	EventSystem* mpEventSystem;//the event system this lister is listening to
protected:
	EventSystem * getEventSystem() const { return mpEventSystem; };
};