#ifndef SE_EVENT
#define SE_EVENT

#include "stdlibs.h"
#include "UID.h"
#include "Constants.h"

class Event {

public:

	Event();;
	~Event();;

	UID * caller;
	Constants::EVENT_TYPE event_type;
	std::vector<std::string> args;

private:



};

#endif