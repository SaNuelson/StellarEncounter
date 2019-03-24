#ifndef SE_CHARACTER
#define SE_CHARACTER

#include <vector>
#include "EntityManager.h"
#include "ExceptionManager.h"
#include "UID.h"

class Character
{
public:

	Character() = default;
	Character(UID ownerID, int HP, int AP, int Att) {
		owner = ownerID;
		HPmax = HP;
		HPcur = HP;
		APmax = AP;
		APcur = AP;
		AttackPower = Att;
	};
	~Character() { OnCleanup(); };

	UID GetOwner() { return owner; };
	void OnCleanup() {};

	void Attack(Character* defender) {
		defender->Defend(this, AttackPower);
	}

	void BindToOwner(UID ownerID) {
		owner = ownerID;
	}

	void Defend(Character* attacker, int &damage) {
		HPcur -= damage;
		if (HPcur <= 0) {
			std::cout << "Unit died" << std::endl;
		}
	}

private:


	int HPmax;
	int HPcur;

	int APmax;
	int APcur;

	int AttackPower;

	UID owner;

	SDL_Texture* tex;
	SDL_Point mappos;
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