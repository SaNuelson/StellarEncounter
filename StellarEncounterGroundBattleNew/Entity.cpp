#include "Entity.h"
#include "Component.h"

std::shared_ptr<Entity> Entity::GetDefault(SDL_Renderer * renderer) {
	Entity ent;
	ent.controllable = true;
	ent.AP = 5;
	ent.info = InfoComponent(&ent, "Hero", "Hero description...");
	ent.health = HealthComponent(&ent, 200);
	ent.shield = ShieldComponent(&ent, 200);
	ent.stat = StatComponent(&ent);
	ent.equip = EquipComponent(&ent);
	SDL_Rect rect;
	rect.x = 50;
	rect.y = 50;
	rect.w = 100;
	rect.h = 100;
	//ent.transform = TransformComponent(&ent, rect, 5);
	ent.render = RenderComponent(&ent, "Graphics/Hero/");

	auto entptr = std::make_shared<Entity>(ent);

	return entptr;
}
