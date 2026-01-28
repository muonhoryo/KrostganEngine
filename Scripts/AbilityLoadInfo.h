#pragma once

#include <ObjectsCatalog.h>
#include <AbilitiesSystem.h>
#include <LvlLoadingStructs.h>
#include <_BuiltAbilities.h>

using namespace KrostganEngine::Core;

namespace KrostganEngine::GameObjects {
	struct AbilityLoadInfo : public ObjectLoadInfo {

		virtual ~AbilityLoadInfo() {}

		string Name = "";
		float CooldownDuration = FLT_MAX;

		virtual Ability& InstantiateAbility() const = 0;

		/// <summary>
		/// Return true if param was wrotten.
		/// </summary>
		/// <param name="param"></param>
		/// <returns></returns>
		virtual bool WriteParam(Attr& param);
		/// <summary>
		/// Return true if param was wrotten.
		/// </summary>
		/// <param name="param"></param>
		/// <returns></returns>
		virtual bool WriteParamByNode(xml_node<>& node);

		virtual AbilityLoadInfo& Clone() const = 0;

	protected:
		AbilityLoadInfo();
		AbilityLoadInfo(const AbilityLoadInfo& copy);
	};

	struct AbilityLoadInfo_Aura : public AbilityLoadInfo {

		AbilityLoadInfo_Aura();
		AbilityLoadInfo_Aura(const AbilityLoadInfo_Aura& copy);
		virtual ~AbilityLoadInfo_Aura(){}

		float AuraRange = 0;
		Relation ToTargetRelMask = Relation::Neutral;
		size_t GameEff_CatalogID = EMPTY_CATALOG_ID;
		std::byte GameEff_SubCatalogID = ABSENT_SUB_CATALOG_ID;

		Ability& InstantiateAbility() const override;
		bool WriteParam(Attr& param) override;
		AbilityLoadInfo& Clone() const override;
	};

	struct AbilityLoadInfo_NonTar_Durable : public AbilityLoadInfo {

		AbilityLoadInfo_NonTar_Durable();
		AbilityLoadInfo_NonTar_Durable(const AbilityLoadInfo_NonTar_Durable& copy);
		virtual ~AbilityLoadInfo_NonTar_Durable();

		float CooldownSinceStart = FLT_MAX;
		size_t GameEff_CatalogID = EMPTY_CATALOG_ID;
		std::byte GameEff_SubCatalogID = ABSENT_SUB_CATALOG_ID;

		Ability& InstantiateAbility() const override;
		bool WriteParam(Attr& param) override;
		AbilityLoadInfo& Clone() const override;
	};

	/// <summary>
	/// Head-info contains infos of all next abilities and in InstantiateAbility() creates whole chain of set auto-attack-ablities.
	/// Array of next ability infos filled only in head-info.
	/// </summary>
	struct AbilityLoadInfo_NonTar_SetAA : public AbilityLoadInfo {

		AbilityLoadInfo_NonTar_SetAA();
		AbilityLoadInfo_NonTar_SetAA(const AbilityLoadInfo_NonTar_SetAA& copy);
		virtual ~AbilityLoadInfo_NonTar_SetAA();

		vector<AbilityLoadInfo_NonTar_SetAA*> NextAbilitiesInfo;
		size_t AAIndex = 0;
		size_t OnAddGameEff_CatalogID = EMPTY_CATALOG_ID;
		std::byte OnAddGameEff_SubCatalogID = ABSENT_SUB_CATALOG_ID;
		float NextAbilityCooldown = 0;
		bool DeleteGameEffOnRemove = true;

		Ability& InstantiateAbility() const override;
		bool WriteParam(Attr& param) override;
		bool WriteParamByNode(xml_node<>& node) override;
		AbilityLoadInfo& Clone() const override;

	private:
		Ability_NonTar_SetAA& InstantiateSingleSetAAAbility() const;
	};

	struct AbilityLoadInfo_NonTar_TempEff : public AbilityLoadInfo {

		AbilityLoadInfo_NonTar_TempEff();
		AbilityLoadInfo_NonTar_TempEff(const AbilityLoadInfo_NonTar_TempEff& copy);
		virtual ~AbilityLoadInfo_NonTar_TempEff();

		size_t GameEff_CatalogID = EMPTY_CATALOG_ID;
		std::byte GameEff_SubCatalogID = ABSENT_SUB_CATALOG_ID;
		float EffDuration = 0;

		Ability& InstantiateAbility() const override;
		bool WriteParam(Attr& param) override;
		AbilityLoadInfo& Clone() const override;
	};
}