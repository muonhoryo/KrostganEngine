
#include <AbilityLoadInfo.h>
#include <GameEffectsCatalog.h>
#include <AbilitiesCatalogSerConsts.h>

using namespace KrostganEngine::GameObjects;

AbilityLoadInfo_Aura::AbilityLoadInfo_Aura() {

}
AbilityLoadInfo_Aura::AbilityLoadInfo_Aura(const AbilityLoadInfo_Aura& copy) 
	:AbilityLoadInfo(copy),
		AuraRange(copy.AuraRange),
		ToTargetRelMask(copy.ToTargetRelMask),
		GameEff_CatalogID(copy.GameEff_CatalogID),
		GameEff_SubCatalogID(copy.GameEff_SubCatalogID){

}

Ability& AbilityLoadInfo_Aura::InstantiateAbility() const {

	auto& gameEff = GameEffectsCatalog::GetObjectInfo(GameEff_CatalogID, GameEff_SubCatalogID).InstantiateGameEff();
	auto& ability = *new Ability_Aura
			(AuraRange,
			ToTargetRelMask, 
			*dynamic_cast<ComposeGameEff_Permanent*>(&gameEff), 
			CatalogID, 
			SubCatalogID);
	ability.Set_CooldownDuration(CooldownDuration);
	return ability;
}
bool AbilityLoadInfo_Aura::WriteParam(Attr& param) {

	if (AbilityLoadInfo::WriteParam(param))
		return true;

	if (CheckParamName(param, AbilitiesLoading_ParamDefNames::ABILITY_AURA_RANGE)) {
		AuraRange = stof(param.second);
	}
	else if (CheckParamName(param, AbilitiesLoading_ParamDefNames::ABILITY_AURA_TOTARGET_RELATIONMASK)) {
		ToTargetRelMask = RelationSerialization::DeserializeRelation(param.second);
	}
	else if (CheckParamName(param, AbilitiesLoading_ParamDefNames::ABILITY_GAMEEFF_CATALOGID)) {
		GameEff_CatalogID = stoll(param.second);
	}
	else if (CheckParamName(param, AbilitiesLoading_ParamDefNames::ABILITY_GAMEEFF_SUB_CATALOGID)) {
		GameEff_SubCatalogID = (std::byte)stoi(param.second);
	}
	else {
		return false;
	}
	return true;
}
AbilityLoadInfo& AbilityLoadInfo_Aura::Clone() const {
	return *new AbilityLoadInfo_Aura(*this);
}