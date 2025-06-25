#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <forward_list>
#include <string>
#include <EntityBattleStats.h>
#include <RelationsSystem.h>
#include <CoreGameObjects.h>
#include <LevelCellMapDeser.h>

using namespace std;
using namespace sf;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

namespace KrostganEngine::Core {
	struct LevelLoadingInfo;
	struct LoadedObjects;

	struct GameObjectLoadInfo {
		GameObjectLoadInfo(){}
		string Name="";
		string TexturePath="";
		Vector2f SpriteOffset=Vector2f(0,0);
		Vector2f Position = Vector2f(0, 0);
		size_t CatalogID = 0;
		float Size = 1;

		virtual GameObject* InstanceObject(LoadedObjects& levInfo,Vector2f position, vector<string>* additParams = nullptr) = 0;
		GameObject* InstanceObject(LoadedObjects& levInfo, vector<string>* additParams = nullptr) {
			return InstanceObject(levInfo, Position, additParams);
		}
	};

	struct UnitLoadInfo : public GameObjectLoadInfo {
		UnitLoadInfo() :GameObjectLoadInfo(),BattleStats(nullptr) {};

		EntityBattleStats*	BattleStats;
		Fraction	EntityFraction	=	Fraction::Neutral;
	
		GameObject*	InstanceObject(LoadedObjects& levInfo, Vector2f position , vector<string>* additParams = nullptr) override;

	protected:
		UnitObjectCtorParams& GetUnitParams( );
	};

	struct HeroLoadInfo : public UnitLoadInfo {
		HeroLoadInfo():UnitLoadInfo(){}

		GameObject* InstanceObject(LoadedObjects& levInfo, Vector2f position , vector<string>* additParams = nullptr) override;
	};

	struct WallLoadInfo :public GameObjectLoadInfo {
		WallLoadInfo() : GameObjectLoadInfo() {};

		GameObject* InstanceObject(LoadedObjects& levInfo, Vector2f position , vector<string>* additParams = nullptr) override;
	};

	struct LevelLoadingInfo final {

		vector<vector<LevelCellMapDeser::CellInfo*>*>& LevelMap;
		forward_list<GameObjectLoadInfo*>& UniqueObjects;
		size_t MapRowsCount;

		LevelLoadingInfo(vector<vector<LevelCellMapDeser::CellInfo*>*>& LevelMap, forward_list<GameObjectLoadInfo*>& UniqueObjects,
			size_t MapRowsCount)
			:LevelMap(LevelMap),
			UniqueObjects(UniqueObjects),
			MapRowsCount(MapRowsCount)
		{}
		~LevelLoadingInfo() {
			for (auto obj : UniqueObjects) {
				delete obj;
			}
		}
	};

	struct LoadedObjects {
		forward_list<HeroObject*> LoadedHeroes = forward_list<HeroObject*>();
		forward_list<UnitObject*> LoadedUnits = forward_list<UnitObject*>();
		forward_list <WallObject*> LoadedWalls = forward_list<WallObject*>();
		forward_list <ICallbackRec_GraphRen*> LoadedGraphics = forward_list<ICallbackRec_GraphRen*>();
	};
}


