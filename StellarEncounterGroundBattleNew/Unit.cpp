#include "Unit.h"

Unit::Unit(std::string source) {

	ParseSource(this, source);
	SDL_Point dims;
	SDL_QueryTexture(textures[currentTexture], nullptr, nullptr, &dims.x, &dims.y);
	int mult = yTileSize / dims.y;
	position.h = yTileSize;
	position.w = dims.x * xTileSize / dims.y;

	ResourceManager::DispatchEvent(RC_UNIT_STAT_CHANGE, this, nullptr);
}

Unit::~Unit() {}

void Unit::Edit(std::string source)
{
	ParseSource(this, source);
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
		std::cout << this->toString() << " goes from " << std::to_string(currentAction) << " to " << std::to_string(nextAction) << std::endl;
		currentAction = nextAction;
		textureTimeCurrent = textureTime;
		currentTexture = textureSets[currentAction].first;
		if (currentTexture < 0)
			std::cout << "HERE";
		Resize();

		if (currentAction == UNIT_ACTION_IDLE) {
			flip = (Team != 0);
			if (default_flip)
				flip = !flip;
			SDL_Point p = tile->GetCenter();
			position.x = p.x - position.w / 2;
			position.y = p.y - position.h;
		}

	}

	if (currentAction == UNIT_ACTION_MOVE) {
		pos_x += pos_move_unit_vec_x * moveSpeed * delta / 100;
		pos_y += pos_move_unit_vec_y * moveSpeed * delta / 100;

		/*
		std::cout << "Resolving movement..." << std::endl;
		std::cout << "New float position: " << pos_x << " " << pos_y << std::endl;
		std::cout << "Checking monotonicity of x: " << position.x << " " << dest_point.x << " " << (int)pos_x << std::endl;
		std::cout << "Checking monotonicity of y: " << position.y << " " << dest_point.y << " " << (int)pos_y << std::endl;
		*/

		if (isMonotonic(position.x, dest_point.x, (int)pos_x)) {
			pos_move_unit_vec_x = 0;
		}
		if (isMonotonic(position.y, dest_point.y, (int)pos_y)) {
			pos_move_unit_vec_y = 0;
		}
		if (pos_move_unit_vec_x == 0 && pos_move_unit_vec_y == 0) {
			position.x = dest_point.x;
			position.y = dest_point.y;
			nextAction = UNIT_ACTION_IDLE;
		}
		else {
			position.x = pos_x;
			position.y = pos_y;
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
			ResourceManager::DispatchEvent(RC_UNIT_DEATH, this, nullptr);
		}
	}

	// add movement to animataion if needed


	// update animation, always
	textureTimeCurrent -= delta;
	if (textureTimeCurrent <= 0) {
		textureTimeCurrent = textureTime;
		currentTexture++;
		if (textureSets[currentAction].second < currentTexture) {
			currentTexture = textureSets[currentAction].first;
		}
	}

}

void Unit::UseAction(GameObject * defender)
{
	nextAction = UNIT_ACTION_ATTACK;
	if (defender->tile->pos.x < tile->pos.x)
		flip = !default_flip;
	else
		flip = default_flip;
	std::cout << toString() << " uses action against " << defender->toString() << std::endl;
	ChangeAP(-1);  // will vary with equip
	defender->ReceiveAction(-weapon.GetStrength()); // TODO: negative means damage, positive means healing
}

void Unit::ReceiveAction(int amount)
{
	nextAction = UNIT_ACTION_HIT;
	ChangeSP(amount, true);
}

void Unit::Move(Tile * tile)
{
	nextAction = UNIT_ACTION_MOVE;
	SDL_Point move_vec = tilemap->GetMoveVec(this->tile, tile);
	pos_x = position.x;
	pos_y = position.y;
	// dest point is left-top point of unit rect with bottom-middle point of it equal to tile.GetCenter()
	dest_point = tile->GetCenter();
	dest_point.x -= position.w / 2;
	dest_point.y -= position.h;
	int magn = std::abs(move_vec.x) + std::abs(move_vec.y);
	pos_move_unit_vec_x = move_vec.x / (float)magn;
	pos_move_unit_vec_y = move_vec.y / (float)magn;
	ChangeAP(-tilemap->GetDistance(this->tile, tile));

	std::cout << "Got move vec:  " << move_vec.x << " " << move_vec.y << std::endl;
	std::cout << "Current point: " << position.x << " " << position.y << std::endl;
	std::cout << "Destination p: " << dest_point.x << " " << dest_point.y << std::endl;
	std::cout << "Magnitude:     " << magn << std::endl;
	std::cout << "Unit vector:   " << pos_move_unit_vec_x << " " << pos_move_unit_vec_y << std::endl;

	if (dest_point.x < position.x)
		flip = !default_flip;
	else
		flip = default_flip;

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
	SDL_RenderCopyEx(ResourceManager::GetRenderer(), textures[currentTexture], nullptr, &position, 0, nullptr, (flip ? SDL_RendererFlip::SDL_FLIP_HORIZONTAL : SDL_RendererFlip::SDL_FLIP_NONE));
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

		<<< <ATTRIB>=<VALUE>, >>>
		Name=<VALUE>,
		HP=<VALUE>,
		MaxHP=<VALUE>,
		CurHP=<VALUE>,
		SP=<VALUE>,
		MaxSP=<VALUE>,
		CurSP=<VALUE>,
		AP=<VALUE>,
		MaxAP=<VALUE>,
		CurAP=<VALUE>,
		Weapon=<WEAPON_SRC>,
		TextureSpeed=<VALUE>,
		Textures=,
		<TEXTURE_SET_CODE>=<TEXTURE_PATH(where files for individual unit states can be found (idle/tile000.png, idle/tile001.png, hit/tile000.png, etc.)>
	*/

	std::stringstream ss(source);
	std::string line;
	while (std::getline(ss, line, ',')) {
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
		else if (attrib == "Flip") {
			unit->default_flip = (value == "t" || value == "true" || value == "True" || value == "1" ? true : false);
		}
		else if (attrib == "TextureSpeed" || attrib == "TPS") {
			// setting most likely unnecessary
			// unit->TPS = std::stoi(value);
		}
		else if (attrib == "Textures") {

			std::string path_base = value;
			for(int i = 0; i < ActionsSize; i++) {
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
				std::cout << "Found " << count << " textures for i = " << i << " which should be " << Actions[i] << std::endl;
				if(count > 0)
					unit->textureSets[i] = std::make_pair(start, start + count - 1);
			}
		}
		else {
			std::cout << "Mistake in pair " << attrib << " " << value << ".\n Attribute unknown.\n";
		}
	}

}
