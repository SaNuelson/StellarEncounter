#include "Scene.h"
#include "stdlib.h"
#include "ResourceManager.h"
#include "Tilemap.h"
#include "GameObject.h"
#include "Unit.h"
#include "Item.h"


class UnitActionBlock;
class UnitInfoBlock;

class GroundBattleScene : public Scene {
public:

	GroundBattleScene();

	void StartDemo1();

	void ResolveInput(SDL_Event& e) override;
	void OnUpdate(double delta) override;
	void OnRender() override;

	bool IsPlayerTurn();

	Unit * GetCurrentUnit();

	std::vector<Unit*> units;
	int currentUnit = 0;

	std::vector<Item*> items;

	BoxTileMap tilemap;

	UnitInfoBlock infoblock;
	UnitActionBlock actionblock;

};