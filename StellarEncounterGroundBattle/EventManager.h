#ifndef SE_EVENT_MANAGER
#define SE_EVENT_MANAGER

#include "stdlibs.h"
#include "EntityManager.h"
#include "WindowManager.h"
#include "UID.h"
#include "IListener.h"
#include "Constants.h"

class IListener;
class Event;

class EventManager
{
public:

	static void AddListener(IListener * listener, Constants::EVENT_TYPE event_type);

	static void InvokeEvent(UID caller, Event e);
	
private:
	
	static std::map<Constants::EVENT_TYPE, std::vector<IListener*>> EventListeners;

};

#endif