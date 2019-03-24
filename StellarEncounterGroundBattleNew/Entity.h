#pragma once

#include "stdlib.h"
#include "Component.h"
#include "Constants.h"

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
	Entity(SDL_Renderer* rend) : ren(rend) {};
	~Entity() {};

	/*
	static Entity GetDefault(SDL_Renderer* renderer) {
		Entity player;
		player.ren = renderer;
		player.info = std::make_unique<InfoComponent>("The Hero", "A brave and fearless hero wandering throughout the wilderness");
		player.health = std::make_unique<HealthComponent>(&player, 200);
		player.shield = std::make_unique<ShieldComponent>(&player, 150);
		player.stat = std::make_unique<StatComponent>(&player);
		player.equip = std::make_unique <EquipComponent>(&player);
		player.transform = std::make_unique<TransformComponent>(&player, 100, 100, 100, 100);
		player.render = std::make_unique<RenderComponent>(&player);
	}
	*/

	void OnRender() {
		(*render).OnRender(ren);
	}

	bool isActive() { return true; }

	void destroy() {}

	std::unique_ptr<InfoComponent> info;

	std::unique_ptr<StatComponent> stat;
	std::unique_ptr<EquipComponent> equip;

	std::unique_ptr<HealthComponent> health;
	std::unique_ptr<ShieldComponent> shield;

	std::unique_ptr<TransformComponent> transform;
	std::unique_ptr<RenderComponent> render;

private:

	SDL_Renderer* ren = nullptr;

};
