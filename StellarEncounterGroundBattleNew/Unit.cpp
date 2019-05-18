#include "Unit.h"

Unit::Unit() : weapon(10) {}

Unit::Unit(std::string source) {

	ParseSource(this, source);
	SDL_Point dims;
	SDL_QueryTexture(textures[currentTexture], nullptr, nullptr, &dims.x, &dims.y);
	int mult = yTileSize / dims.y;
	position.h = yTileSize;
	position.w = dims.x * xTileSize / dims.y;
}

Unit::Unit(big HP, big SP, small AP, Tile* tile, std::string texSrc, TileMap* tilemap, bool playerTeam) {

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

	textureTimeLeft -= delta;
	if (textureTimeLeft <= 0) {
		textureTimeLeft = textureSpeed;
		currentTexture++;
		if (textureSets[currentTextureSet].second < currentTexture) {
			currentTexture = textureSets[currentTextureSet].first;
		}
	}

	if (CurHP <= 0) {
		CurHP = 0;
		textures.push_back(ResourceManager::LoadTexture("Graphics/Units/rip.png"));
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

void Unit::Move(Tile * tile)
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
		Move(tile->tile_up_right);
		break;
	case 1:
		Move(tile->tile_right);
		break;
	case 2:
		Move(tile->tile_down_right);
		break;
	case 3:
		Move(tile->tile_down_left);
		break;
	case 4:
		Move(tile->tile_left);
		break;
	case 5:
		Move(tile->tile_up_left);
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
	SDL_Point p = tile->GetCenter();
	position.x = p.x - position.w / 2;
	position.y = p.y - position.h;
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

void Unit::ParseSource(Unit* unit, std::string& source)
{

	/*
		Requirements:
			Textures is at the end of file
			Texture paths are all in said format and in .png
			Any repeated attributes will override former attributes

		<<< <ATTRIB>=<VALUE>\n >>>
		Name=<VALUE>\n
		HP=<VALUE>\n
		(or	MaxHP=<VALUE>\n
			CurHP=<VALUE>\n)
		SP=<VALUE>\n
		(or	MaxSP=<VALUE>\n
			CurSP=<VALUE>\n)
		AP=<VALUE>\n
		(or MaxAP=<VALUE>\n
			CurAP=<VALUE>\n)
		Weapon=<WEAPON_SRC>\n
		TextureSpeed=<VALUE>\n
		Textures=\n
		<TEXTURE_SET_CODE>=<COUNT>|<TEXTURE_PATH(in format: path/fileX.png)>\n
	*/

	bool textures = false;
	std::stringstream ss(source);
	std::string line;
	while (std::getline(ss, line)) {
		std::string attrib = line.substr(0, line.find('='));
		std::string value = line.substr(line.find('=') + 1, line.size());
		std::cout << "Parsed attrib = " << attrib << " and val = " << value << std::endl;
		if(!textures){
			if (attrib == "Name") {
				unit->name = value;
			}
			else if (attrib == "HP") {
				unit->MaxHP = std::stoi(value);
				unit->CurHP = std::stoi(value);
			}
			else if (attrib == "MaxHP") {
				unit->MaxHP = std::stoi(value);
			}
			else if (attrib == "CurHP") {
				unit->CurHP = std::stoi(value);
			}
			else if (attrib == "SP") {
				unit->MaxSP = std::stoi(value);
				unit->CurSP = std::stoi(value);
			}
			else if (attrib == "MaxSP") {
				unit->MaxSP = std::stoi(value);
			}
			else if (attrib == "CurSP") {
				unit->CurSP = std::stoi(value);
			}
			else if (attrib == "AP") {
				unit->MaxAP = std::stoi(value);
				unit->CurAP = std::stoi(value);
			}
			else if (attrib == "CurAP") {
				unit->MaxAP = std::stoi(value);
			}
			else if (attrib == "MaxAP") {
				unit->CurAP = std::stoi(value);
			}
			else if (attrib == "Weapon") {
				unit->weapon = Weapon(value);
			}
			else if (attrib == "TextureSpeed") {
				unit->textureSpeed = std::stoi(value);
			}
			else if (attrib == "Textures") {
				textures = true;
			}
			else {
				std::cout << "Mistake in pair " << attrib << " " << value << ".\n Attribute unknown.\n";
			}
		}
		else {
			// <TEXTURE_SET_CODE>=<COUNT>|<TEXTURE_PATH(in format: path/file[X.png] -- part in [] added automatically)>
			// eg. "Graphics/GameObjects/Hero/idle1.png , ... , Graphics/GameObjects/Hero/idle12.png changes to 12|Graphics/GameObjects/Hero/idle
			int count = std::stoi(value.substr(0, value.find('|')));
			std::string path = value.substr(value.find('|') + 1, value.size());
			int start = unit->textures.size();
			int end = start + count - 1;
			for (int i = 0; i < count; i++)
			{
				if (i < 10) {
					unit->textures.push_back(ResourceManager::LoadTexture(path + "00" + std::to_string(i) + ".png"));
				}
				else {
					unit->textures.push_back(ResourceManager::LoadTexture(path + "0" + std::to_string(i) + ".png"));
				}
			}
			unit->textureSets[std::stoi(attrib)] = std::make_pair(start, end);
		}
	}

}
