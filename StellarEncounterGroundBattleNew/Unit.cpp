#include "Unit.h"

Unit::Unit(big HP, big SP, small AP, BoxTile* tile, std::string texSrc, BoxTileMap* tilemap, bool playerTeam) {

	MaxHP = HP;
	CurHP = HP;
	MaxAP = AP;
	CurAP = AP;
	this->tile = tile;
	tile->occ = this;
	LoadTextures(texSrc);
	this->tilemap = tilemap;
	isPlayer = playerTeam;
}

void Unit::LoadTextures(std::string texSrc)
{
	textures.push_back(ResourceManager::LoadTexture(texSrc));
	SDL_QueryTexture(textures[0], nullptr, nullptr, &position.w, &position.h);
}

void Unit::OnUpdate(double delta) {

	if (CurHP <= 0) {
		CurHP = 0;
		textures.push_back(ResourceManager::LoadTexture("Graphics/rip.png"));
		currentTexture++;
	}

}

void Unit::UseAction(GameObject * defender)
{
	std::cout << toString() << " uses action against " << defender->toString() << std::endl;
	CurAP--; // will vary with equip
	defender->ReceiveAction(weapon.GetStrength());
}

void Unit::ReceiveAction(int amount)
{
	ChangeSP(amount, true);
}

void Unit::Move(BoxTile * tile)
{
	this->CurAP -= tilemap->GetDistance(this->tile, tile);
	this->tile->SetOccupant(nullptr);
	tile->SetOccupant(this);
	this->tile = tile;
}

void Unit::Move(Direction dir)
{
	switch (dir) {
	case 0:
		Move(tile->tile_left);
		break;
	case 1:
		Move(tile->tile_up);
		break;
	case 2:
		Move(tile->tile_right);
		break;
	case 3:
		Move(tile->tile_down);
		break;
	}
}

void Unit::ChangeHP(big amount, bool overload)
{
	// for debug
	if (amount > 0) {
		std::cout << toString() << " gets healed for " << amount << "points." << std::endl;
	}
	else if (amount < 0) {
		std::cout << toString() << " gets hurt for " << amount << " points." << std::endl;
	}
	else {
		std::cout << toString() << " felt some distant breeze, its health not changed at all." << std::endl;
	}

	CurHP += amount;
	if (CurHP < 0) {
		CurHP = 0;
		Die();
	}
	else if (CurHP >= MaxHP) {
		if (overload)
			ChangeSP(CurHP - MaxHP, false);
		CurHP = MaxHP;
	}
}

void Unit::ChangeSP(big amount, bool overload)
{
	// for debug
	if (amount > 0) {
		std::cout << toString() << "'s shields regenerate for " << amount << "points." << std::endl;
	}
	else if (amount < 0) {
		std::cout << toString() << "'s shields are damaged for " << amount << " points." << std::endl;
	}
	else {
		std::cout << toString() << " felt some distant breeze, its health not changed at all." << std::endl;
	}

	CurSP += amount;
	if (CurSP < 0) {
		if (overload)
			ChangeHP(CurSP, false);
		CurSP = 0;
	}
	else if (CurSP >= MaxSP) {
		CurSP = MaxSP;
	}
}

void Unit::ChangeAP(big amount)
{
	// for debug
	if (amount > 0) {
		std::cout << toString() << " is exhausted by " << amount << "points of stamina." << std::endl;
	}
	else if (amount < 0) {
		std::cout << toString() << " catches it's breath and gains back " << amount << " points of stamina." << std::endl;
	}
	else {
		std::cout << toString() << " nonchalantly scratched it's crotch, using the same amount of stamina which it gained by the feeling of relief. " << std::endl;
	}

	CurAP += amount;
	if (CurAP < 0) {
		CurAP = 0;
	}
	else if (CurAP >= MaxAP) {
		CurAP = MaxAP;
	}
}

void Unit::Die() 
{
	
}

void Unit::OnRender() {
	//std::cout << "Render " << position.x << " " << position.y << " " << position.w << " " << position.h << std::endl;
	SDL_Point p = tile->GetCenter();
	SDL_Point s;
	SDL_QueryTexture(textures[currentTexture], nullptr, nullptr, &s.x, &s.y);
	position.x = p.x - s.x / 2;
	position.y = p.y - s.y;
	SDL_RenderCopy(ResourceManager::ren, textures[currentTexture], nullptr, &position);
}

bool Unit::isEnemy() { return !isPlayer; }

std::string Unit::toString()
{
	if (name != "")
		return name;

	auto str = "GameObject::Unit( HP: " + std::to_string(CurHP) + "/" + std::to_string(MaxHP) +
		", SP: " + std::to_string(CurSP) + "/" + std::to_string(MaxSP) +
		", AP: " + std::to_string(CurAP) + "/" + std::to_string(MaxAP) +
		(isPlayer ? "PU" : "NPU") + ")";
	return str;
}

Unit * Unit::getPtr() { return this; }
