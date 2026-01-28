#pragma once

#include <string>
#include <SFML/System.hpp>
#include <HeroObject.h>
#include <ObjectsCatalog.h>
#include <LvlLoadingStructs.h>

using namespace std;
using namespace sf;

namespace KrostganEngine::GameObjects {

	struct WorldObjectLoadInfo : public ObjectLoadInfo {

		virtual ~WorldObjectLoadInfo() {}

		string		Name = "";
		Vector2f	Position = (Vector2f)ITransformableObj::NULL_POS;
		float		Size = 1;
		float		Rotation = 0;

		bool WarFog_IsHiden = false;
		bool WarFog_IsShowed = false;
		bool LateRender = true;
		vector<LvlObjInstantiationInfo> ChildObjs;

		WorldTransfObj* InstantiateObject(LvlObjAdditParams* additParams = nullptr) const;

		/// <summary>
		/// Return true if param was wrotten.
		/// </summary>
		/// <param name="param"></param>
		/// <returns></returns>
		virtual bool WriteParam(Attr& param);
		virtual bool WriteParamByNode(xml_node<>& node);

		virtual WorldObjectLoadInfo& Clone() const = 0;

	protected:
		WorldObjectLoadInfo() { }
		WorldObjectLoadInfo(const WorldObjectLoadInfo& copy);

		mutable WorldObjectLoadInfo* Cache = nullptr;

		virtual WorldTransfObj* InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const = 0;

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

		virtual ~GameObjectLoadInfo() {}

		string SpriteSource = "";

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

	struct EntityLoadInfo : public GameObjectLoadInfo {

		virtual ~EntityLoadInfo() {}

		string								HPBarSpriteSource = "";
		string								HPBarMaskSource = "";
		string								HitEffectSprite = "";
		string								SelectionAreaSource = "";
		Fraction							EntityFraction = Fraction::Neutral;
		EntityBattleStats					BattleStats = EntityBattleStats();
		vector<pair<size_t, std::byte>>		Abilities = vector<pair<size_t, std::byte>>();

		bool WriteParam(Attr& param) override;
		bool WriteParamByNode(xml_node<>& node) override;

	protected:
		EntityLoadInfo() :GameObjectLoadInfo() {}
		EntityLoadInfo(const EntityLoadInfo& copy);

		void VerifyAAStatsExisting();
		void WriteBattleStatsParams(const string& input, IModifiableStatsWrapper& stats);
		void WriteBattleStatsParams(const xml_node<>& input, IModifiableStatsWrapper& stats);
		void WriteAbility(const xml_node<>& input);

		void FillCtorParams(GameObjectCtorParams& params, const GameObjectLoadInfo& usedInfo) const override;

		static inline const string ENTITY_BSTATS_PARAMS_SEP = ";;";
	};

	struct UnitLoadInfo : public EntityLoadInfo {

		virtual ~UnitLoadInfo() {}

		UnitLoadInfo() : EntityLoadInfo() {}
		UnitLoadInfo(const UnitLoadInfo& copy) : EntityLoadInfo(copy) {}

		WorldObjectLoadInfo& Clone() const override;

	protected:
		WorldTransfObj* InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const override;
	};

	struct HeroLoadInfo : public UnitLoadInfo {

		virtual ~HeroLoadInfo() {}

		HeroLoadInfo() :UnitLoadInfo() {}
		HeroLoadInfo(const HeroLoadInfo& copy) : UnitLoadInfo(copy) {}

		bool WriteParam(Attr& param) override;

		WorldObjectLoadInfo& Clone() const override;

	protected:
		WorldTransfObj* InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const override;
	};

	struct WallLoadInfo :public GameObjectLoadInfo {

		virtual ~WallLoadInfo() {}

		WallLoadInfo() : GameObjectLoadInfo() {}
		WallLoadInfo(const WallLoadInfo& copy) : GameObjectLoadInfo(copy) {}

		bool WriteParam(Attr& param) override;

		WorldObjectLoadInfo& Clone() const override;

	protected:
		WorldTransfObj* InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const override;

	};

	struct DecorationLoadInfo : public GameObjectLoadInfo {

		virtual ~DecorationLoadInfo() {}

		string			HitEffectSprite = "";
		size_t			CurrentHP = 1;
		size_t			MaxHP = 1;
		bool			IsTargetableForAA = true;
		ColliderShape* COLLIDER = nullptr;

		DecorationLoadInfo() : GameObjectLoadInfo() {}
		DecorationLoadInfo(const DecorationLoadInfo& copy);

		bool WriteParam(Attr& param) override;
		bool WriteParamByNode(xml_node<>& node) override;

		WorldObjectLoadInfo& Clone() const override;

	protected:
		void FillCtorParams(GameObjectCtorParams& params, const GameObjectLoadInfo& usedInfo) const override;
		WorldTransfObj* InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const override;

	};

	struct SpriteRendLoadInfo : public WorldObjectLoadInfo {

		virtual ~SpriteRendLoadInfo() {}

		SpriteRendLoadInfo() : WorldObjectLoadInfo() {}
		SpriteRendLoadInfo(const SpriteRendLoadInfo& copy);

		string SpriteSource = "";
		float MaxSpriteSize = 0;
		//Vector2f	Origin = DEFAULT_ORIGIN;
		std::byte RendLayer = DEFAULT_RENDLAYER;

		bool WriteParam(Attr& param) override;

		WorldObjectLoadInfo& Clone() const override;

	protected:
		WorldTransfObj* InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const override;
	};

	/// <summary>
	/// InstantiateObject() doesn't work directly, cause projectile needs an owner and a target.
	/// Use InstantiateProjectile() to instantiate projectile.
	/// </summary>
	struct AAProjectileLoadInfo : public WorldObjectLoadInfo {

		virtual ~AAProjectileLoadInfo() {}

		AAProjectileLoadInfo() : WorldObjectLoadInfo() {}
		AAProjectileLoadInfo(const AAProjectileLoadInfo& copy);

		AutoAttackProjectile& InstantiateProjectile
		(AutoAttackModule& Owner,
			IAttackableObj& Target,
			LvlObjAdditParams* additParams = nullptr) const;

		WorldObjectLoadInfo& Clone() const override;

	protected:
		WorldTransfObj* InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const override;

		mutable AutoAttackModule* Owner = nullptr;
		mutable IAttackableObj* Target = nullptr;
	};
}