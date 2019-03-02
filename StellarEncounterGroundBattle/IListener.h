#ifndef SE_ILISTENER
#define SE_ILISTENER

#include "Event.h"
#include "EventManager.h"
#include "Constants.h"

class IListener {

public:
	void StartEventListening(Constants::EVENT_TYPE event_type);

	virtual void ReceiveEvent(UID caller, Event e) = 0;

};

#endif