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

	InfoComponent IC;
	HealthComponent HC;
	ShieldComponent SC;
	AttribComponent AC;
	StatComponent SC;
	EquipComponent EC;
	RenderComponent RC;

};

/*

+ HealthComponent
? ShieldComponent
? AttribComponent (base)
+ StatComponent
? EquipComponent
+ RenderComponent

*/

#endif