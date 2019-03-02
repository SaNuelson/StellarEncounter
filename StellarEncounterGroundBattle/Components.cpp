#include "Components.h"

HealthComponent::HealthComponent(int HP, UID owner) : CurrentHP(HP), MaxHP(HP), ownerID(owner) {}

int HealthComponent::GetCurrentHealth() { return CurrentHP; }

int HealthComponent::GetMaxHealth() { return MaxHP; }

bool HealthComponent::GetIsAlive() { return IsAlive; }
/*
void HealthComponent::ReceiveEvent(UID caller, Event e)
{
	if (e.event_type == Constants::EVENT_TYPE::DamageEntity) {
		ReceiveDamage(std::stoi(e.args[0]));
	}
	else if (e.event_type == Constants::EVENT_TYPE::HealEntity) {
		HealDamage(std::stoi(e.args[0]));
	}
	else {
		Managers::ExceptionManager::logError("Incompatible Event received (" + caller.toString() +")");
	}
}
*/
void HealthComponent::OwnerDied() {  }

void HealthComponent::ReceiveDamage(int amount) {
	CurrentHP -= amount;
	if (CurrentHP < 0) {
		CurrentHP = 0;
		IsAlive = false;
	}
}

void HealthComponent::HealDamage(int amount) {
	CurrentHP += amount;
	if (CurrentHP > MaxHP)
		CurrentHP = MaxHP;
}

ArmorComponent::ArmorComponent(int AP, UID owner) : CurrentAP(AP), MaxAP(AP), ownerID(owner) {}

ShieldComponent::ShieldComponent(int SP, UID owner) : CurrentSP(SP), MaxSP(SP), ownerID(owner) {}

InfoComponent::InfoComponent(std::string name, std::string desc) : Name(name), Desc(desc) {}

