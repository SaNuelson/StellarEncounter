#pragma once
#include "stdlib.h"
#include "Entity.h"
#include "Component.h"

class EntityManager {
public:


	/*
		src =
			info <name> <desc>
			health <HP>
			shield <SP>
			stat
			equip
			transform <x> <y> <w> <h>
			render <pathBase> <idleCount> [<attackCount> <hurtCount> ...]
	*/


	static Entity* CreateEntity(std::map<std::string,std::string> &src) {

		entities.push_back(Entity());
		Entity* ent =  &entities[entities.size() - 1];

		for (auto &data : src) {
			if (data.first == "info")
				ent->info = std::make_unique<InfoComponent>(ent, data.second);
			else if (data.first == "health")
				ent->health = std::make_unique<HealthComponent>(ent, data.second);
			else if (data.first == "shield")
				ent->health == std::make_unique<ShieldComponent>(ent, data.second);
			else if (data.first == "stat")
				ent->stat = std::make_unique<StatComponent>(ent, data.second);
			else if (data.first == "equip")
				ent->equip = std::make_unique<EquipComponent>(ent, data.second);
			else if (data.first == "trans")
				ent->equip == std::make_unique<TransformComponent>(ent, data.second);
			else if (data.first == "render")
				ent->render = std::make_unique<RenderComponent>(ent, data.second);
		}

		return ent;

	}

	static std::vector<Entity> entities;
	static std::map<Entity*,HealthComponent> healthCs;
	static std::map<Entity*,ShieldComponent> shieldCs;
	static std::map<Entity*,StatComponent> statCs;
	static std::map<Entity*,EquipComponent> equipCs;
	static std::map<Entity*,TransformComponent> transCs;
	static std::map<Entity*,RenderComponent> renderCs;

};