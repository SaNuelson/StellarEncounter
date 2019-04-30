#pragma once
#include "stdlib.h"
#include "ResourceManager.h"
#include "UnitInfoBlock.h"

class UIHolder {
public:

	UIHolder(TileMap* tilemap) {
		unitinfo = UnitInfoBlock(tilemap);

	};
	~UIHolder() {};

	void OnUpdate(double delta) {
		unitinfo.OnUpdate(delta);
	};
	void OnRender() {
		unitinfo.OnRender();
	}

private:

	UnitInfoBlock unitinfo;

};