#include "EventManager.h"

std::map<Constants::EVENT_TYPE, std::vector<IListener*>> EventManager::EventListeners;

void EventManager::AddListener(IListener * listener, Constants::EVENT_TYPE event_type) {
	EventListeners[event_type].push_back(listener);
}

void EventManager::InvokeEvent(UID caller, Event e) {
	for (auto listener : EventListeners[e.event_type]) {
		listener->ReceiveEvent(caller, e);
	}
}
