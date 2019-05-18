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

Unit::Unit(big HP, big SP, small AP, Tile* tile, std::string texSrc, TileMap* tilemap, small team) {
	MaxHP = HP;
	CurHP = HP;
	MaxAP = AP;
	CurAP = AP;
	this->tile = tile;
	tile->occ = this;
	LoadTextures(texSrc);
	this->tilemap = tilemap;
	Team = team;
}

void Unit::LoadTextures(std::string texSrc)
{
	textures.push_back(ResourceManager::LoadTexture(texSrc));
	SDL_QueryTexture(textures[0], nullptr, nullptr, &position.w, &position.h);
}

void Unit::Resize()
{
	SDL_Point dims;
	SDL_QueryTexture(textures[currentTexture], nullptr, nullptr, &dims.x, &dims.y);
	int mult = yTileSize / dims.y;
	position.h = yTileSize;
	position.w = dims.x * xTileSize / dims.y;
}

void Unit::OnUpdate(double delta) {

	// change animation if needed
	if (currentAction != nextAction) {
		currentAction = nextAction;
		textureTimeLeft = textureSpeed;
		currentTexture = textureSets[currentAction].first;
		Resize();

		if (currentAction == UNIT_ACTION_IDLE) {
			flip = (Team != 0);
			SDL_Point p = tile->GetCenter();
			position.x = p.x - position.w / 2;
			position.y = p.y - position.h;
		}

	}

	if (currentAction == UNIT_ACTION_MOVE) {
		if (move_vec.x == 0 && move_vec.y == 0) {
			nextAction = 0;
		}
		else {
			if (move_vec.x < 0)
				flip = true;
			else
				flip = false;
			moveTimeLeft--;
			if (moveTimeLeft == 0) {
				if (move_vec.x != 0 && move_vec.y != 0)
					moveTimeLeft = 2 * moveSpeed;
				else
					moveTimeLeft = moveSpeed;
				int mx;
				int my;
				if (move_vec.x > 0)
					mx = 1;
				else if (move_vec.x < 0)
					mx = -1;
				else
					mx = 0;
				if (move_vec.y > 0)
					my = 1;
				else if (move_vec.y < 0)
					my = -1;
				else
					my = 0;
				move_vec.x -= mx;
				move_vec.y -= my;
				position.x += mx;
				position.y += my;
			}
		}
	}
	else if (currentAction == UNIT_ACTION_ATTACK) {
		if (currentTexture == textureSets[UNIT_ACTION_ATTACK].second) {
			nextAction = UNIT_ACTION_IDLE;
		}
	}
	else if (currentAction == UNIT_ACTION_HIT) {
		if (currentTexture == textureSets[UNIT_ACTION_HIT].second) {
			nextAction = UNIT_ACTION_IDLE;
		}
	}
	else if (currentAction == UNIT_ACTION_DYING) {
		if (currentTexture == textureSets[UNIT_ACTION_DYING].second) {
			nextAction = UNIT_ACTION_DEAD;
		}
	}

	// add movement to animataion if needed


	// update animation, always
	textureTimeLeft -= delta;
	if (textureTimeLeft <= 0) {
		textureTimeLeft = textureSpeed;
		currentTexture++;
		if (textureSets[currentAction].second < currentTexture) {
			currentTexture = textureSets[currentAction].first;
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
	nextAction = UNIT_ACTION_ATTACK;
	if (defender->tile->pos.x < tile->pos.x)
		flip = (Team == 0);
	std::cout << toString() << " uses action against " << defender->toString() << std::endl;
	ChangeAP(-1);  // will vary with equip
	defender->ReceiveAction(weapon.GetStrength());
}

void Unit::ReceiveAction(int amount)
{
	nextAction = UNIT_ACTION_HIT;
	ChangeSP(amount, true);
}

void Unit::Move(Tile * tile)
{
	nextAction = UNIT_ACTION_MOVE;
	move_vec = tilemap->GetMoveVec(this->tile, tile);
	ChangeAP(-tilemap->GetDistance(this->tile, tile));
	
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
		nextAction = UNIT_ACTION_DYING;
	}
	else if (CurHP >= MaxHP) {
		if (overload)
			ChangeSP(CurHP - MaxHP, false);
		CurHP = MaxHP;
	}

	ResourceManager::DispatchEvent(RC_UNIT_STAT_CHANGE, this, nullptr);

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

	ResourceManager::DispatchEvent(RC_UNIT_STAT_CHANGE, this, nullptr);
}

void Unit::ChangeAP(big amount)
{
	// for debug
	if (amount < 0) {
		std::cout << toString() << " is exhausted by " << amount << "points of stamina." << std::endl;
	}
	else if (amount > 0) {
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

	ResourceManager::DispatchEvent(RC_UNIT_STAT_CHANGE, this, nullptr);
}

void Unit::OnRender() {
	SDL_RenderCopyEx(ResourceManager::ren, textures[currentTexture], nullptr, &position, 0, nullptr, (flip ? SDL_RendererFlip::SDL_FLIP_HORIZONTAL : SDL_RendererFlip::SDL_FLIP_NONE));
}

std::string Unit::toString()
{
	if (name != "")
		return name;

	auto str = "GameObject::Unit( HP: " + std::to_string(CurHP) + "/" + std::to_string(MaxHP) +
		", SP: " + std::to_string(CurSP) + "/" + std::to_string(MaxSP) +
		", AP: " + std::to_string(CurAP) + "/" + std::to_string(MaxAP) +
		", Team: " + std::to_string(Team) + ")";
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

	std::stringstream ss(source);
	std::string line;
	while (std::getline(ss, line)) {
		std::string attrib = line.substr(0, line.find('='));
		std::string value = line.substr(line.find('=') + 1, line.size());
		std::cout << "Parsed attrib = " << attrib << " and val = " << value << std::endl;
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
			// <TEXTURE_SET_CODE>=<COUNT>|<TEXTURE_PATH(in format: path/file[X.png] -- part in [] added automatically)>
			// eg. "Graphics/GameObjects/Hero/idle1.png , ... , Graphics/GameObjects/Hero/idle12.png changes to Graphics/GameObjects/Hero/idle

			std::string path_base = value;
			for(int i = 0; i < Actions->size(); i++) {
				int start = unit->textures.size();
				int count = 0;
				while (true) {
					SDL_Texture* tex = ResourceManager::LoadTexture(path_base + "/" + Actions[i] + "/tile0" + (count < 10 ? "0" : "") + std::to_string(count) + ".png");
					if (tex == nullptr) {
						break;
					}
					else {
						unit->textures.push_back(tex);
						count++;
					}
				}
				unit->textureSets[i] = std::make_pair(start, start + count - 1);
			}
		}
		else {
			std::cout << "Mistake in pair " << attrib << " " << value << ".\n Attribute unknown.\n";
		}
	}

}
