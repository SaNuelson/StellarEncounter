#ifndef SE_CHARACTER
#define SE_CHARACTER

#include <vector>
#include "IListener.h"
#include "Components.h"
#include "EntityManager.h"
#include "ExceptionManager.h"

class Component;
class UID;
class Event;

class Character
{
public:
	Character();
	~Character();

	void AddComponent(std::shared_ptr<Component> ptr);

	// void ReceiveEvent(UID, Event) override;

private:

	std::vector<std::shared_ptr<Component>> Components;

};

#endif