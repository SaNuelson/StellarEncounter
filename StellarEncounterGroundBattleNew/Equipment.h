#pragma once
#include "stdlib.h"

class Weapon {
public:

	Weapon() : amt(-10) {};
	Weapon(std::string source) {
		ParseSource(this, source);
	}
	Weapon(int amount) : amt(amount) {};

	int GetStrength() { return amt; }

private:

	int amt;

	static void ParseSource(Weapon* weapon, std::string& source) {

		weapon->amt = std::stoi(source);

	}

};

/*
class Equipment {
public:

	Equipment() {};
	~Equipment() {};

private:



};

class Equipable {
public:

	Equipable(Equipment * equipment) : equipment(equipment) {};

	virtual void Use(Unit * unit) = 0;

private:

	Equipment* equipment;

};

class Weapon : public Equipable {
public:

	Weapon(Equipment * equipment, int attack) : Equipable(equipment), attack(attack) {};

	void Use(Unit * unit) override { unit->ReceiveAction() }

private:

	int attack;

};
*/