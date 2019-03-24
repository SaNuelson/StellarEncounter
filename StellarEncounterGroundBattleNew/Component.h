#pragma once

#include "stdlib.h"
#include "Entity.h"
#include "Constants.h"

class Entity;

class Component
{
public:
	Component();

	Entity* owner;
	~Component();

};

class HealthComponent : Component {

public:

	HealthComponent(Entity* ent, int HP) : owner(ent), CurHP(HP), MaxHP(HP) {};
	~HealthComponent() = default;

	void Damage(int amount) {
		CurHP -= amount;
		if (CurHP < 0) {
			CurHP = 0;
			// statcomponent -> dead
		}
	}

	void Heal(int amount) {
		CurHP += amount;
		CurHP = std::min(CurHP, MaxHP);
	}

private:

	int MaxHP;
	int CurHP;
	Entity* owner;

};

class InfoComponent : Component {
public:

	InfoComponent(Entity* ent) : owner(ent) {};

	std::string name;
	std::string desc;
	Entity* owner;

};

class ShieldComponent : Component {
public:

	ShieldComponent(Entity* ent, int SP) : owner(ent), MaxSP(SP), CurSP(SP) {};

	void Damage(int amount) {
		if (amount > CurSP) {
			int surp = amount - CurSP;
			CurSP = 0;
			owner->health->Damage(surp);
		}
	}

	void Fix(int amount) {
		CurSP = std::min(CurSP + amount, MaxSP);
	}

private:

	int MaxSP;
	int CurSP;
	Entity* owner;

};

class StatComponent : Component {
public:

	StatComponent(Entity* ent) : owner(ent), isAlive(true) {};

private:

	bool isAlive;
	Entity* owner;

};

class EquipComponent : Component {
public:
	EquipComponent(Entity* ent) : owner(ent) {};
	// EquipComponent(Race race) { race.GetAvailableEquip() };

private:

	Entity* owner;

};

class TransformComponent : Component {
public:

	TransformComponent(Entity* ent, SDL_Rect &start_pos, int speed) : owner(ent), position(start_pos), speed(speed) {};

	SDL_Rect position;
	int speed;

private:

	Entity* owner;

};

class RenderComponent : Component {
public:

	RenderComponent(Entity* ent, std::string folderPath) : owner(ent) { Load(folderPath); }

	void Load(std::string folderPath) {

	}

	void OnRender(SDL_Renderer* ren) {
		SDL_RenderCopy(ren, textures[currentTex], nullptr, &owner->transform->position);
	}

private:

	std::vector<SDL_Texture*> textures;
	int currentTex = 0;
	std::vector<std::pair<int, int>> textureBounds;
	Entity* owner;

};