#include "Component.h"
#include "Entity.h"
#include "ResourceManager.h"
#include "Tiles.h"

Component::Component(){}
Component::~Component(){}

void HealthComponent::Damage(int amount) {
	CurHP -= amount;
	if (CurHP < 0) {
		CurHP = 0;
		// statcomponent -> dead
	}
}

void HealthComponent::Heal(int amount) {
	CurHP += amount;
	CurHP = std::min(CurHP, MaxHP);
}

void ShieldComponent::Damage(int amount) {
	if (amount > CurSP) {
		int surp = amount - CurSP;
		CurSP = 0;
		owner->health.Damage(amount);
	}
}

void ShieldComponent::Fix(int amount) {
	CurSP = std::min(CurSP + amount, MaxSP);
}

TransformComponent::TransformComponent(Entity * owner, BoxTileMap * tilemap, int tx, int ty, int speed) : owner(owner), tilemap(tilemap), speed(speed) {
	currentTile.x = tx;
	currentTile.y = ty;
	SDL_Point p = tilemap->GetCoords(tx, ty);
	position.x = p.x;
	position.y = p.y;
	std::cout << "Position " << position.x << " " << position.y << std::endl;
}

SDL_Rect* TransformComponent::GetPosition()
{
	SDL_QueryTexture(owner->render.GetTexture(), nullptr, nullptr, &position.w, &position.h);
	std::cout << "GetPosition " << position.x << " " << position.y << std::endl;
	return &position;
}

void TransformComponent::Move(SDL_Point moveVec) {
	moving = true;
	int magnitude = abs(moveVec.x) + abs(moveVec.y);
	velocity.x = speed * moveVec.x / magnitude;
	velocity.y = speed * moveVec.y / magnitude;
}

void TransformComponent::MoveTo(SDL_Point &dst) {
	destTile = dst;
	dest = tilemap->GetCoords(destTile.x, destTile.y);
	moving = true;
	int magnitude = dest.x + dest.y;
	velocity.x = speed * dest.x / magnitude;
	velocity.y = speed * dest.y / magnitude;
	std::cout << "Moving starting, velocity set to " << velocity.x << " " << velocity.y << std::endl;
}

void TransformComponent::OnUpdate(double delta) {
	if (moving) {
		if (abs(dest.x - position.x) <= velocity.x && abs(dest.y - position.y) <= velocity.y) {
			std::cout << "Ending movement" << std::endl;
			moving = false;
			position.x = dest.x;
			position.y = dest.y;
		}
		else {
			position.x += velocity.x;
			position.y += velocity.y;
			std::cout << "Moving to " << position.x << " " << position.y << " with velocity " << velocity.x << " " << velocity.y << std::endl;
		}
	}
}

void RenderComponent::Load(std::string folderPath) {
	// TODO
	textures.push_back(ResourceManager::LoadTexture(folderPath + "idle1.png"));
}

SDL_Texture * RenderComponent::GetTexture()
{
	return textures[currentTex];
}

void RenderComponent::OnRender(SDL_Renderer * ren) {
	if (textures[currentTex] == nullptr) {
		std::cout << "null texture" << std::endl;
		exit(-1);
	}
	SDL_RenderCopy(ren, textures[currentTex], nullptr, owner->transform.GetPosition());
	std::cout << "Render to " << owner->transform.position.x << " " << owner->transform.position.y << std::endl;
}
