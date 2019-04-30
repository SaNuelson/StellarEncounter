#include "Scene.h"
#include "stdlib.h"
#include "ResourceManager.h"
#include "Tilemap.h"
#include "GameObject.h"
#include "Unit.h"
#include "Item.h"
#include "UnitStackBlock.h"


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

	bool UpKey = false;
	bool DownKey = false;

	TileMap tilemap;

	std::vector<Unit*> units;
	int currentUnit = 0;
	Unit * GetCurrentUnit();

	std::vector<Item*> items;


	UnitInfoBlock infoblock;
	UnitActionBlock actionblock;
	UnitStackBlock stackblock;
};