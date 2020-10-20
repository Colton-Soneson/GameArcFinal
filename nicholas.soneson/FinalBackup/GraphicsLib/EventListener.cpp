#include "EventListener.h"
#include "EventSystem.h"

EventListener::EventListener(EventSystem* pEventSystem)
	:mpEventSystem(pEventSystem)
{
}

EventListener::~EventListener()
{
		mpEventSystem->removeListenerFromAllEvents( this );	//if you are an event listener and get destroyed, it goes into the event system and REMOVES IS
															//this is how you get around the delete problem. More complex but a lot safer
}
