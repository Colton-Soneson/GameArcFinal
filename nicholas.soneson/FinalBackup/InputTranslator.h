#pragma once

#include "EventListener.h"
#include <Trackable.h>

class EventSystem;

using namespace std;

class InputTranslator : public EventListener
{
public:
	InputTranslator();
	~InputTranslator();

	void initInputTranslator();
	void cleanupInputTranslator();

	void handleEvent(const Event& theEvent);

private:
	static int msID;
	int mID;
};
