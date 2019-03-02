#include "IListener.h"

void IListener::StartEventListening(Constants::EVENT_TYPE event_type) {
	EventManager::AddListener(this, event_type); 
}
