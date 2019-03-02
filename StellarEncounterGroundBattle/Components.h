#ifndef SE_COMPONENTS
#define SE_COMPONENTS

#include "stdlibs.h"
#include "UID.h"
#include "Event.h"
#include "IListener.h"
#include "EntityManager.h"
#include "ExceptionManager.h"

class Component : public IListener{

};

class HealthComponent : public Component {

public:

	HealthComponent(int HP, UID owner);

	int GetCurrentHealth();;
	int GetMaxHealth();;
	bool GetIsAlive();;

	void ReceiveEvent(UID caller, Event e) override;

private:

	UID ownerID;

	void OwnerDied();

	int CurrentHP;
	int MaxHP;
	bool IsAlive;

	// EventReceiverMethods

	void ReceiveDamage(int amount);;

	void HealDamage(int amount);

};

class ArmorComponent : public Component {

	ArmorComponent(int AP, UID owner);

	int CurrentAP;
	int MaxAP;
	UID ownerID;

};

class ShieldComponent : public Component {

	ShieldComponent(int SP, UID owner);

	int CurrentSP;
	int MaxSP;
	UID ownerID;
};

class StatsComponent : public Component {

};

class EquipComponent : public Component {

};

class InfoComponent : public Component {

	InfoComponent(std::string name, std::string desc);;

	std::string Name;
	std::string Desc;

};

#endif