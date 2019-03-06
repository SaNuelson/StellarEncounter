#ifndef SE_CHARACTER
#define SE_CHARACTER

#include <vector>
#include "Components.h"
#include "EntityManager.h"
#include "ExceptionManager.h"

class Component;
class UID;

class Character
{
public:
	Character();
	~Character();

	void AddComponent(std::shared_ptr<Component> ptr);

private:

	std::vector<std::shared_ptr<Component>> Components;

};

#endif