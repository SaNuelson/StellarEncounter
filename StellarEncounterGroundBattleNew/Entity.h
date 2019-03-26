#pragma once

#include "stdlib.h"
#include "Constants.h"
#include "Component.h"

class Component;
class HealthComponent;
class ShieldComponent;
class StatComponent;
class EquipComponent;
class InfoComponent;
class RenderComponent;
class TransformComponent;

class Entity {
public:

	Entity() {};
	Entity(SDL_Renderer* rend, bool controllable) : ren(rend), controllable(controllable) {};
	~Entity() {};

	static std::shared_ptr<Entity> GetDefault(SDL_Renderer* renderer);

	void OnUpdate(double delta) {
		transform.OnUpdate(delta);
	}

	void OnRender() {
		render.OnRender(ren);
	}

	bool isControllable() { return controllable; }

	bool isActive() { return true; }

	void destroy() {}

	InfoComponent info;

	StatComponent stat;
	EquipComponent equip;

	HealthComponent health;
	ShieldComponent shield;

	TransformComponent transform;
	RenderComponent render;

private:

	bool controllable;
	SDL_Renderer* ren = nullptr;
	int AP;

};
