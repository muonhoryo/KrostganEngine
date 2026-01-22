#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <forward_list>
#include <EntityBattleStats.h>
#include <RelationsSystem.h>
#include <CoreGameObjects.h>
#include <AutoAttackModule.h>
#include <LvlLoadingStructs.h>

using namespace std;
using namespace sf;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

namespace KrostganEngine::Core {
	struct LevelLoadingInfo;


//
//
// LoadInfo
//
//

	struct WorldObjectLoadInfo {

		virtual ~WorldObjectLoadInfo() {}

		string Name = "";
		Vector2f Position = (Vector2f)ITransformableObj::NULL_POS;
		float Size = 1;
		float Rotation = 0;
		size_t CatID = 0;

		bool WarFog_IsHiden = false;
		bool WarFog_IsShowed = false;
		bool LateRender = true;
		vector<LvlObjInstantiationInfo> ChildObjs;

		WorldTransfObj* InstantiateObject
				(LvlObjAdditParams*			objSubInfo = nullptr,
				LvlObjAdditParams*			additParams	= nullptr) const;

		/// <summary>
		/// Return true if param was wrotten.
		/// </summary>
		/// <param name="param"></param>
		/// <returns></returns>
		virtual bool WriteParam(Attr& param);
		virtual bool WriteParamByNode(xml_node<>& node);

	protected:
		WorldObjectLoadInfo() { }
		WorldObjectLoadInfo(const WorldObjectLoadInfo& copy);

		mutable WorldObjectLoadInfo* Cache = nullptr;

		virtual WorldTransfObj* InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const = 0;
		virtual WorldObjectLoadInfo* CreateCacheInfo() const = 0;
		/// <summary>
		/// Return true if names are equal
		/// </summary>
		/// <param name="param"></param>
		/// <param name="paramName"></param>
		/// <returns></returns>
		static bool CheckParamName(Attr& param, const string& paramName);

//
//
// Check child instantiating recursion
// 	On instantiating children RecursionCount is inreasing and decreasing on children instantiating done
//	If RecursionCount would increased to its max exception will be thrown
//
//
	private:
		void InstantiateChildren(WorldTransfObj& parent) const;

		static inline unsigned int RecursionCount = 0;
	};

	struct GameObjectLoadInfo : public WorldObjectLoadInfo {

		virtual ~GameObjectLoadInfo(){}

		string SpriteSource="";
		
		bool SolidCollision = true;

		/// <summary>
		/// Return true if param was wrotten.
		/// </summary>
		/// <param name="param"></param>
		/// <returns></returns>
		bool WriteParam(Attr& param) override;

	protected:
		GameObjectLoadInfo() {}
		GameObjectLoadInfo(const GameObjectLoadInfo& copy);

		virtual void FillCtorParams(GameObjectCtorParams& params, const GameObjectLoadInfo& usedInfo) const;
	};

	struct EntityLoadInfo : public GameObjectLoadInfo{

		virtual ~EntityLoadInfo(){}

		string				HPBarSpriteSource		= "";
		string				HPBarMaskSource			= "";
		string				HitEffectSprite			= "";
		string				SelectionAreaSource		= "";
		Fraction			EntityFraction			= Fraction::Neutral;
		EntityBattleStats	BattleStats				= EntityBattleStats();

		bool WriteParam(Attr& param) override;
		bool WriteParamByNode(xml_node<>& node) override;

	protected:
		EntityLoadInfo():GameObjectLoadInfo(){}
		EntityLoadInfo(const EntityLoadInfo& copy);

		void VerifyAAStatsExisting();
		void WriteBattleStatsParams(const string& input, IModifiableStatsWrapper& stats);
		void WriteBattleStatsParams(const xml_node<>& input, IModifiableStatsWrapper& stats);

		void FillCtorParams(GameObjectCtorParams& params, const GameObjectLoadInfo& usedInfo) const override;

		static inline const string ENTITY_BSTATS_PARAMS_SEP = ";;";
	};

	struct UnitLoadInfo : public EntityLoadInfo{

		virtual ~UnitLoadInfo(){}

		UnitLoadInfo() : EntityLoadInfo(){}
		UnitLoadInfo(const UnitLoadInfo& copy) : EntityLoadInfo(copy) {}

	protected:
		WorldTransfObj*	InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const override;
		WorldObjectLoadInfo* CreateCacheInfo() const override;
	};

