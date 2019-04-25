#include "GameObject.h"
#include "Tilemap.h"

bool GameObject::isEnemy() { return false; }

std::string GameObject::toString()
{
	return "GameObject::BaseClass";
}

GameObject * GameObject::getPtr() { return this; }
