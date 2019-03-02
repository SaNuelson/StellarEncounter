#ifndef SE_COMPONENTS
#define SE_COMPONENTS

#include "Event.h"
#include "EntityManager.h"
#include "ExceptionManager.h"

class UID;
class IListener;

class Component : public std::enable_shared_from_this<Component> {
public:
	
	virtual std::shared_ptr<Component> GetPtr() = 0;

};

class HealthComponent : public Component {

public:

	HealthComponent(int HP, UID owner);

	int GetCurrentHealth();;
	int GetMaxHealth();;
	bool GetIsAlive();;

	// void ReceiveEvent(UID caller, Event e) override;

	std::shared_ptr<Component> GetPtr() override { return shared_from_this(); };

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

	std::shared_ptr<Component> GetPtr() override { return shared_from_this(); };

};

class ShieldComponent : public Component {

	ShieldComponent(int SP, UID owner);

	int CurrentSP;
	int MaxSP;
	UID ownerID;

	std::shared_ptr<Component> GetPtr() override { return shared_from_this(); };

};

class StatsComponent : public Component {

	std::shared_ptr<Component> GetPtr() override { return shared_from_this(); };

};

class EquipComponent : public Component {

	std::shared_ptr<Component> GetPtr() override { return shared_from_this(); };

};

class InfoComponent : public Component {

	InfoComponent(std::string name, std::string desc);;

	std::string Name;
	std::string Desc;

	std::shared_ptr<Component> GetPtr() override { return shared_from_this(); };

};

#endif