	struct HeroLoadInfo : public UnitLoadInfo {
		
		virtual ~HeroLoadInfo(){}

		HeroLoadInfo():UnitLoadInfo(){}
		HeroLoadInfo(const HeroLoadInfo& copy) : UnitLoadInfo(copy) {}

		bool WriteParam(Attr& param) override;

	protected:
		WorldTransfObj* InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const override;
		WorldObjectLoadInfo* CreateCacheInfo() const override;
	};

	struct WallLoadInfo :public GameObjectLoadInfo {

		virtual ~WallLoadInfo(){}

		WallLoadInfo() : GameObjectLoadInfo() {}
		WallLoadInfo(const WallLoadInfo& copy) : GameObjectLoadInfo(copy) {}

		bool WriteParam(Attr& param) override;

	protected:
		WorldTransfObj* InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const override;
		WorldObjectLoadInfo* CreateCacheInfo() const override;

	};

	struct DecorationLoadInfo : public GameObjectLoadInfo {

		virtual ~DecorationLoadInfo(){}

		string			HitEffectSprite = "";
		size_t			CurrentHP = 1;
		size_t			MaxHP = 1;
		bool			IsTargetableForAA = true;
		ColliderShape*	Collider = nullptr;

		DecorationLoadInfo() : GameObjectLoadInfo(){}
		DecorationLoadInfo(const DecorationLoadInfo& copy);

		bool WriteParam(Attr& param) override;
		bool WriteParamByNode(xml_node<>& node) override;

	protected:
		void FillCtorParams(GameObjectCtorParams& params, const GameObjectLoadInfo& usedInfo) const override;
		WorldTransfObj* InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const override;
		WorldObjectLoadInfo* CreateCacheInfo() const override;

	};

	struct SpriteRendLoadInfo : public WorldObjectLoadInfo{

		virtual ~SpriteRendLoadInfo(){}

		SpriteRendLoadInfo() : WorldObjectLoadInfo(){}
		SpriteRendLoadInfo(const SpriteRendLoadInfo& copy);

		string SpriteSource = "";
		float MaxSpriteSize = 0;
		std::byte RendLayer = DEFAULT_RENDLAYER;

		bool WriteParam(Attr& param) override;

	protected:
		WorldTransfObj* InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const override;
		WorldObjectLoadInfo* CreateCacheInfo() const override;
	};

	/// <summary>
	/// InstantiateObject() doesn't work directly, cause projectile needs an owner and a target.
	/// Use InstantiateProjectile() to instantiate projectile.
	/// </summary>
	struct AAProjectileLoadInfo : public WorldObjectLoadInfo {

		virtual ~AAProjectileLoadInfo(){}

		AAProjectileLoadInfo() : WorldObjectLoadInfo(){}
		AAProjectileLoadInfo(const AAProjectileLoadInfo& copy);

		AutoAttackProjectile& InstantiateProjectile
			(AutoAttackModule& Owner,
			IAttackableObj& Target,
			LvlObjAdditParams* objSubInfo = nullptr,
			LvlObjAdditParams* additParams = nullptr) const;

	protected:
		WorldTransfObj* InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const override;
		WorldObjectLoadInfo* CreateCacheInfo() const override;

		mutable AutoAttackModule* Owner=nullptr;
		mutable IAttackableObj* Target=nullptr;
	};

//
//
// LevelLoadingInfo
//
//

	struct LevelLoadingInfo final {

		vector<vector<LvlObjInstantiationInfo*>*>& LevelMap;
		forward_list<LvlObjInstantiationInfo*>& UniqueObjects;
		size_t MapRowsCount = 0;
		size_t MapColumnsCount = 0;

		//Consts

		Rect<float>	CameraBorders;

		float WarFogOffset = 0;

		string WarFogShaderPath;

		string BackgroundImagePath;
		bool BackgroundTiled = false;

		LevelLoadingInfo(vector<vector<LvlObjInstantiationInfo*>*>& LevelMap, forward_list<LvlObjInstantiationInfo*>& UniqueObjects)
			:LevelMap(LevelMap),
			UniqueObjects(UniqueObjects)
		{}
		~LevelLoadingInfo() {

			for (auto row : LevelMap) {
				for (auto obj : *row) {
					delete obj;
				}
				delete row;
			}

			for (auto obj : UniqueObjects) {
				delete obj;
			}
			
			delete &LevelMap;
			delete &UniqueObjects;
		}
	};
}


