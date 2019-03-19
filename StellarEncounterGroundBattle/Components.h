#ifndef SE_COMPONENTS
#define SE_COMPONENTS

#include "Event.h"
#include "EntityManager.h"
#include "ExceptionManager.h"

class UID;

class Component {
public:

	virtual ~Component() {};

};

class HealthComponent : public Component {

public:

	HealthComponent(int HP, UID owner);

	void OnExec(SDL_Event&);

	int GetCurrentHealth();
	int GetMaxHealth();
	bool GetIsAlive();

	// void ReceiveEvent(UID caller, Event e) override;

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

class ShieldComponent : public Component {

	ShieldComponent(int SP, UID owner);

	int CurrentSP;
	int MaxSP;
	UID ownerID;


};

class StatComponent : public Component {

};

class AttribComponent : public Component {

};

class EquipComponent : public Component {

};

class InfoComponent : public Component {

	InfoComponent(std::string name, std::string desc);;

	std::string Name;
	std::string Desc;

};

class RenderComponent : public Component {
public:

	void OnExec(SDL_Event&) override;

private:

	SDL_Texture * tex; // TODO: Animated textures.

};

#endif