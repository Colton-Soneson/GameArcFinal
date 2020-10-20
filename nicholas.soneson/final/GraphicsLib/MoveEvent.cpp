#include "MoveEvent.h"


/*
	When we construct it like this, by passing the type right into it, we dont leave it by chance
	You make move event, its a MOVE_EVENT
*/
MoveEvent::MoveEvent(const Vector2D& loc)
	:Event(MOVE_EVENT)
	, mLoc(loc)
{
}

MoveEvent::~MoveEvent()
{
}