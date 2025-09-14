#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <forward_list>
#include <string>
#include <EntityBattleStats.h>
#include <RelationsSystem.h>
#include <CoreGameObjects.h>
#include <LevelCellMapDeser.h>
#include <vector>

using namespace std;
using namespace sf;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

#define Attr		const pair<const string,const string>
#define AttrsCollectn	vector<Attr*>

namespace KrostganEngine::Core {
	struct LevelLoadingInfo;
	struct LoadedObjects;

	struct LvlObjCatalogSubInfo {

		LvlObjCatalogSubInfo(const AttrsCollectn& Attrs) 
			:Attrs(Attrs){}
		~LvlObjCatalogSubInfo() {
			for (auto& attr : Attrs) {
				delete attr;
			}
		}

		AttrsCollectn Attrs;
	};

	struct GameObjectLoadInfo {

		virtual ~GameObjectLoadInfo(){}

		string Name="";
		string SpriteSource="";
		Vector2f Position = (Vector2f)ITransformableObj::NULL_POS;
		size_t CatID = 0;
		float Size = 1;

		virtual GameObject* InstanceObject
			(LoadedObjects&			levInfo,
			vector<Attr*>*			additParams		= nullptr,
			LvlObjCatalogSubInfo*	objSubInfo		= nullptr) = 0;

		/// <summary>
		/// Return true if param was wrotten.
		/// </summary>
		/// <param name="param"></param>
		/// <returns></returns>
		virtual bool WriteParam(Attr& param);

	protected:
		GameObjectLoadInfo() {}

		GameObjectLoadInfo* Cache = nullptr;

		virtual void ResetFromCache();
		/// <summary>
		/// Return true if names are equal
		/// </summary>
		/// <param name="param"></param>
		/// <param name="paramName"></param>
		/// <returns></returns>
		static bool CheckParamName(Attr& param, const string& paramName);
	};

	struct EntityLoadInfo : public GameObjectLoadInfo{

		string				HPBarSpriteSource		= "";
		string				HPBarMaskSource			= "";
		string				SelectionAreaSource		= "";
		Fraction			EntityFraction			= Fraction::Neutral;
		EntityBattleStats	BattleStats;

		bool WriteParam(Attr& param) override;

	protected:
		EntityLoadInfo():GameObjectLoadInfo(){}

		void ResetFromCache() override;

		virtual EntityCtorParams& GetCtorParams() = 0;
	};

	struct UnitLoadInfo : public EntityLoadInfo{

		UnitLoadInfo() : EntityLoadInfo(){}

	
		GameObject*	InstanceObject
			(LoadedObjects&			levInfo,
			AttrsCollectn*			additParams = nullptr,
			LvlObjCatalogSubInfo*	objSubInfo = nullptr) override;

		//bool WriteParam(pair<const string&, const string&> param) override;

	//protected:
	//	UnitObjectCtorParams& GetUnitParams();

	protected:
		EntityCtorParams& GetCtorParams() override;
	};

	struct HeroLoadInfo : public UnitLoadInfo {
		
		HeroLoadInfo():UnitLoadInfo(){}

		GameObject* InstanceObject
			(LoadedObjects&			levInfo,
			AttrsCollectn*			additParams = nullptr,
			LvlObjCatalogSubInfo*	objSubInfo = nullptr)override;

		bool WriteParam(Attr& param) override;

	protected:
		EntityCtorParams& GetCtorParams() override;
	};

	struct WallLoadInfo :public GameObjectLoadInfo {

		WallLoadInfo() : GameObjectLoadInfo() {};

		GameObject* InstanceObject
			(LoadedObjects&			levInfo,
			AttrsCollectn*			additParams = nullptr,
			LvlObjCatalogSubInfo*	objSubInfo	= nullptr) override;

		bool WriteParam(const pair<const string, const string>& param) override;
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

	struct LoadedObjects final {
		forward_list<HeroObject*> LoadedHeroes = forward_list<HeroObject*>();
		forward_list<UnitObject*> LoadedUnits = forward_list<UnitObject*>();
		forward_list <WallObject*> LoadedWalls = forward_list<WallObject*>();
		forward_list <ICallbackRec_GraphRen*> LoadedGraphics = forward_list<ICallbackRec_GraphRen*>();
	};
}


