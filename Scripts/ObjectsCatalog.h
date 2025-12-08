#pragma once

#include <map>
#include <LevelLoadingInfo.h>
#include <SFML/System.hpp>
#include <LevelSerialization.h>

using namespace sf;
using namespace std;

#define _ObjSubsPairType		pair<std::byte,LvlObjAdditParams*>
#define _ObjSubsCollection		vector<_ObjSubsPairType>

namespace KrostganEngine::Core {
	class ObjectsCatalog {

	public:
		static inline const size_t	EMPTY_CATALOG_ID		= 0;
		static inline const std::byte	ABSENT_SUB_CATALOG_ID	= (std::byte)0;

	private:
		struct GetSubInfoFunc : public CollectionsExts::Predicate<const _ObjSubsPairType &> {
			
			GetSubInfoFunc(std::byte ID)
				:ID(ID){}

			bool Condition(const _ObjSubsPairType& input) const override {
				return input.first == ID;
			}

			const std::byte ID;
		};

	public:

		static void					Add(WorldObjectLoadInfo* obj) {
			if (obj->CatID== EMPTY_CATALOG_ID)
				return;

			if (Catalog.find(obj->CatID) == Catalog.end()) {
				Catalog.insert(pair<size_t, WorldObjectLoadInfo*>(obj->CatID, obj));
			}
		}
		static void					Remove(WorldObjectLoadInfo* obj) {
			Remove(obj->CatID);
		}
		static void					Remove(size_t id) {
			Catalog.erase(id);
			auto subs = SubCatalog.find(id);
			if (subs != SubCatalog.end()) {
				for (auto& pr : (*subs).second) {
					delete pr.second;
				}
			}
			SubCatalog.erase(subs);
		}
		static size_t				GetCatalogSize() {
			return Catalog.size();
		}
		static WorldObjectLoadInfo*	GetObjectInfo(size_t id) {
			return Catalog[id];
		}

		static void						AddSub(size_t objID, std::byte subID, LvlObjAdditParams& subObjInfo) {

			if (Catalog.find(objID) != Catalog.end()) {
				
				auto subs = SubCatalog.find(objID);
				if (subs == SubCatalog.end()) {

					auto nSub = pair<size_t, _ObjSubsCollection >
						(objID, _ObjSubsCollection());
					SubCatalog.insert(nSub);
					subs = SubCatalog.find(objID);
				}
				else {
					auto el = CollectionsExts::Get<_ObjSubsCollection, _ObjSubsPairType>
						((*subs).second, GetSubInfoFunc(subID));
					if (el != nullptr)
						throw exception("Sub info is already defined.");
				}
				(*subs).second.push_back(_ObjSubsPairType(subID, &subObjInfo));
			}
		}
		static void						RemoveSub(size_t objID, std::byte subID) {
			auto sub = SubCatalog.find(objID);
			if (sub != SubCatalog.end()) {
				
				auto index = CollectionsExts::IndexOf<_ObjSubsCollection, _ObjSubsPairType>
					((*sub).second, GetSubInfoFunc(subID));
				auto it = (*sub).second.begin();
				it += index;
				(*sub).second.erase(it);
			}
		}
		static LvlObjAdditParams*			GetSubObjInfo(size_t id, std::byte subID) {
			
			auto subs = SubCatalog.find(id);
			if (subs != SubCatalog.end()) {

				return CollectionsExts::Get<_ObjSubsCollection, _ObjSubsPairType>
					((*subs).second, GetSubInfoFunc(subID))->second;

			}
			return nullptr;
		}

		static void Unload() {
			for (auto& pair : Catalog) {
				delete pair.second;
			}
			Catalog.clear();

			for (auto& pair : SubCatalog) {
				for (auto& subsPair : pair.second) {
					delete subsPair.second;
				}
			}
			SubCatalog.clear();
		}

	private:
		ObjectsCatalog(){}

		static inline map<size_t, WorldObjectLoadInfo*>	Catalog;
		static inline map<size_t, _ObjSubsCollection >	SubCatalog;
	};

	class ObjsCatalogDeserial {
		
	public:
		static void										DeserializeCatalog(string serPath);
		static WorldObjectLoadInfo&						ParseObjInfo	(const vector<string>& params);
		static pair<size_t,_ObjSubsPairType>&			ParseObjSubinfo	(const vector<string>& params);
		static const pair<const string, const string>*	ParseParamLine(const string& line);

		static inline const string PAR_DEF_NAME_END_SYM = ":";
		static inline const string OBJECTS_SEP_LINE = "endl;";

	private:
		ObjsCatalogDeserial() {}

	};

	struct SerializationObjectsTypes {

		static inline const string OBJECT_TYPE_UNIT = "Unit";
		static inline const string OBJECT_TYPE_WALL = "Wall";
		static inline const string OBJECT_TYPE_HERO = "Hero";
		static inline const string OBJECT_TYPE_SPRITE = "Sprite";
		static inline const string OBJECT_TYPE_AA_PROJECTILE = "Projectile";
	};
	struct SerializationParDefNames {
		static inline const string CATALOG_SUB_INFO_ID	= "Subcatalog";

		static inline const string OBJECT_NAME			= "Name";
		static inline const string OBJECT_POSITION		= "Position";
		static inline const string OBJECT_ROTATION		= "Rotation";
		static inline const string OBJECT_SIZE			= "Size";
		static inline const string OBJECT_TYPE			= "Type";
		static inline const string OBJECT_CATALOG_ID	= "CatalogID";
		static inline const string OBJECT_CHILDREN		= "Children";

		static inline const string IMAGEUSR_SPRITE_SOURCE	= "SpriteSource";
		static inline const string IMAGEUSR_SPRITE_LAYER	= "Layer";

		static inline const string ENTITY_FRACTION				= "Fraction";
		static inline const string ENTITY_SELECT_AREA_SOURCE	= "SelectionAreaSource";
		static inline const string ENTITY_HPBAR_SPRITE_SOURCE	= "HPBarSprite";
		static inline const string ENTITY_HITEFF_SPRITE_SOURCE	= "HitEffectSprite";
		static inline const string ENTITY_HPBAR_MASK			= "HPBarMask";

		static inline const string ENTITY_BATTLE_STATS			= "BattleStats";
		static inline const string ENTITY_AA_STATS				= "AAStats";
	};
}