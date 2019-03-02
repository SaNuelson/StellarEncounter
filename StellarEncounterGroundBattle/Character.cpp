#include "Character.h"

Character::Character()
{
	std::vector<Component*> Components;
}


Character::~Character()
{
}

void Character::AddComponent(Component * comp) { 
	Components.push_back(comp); 
}

void Character::ReceiveEvent(UID, Event) {}
