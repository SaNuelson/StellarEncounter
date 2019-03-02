#ifndef SE_UID
#define SE_UID

#include "ExceptionManager.h"

struct UID
{
public:

	UID() : id(-1), type(-1) {};

	static UID GetNewTexUID() { return UID(0); };
	static UID GetNewEntUID() { return UID(1); };
	static UID GetNewTileUID() { return UID(2); };
	static UID GetNewFontUID() { return UID(3); };
	static UID GetNewOtherUID() { return UID(4); };
	static UID GetEmptyUID() { return UID(-1); };

	bool operator <(const UID &right) const {
		if (type < right.type)
			return true;
		if (type > right.type)
			return false;
		if (id < right.id)
			return true;
		return false;
	}

	std::string toString() {
		return type + "." + id;
	}

private:

	UID(char uid_type) {
		type = uid_type;
		switch (uid_type) {
		case -1:
			id = -1;
			break;
		case 0:
			id = tex_ctr++;
			break;
		case 1:
			id = ent_ctr++;
			break;
		case 2:
			id = til_ctr++;
			break;
		case 3:
			id = ttf_ctr++;
			break;
		case 4:
			id = oth_ctr++;
			break;
		default:
			Managers::ExceptionManager::logError("Unknown UID type: " + uid_type);
			break;
		}
	}

	char type;
	int id;

	enum Type {
		Texture = 0,
		Entity = 1,
		Tile = 2,
		Other = 3
	};

	static int tex_ctr;
	static int ent_ctr;
	static int til_ctr;
	static int ttf_ctr;
	static int oth_ctr;

};

#endif