#pragma once

#include <map>
#include <LevelLoadingInfo.h>
#include <SFML/System.hpp>
#include <LevelSerialization.h>

using namespace sf;
using namespace std;

namespace KrostganEngine::Core {
	class ObjectsCatalog {

	public:

		static void Unload() {
			for (auto& pair : Catalog) {

				delete pair.second;
			}
			Catalog.clear();
		}
		static void Add(GameObjectLoadInfo* obj) {
			if (obj->CatalogID == LevelCellMapDeser::EMPTY_CATALOG_ID)
				return;

			if (Catalog.find(obj->CatalogID) == Catalog.end()) {
				Catalog.insert(pair<size_t, GameObjectLoadInfo*>(obj->CatalogID, obj));
			}
		}
		static void Remove(GameObjectLoadInfo* obj) {
			Remove(obj->CatalogID);
		}
		static void Remove(size_t id) {
			Catalog.erase(id);
		}
		static GameObjectLoadInfo* GetObjectInfo(size_t id) {
			return Catalog[id];
		}
		static size_t GetCatalogSize(){
			return Catalog.size();
		}

	private:
		ObjectsCatalog(){}

		static inline map<size_t, GameObjectLoadInfo*> Catalog= map<size_t, GameObjectLoadInfo*>();
	};

	class ObjsCatalogDeserial {
		
	public:
		static void DeserializeCatalog(string serPath);
		//static GameObject* DeserializeObj(vector<string>& params,LevelLoadingInfo& levelInfo, Vector2f position=Vector2f(0,0));
		static GameObjectLoadInfo& ParseObjInfo(vector<string>& params);

		static inline const string PAR_DEF_NAME_END_SYM = ":";
		static inline const string OBJECTS_SEP_LINE = "endl;";

		static UnitLoadInfo& ParseUnitInfo(vector<string>& params);
		static HeroLoadInfo& ParseHeroInfo(vector<string>& params);
		static WallLoadInfo& ParseWallInfo(vector<string>& params);

		static bool TryGetSerValueOfParam(vector<string>& params, const string& paramName, string* output);
		static EntityBattleStats& GetBattleStats(vector<string>& params, string* buffer);

	private:
		ObjsCatalogDeserial() {}

	};

	struct SerializationObjectsTypes {

		static inline const string OBJECT_TYPE_UNIT = "Unit";
		static inline const string OBJECT_TYPE_WALL = "Wall";
		static inline const string OBJECT_TYPE_HERO = "Hero";
	};
	struct SerializationParDefNames {
		static inline const string OBJECT_NAME = "Name";
		static inline const string OBJECT_SPRITE_PATH = "SpritePath";
		static inline const string OBJECT_SPRITE_OFFSET = "SpriteOffset";
		static inline const string OBJECT_POSITION = "Position";
		static inline const string OBJECT_SIZE = "Size";
		static inline const string OBJECT_TYPE = "Type";
		static inline const string OBJECT_CATALOG_ID = "CatalogID";

		static inline const string ENTITY_MAX_HP = "MaxHP";
		static inline const string ENTITY_CURR_HP = "CurrentHP";
		static inline const string ENTITY_REGEN_HP_COUNT = "HPRegenCount";
		static inline const string ENTITY_REGEN_HP_TICK = "HPRegenTick";
		static inline const string ENTITY_AA_DAMAGE = "AADamage";
		static inline const string ENTITY_AA_SPEED = "AASpeed";
		static inline const string ENTITY_AA_RADIUS = "AARadius";
		static inline const string ENTITY_FRACTION = "Fraction";
		static inline const string ENTITY_AUTO_AGGRESSIONS_RADIUS = "AutoAggrRadius";

		static inline const string UNIT_MOVINGSPEED = "MovingSpeed";
	};
}