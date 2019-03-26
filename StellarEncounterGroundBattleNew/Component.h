#pragma once

#include "stdlib.h"
#include "Constants.h"


class Entity;
class BoxTileMap;

class Component
{
public:
	Component();

	Entity* owner;
	~Component();

};

class HealthComponent : Component {

public:

	HealthComponent() {};
	HealthComponent(Entity* ent, int HP) : owner(ent), CurHP(HP), MaxHP(HP) {};
	~HealthComponent() = default;

	void Damage(int amount);

	void Heal(int amount);

private:

	int MaxHP;
	int CurHP;
	Entity* owner;

};

class InfoComponent : Component {
public:

	InfoComponent() {};
	InfoComponent(Entity* ent, std::string Name, std::string Desc) : owner(ent), name(Name), desc(Desc) {};

	std::string name;
	std::string desc;
	Entity* owner;

};

class ShieldComponent : Component {
public:

	ShieldComponent() {};
	ShieldComponent(Entity* ent, int SP) : owner(ent), MaxSP(SP), CurSP(SP) {};

	void Damage(int amount);

	void Fix(int amount);

private:

	int MaxSP;
	int CurSP;
	Entity* owner;

};

class StatComponent : Component {
public:

	StatComponent() {};
	StatComponent(Entity* ent) : owner(ent), isAlive(true) {};

private:

	bool isAlive;
	Entity* owner;

};

class EquipComponent : Component {
public:

	EquipComponent() {};
	EquipComponent(Entity* ent) : owner(ent) {};
	// EquipComponent(Race race) { race.GetAvailableEquip() };

private:

	Entity* owner;

};

class TransformComponent : Component {
public:

	TransformComponent() {};
	TransformComponent(Entity* owner, BoxTileMap* tilemap, int tx, int ty, int speed);

	SDL_Rect* GetPosition();
	void MoveTo(SDL_Point &dst);
	void Move(SDL_Point movevec);
	void OnUpdate(double delta);

	int speed;
	SDL_Point currentTile;
	SDL_Point destTile;
	SDL_Point dest;
	SDL_Point velocity;
	bool moving = false;
	SDL_Rect position;

private:

	Entity* owner;
	BoxTileMap* tilemap;

};

class RenderComponent : Component {
public:

	RenderComponent() {};
	RenderComponent(Entity* ent, std::string folderPath) : owner(ent) { Load(folderPath); }

	void Load(std::string folderPath);

	SDL_Texture* GetTexture();

	void OnRender(SDL_Renderer* ren);

private:

	std::vector<SDL_Texture*> textures;
	int currentTex = 0;
	std::vector<std::pair<int, int>> textureBounds;
	Entity* owner;

};