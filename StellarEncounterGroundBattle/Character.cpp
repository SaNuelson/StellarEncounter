#include "Character.h"

Character::Character()
{
	std::vector<Component> Components;
}


Character::~Character()
{
}

void Character::AddComponent(std::shared_ptr<Component> ptr)
{
	Components.push_back(ptr);
}

// void Character::ReceiveEvent(UID, Event) {}
