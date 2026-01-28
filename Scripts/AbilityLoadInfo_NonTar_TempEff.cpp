
#include <AbilityLoadInfo.h>
#include <GameEffectsCatalog.h>
#include <AbilitiesCatalogSerConsts.h>

using namespace KrostganEngine::GameObjects;

AbilityLoadInfo_NonTar_TempEff::AbilityLoadInfo_NonTar_TempEff() {

}
AbilityLoadInfo_NonTar_TempEff::AbilityLoadInfo_NonTar_TempEff(const AbilityLoadInfo_NonTar_TempEff& copy)
	:AbilityLoadInfo(copy),
		GameEff_CatalogID(copy.GameEff_CatalogID),
		GameEff_SubCatalogID(copy.GameEff_SubCatalogID),
		EffDuration(copy.EffDuration){

}
AbilityLoadInfo_NonTar_TempEff::~AbilityLoadInfo_NonTar_TempEff() {

}

Ability& AbilityLoadInfo_NonTar_TempEff::InstantiateAbility() const {

	auto& gameEff = GameEffectsCatalog::GetObjectInfo(GameEff_CatalogID, GameEff_SubCatalogID).InstantiateGameEff();
	auto& ability = *new Ability_NonTar_TempEff
		(*dynamic_cast<ComposeGameEff_Temporal*>(&gameEff), 
			EffDuration, 
			CatalogID, 
			SubCatalogID);
	ability.Set_CooldownDuration(CooldownDuration);
	return ability;
}
bool AbilityLoadInfo_NonTar_TempEff::WriteParam(Attr& param) {

	if (AbilityLoadInfo::WriteParam(param))
		return true;

	if (CheckParamName(param, AbilitiesLoading_ParamDefNames::ABILITY_GAMEEFF_CATALOGID)) {
		GameEff_CatalogID = stoll(param.second);
	}
	else if (CheckParamName(param, AbilitiesLoading_ParamDefNames::ABILITY_GAMEEFF_SUB_CATALOGID)) {
		GameEff_SubCatalogID = (std::byte)stoi(param.second);
	}
	else if (CheckParamName(param, AbilitiesLoading_ParamDefNames::ABILITY_GAMEEFF_DURATION)) {
		EffDuration = stof(param.second);
	}
	else
		return false;

	return true;
}
AbilityLoadInfo& AbilityLoadInfo_NonTar_TempEff::Clone() const {
	return *new AbilityLoadInfo_NonTar_TempEff(*this);
}