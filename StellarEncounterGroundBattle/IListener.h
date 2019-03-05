#ifndef SE_ILISTENER
#define SE_ILISTENER

#include "Event.h"
#include "EventManager.h"
#include "Constants.h"

// interface for listening to events, couldn't make it work, maybe will work in SEUI with less things to worry about.

class IListener {

public:
	void StartEventListening(Constants::EVENT_TYPE event_type);

	virtual void ReceiveEvent(UID caller, Event e) = 0;

};

#endif