#pragma once
#include "stdlibs.h"
#include "EntityManager.h"
#include "Character.h"
#include "UID.h"

class Player
{
public:

	Player() : ID(UID::GetNewOtherUID()) {};

	~Player() = default;

	virtual void Update(double delta) = 0;

	std::vector<UID> units;

	UID GetID() { return ID; };

private:

	UID ID;

};

class HumanPlayer : public Player {

public:
	void ResolveEvent(SDL_Event &e) {};
	void Update(double delta) override {};

};

class AIPlayer : public Player {

public:
	void Update(double delta) override {};

private:

	int8_t difficulty;

};
