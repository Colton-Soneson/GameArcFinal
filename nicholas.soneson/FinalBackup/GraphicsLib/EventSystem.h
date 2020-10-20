#pragma once

#include <map>
#include <Trackable.h>

class Event;
class EventListener;
enum EventType;

using namespace std;

class EventSystem:public Trackable
{
public:
	/*
		In assignment five, this should actually be made into a static class (IN PROCESS)
	*/
	static EventSystem* getInstance();

	static void initInstance();
	static void cleanupInstance();

	
	void fireEvent( const Event& theEvent );							//does all the plumbing, it doesn't know what order its gonna do it in, dont count on order
	void addListener( EventType type, EventListener* pListener );		//you have to add yourself for all types you are interested in
	void removeListener( EventType type, EventListener* pListener );	
	void removeListenerFromAllEvents( EventListener* pListener );

private:

	EventSystem();
	~EventSystem();
	static EventSystem* mpsInstance;
	
	
	multimap< EventType, EventListener* > mListenerMap;

	void dispatchAllEvents( const Event& theEvent );

};

