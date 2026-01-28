
#include <AbilityLoadInfo.h>
#include <AbilitiesCatalogSerConsts.h>
#include <GameEffectsCatalog.h>

using namespace KrostganEngine::GameObjects;

AbilityLoadInfo_NonTar_Durable::AbilityLoadInfo_NonTar_Durable() {

}
AbilityLoadInfo_NonTar_Durable::AbilityLoadInfo_NonTar_Durable(const AbilityLoadInfo_NonTar_Durable& copy) 
	:AbilityLoadInfo(copy),
		CooldownSinceStart(copy.CooldownSinceStart){

}
AbilityLoadInfo_NonTar_Durable::~AbilityLoadInfo_NonTar_Durable() {

}

Ability& AbilityLoadInfo_NonTar_Durable::InstantiateAbility() const {
	auto& eff = GameEffectsCatalog::GetObjectInfo(GameEff_CatalogID, GameEff_SubCatalogID);
	auto& ab = *new Ability_NonTar_Durable
			(*dynamic_cast<ComposeGameEff_Permanent*>(&eff),
			CatalogID, 
			SubCatalogID);
	ab.Set_CooldownDuration(CooldownDuration);
	ab.Set_CooldownSinceStart(CooldownSinceStart);
	return ab;
}
bool AbilityLoadInfo_NonTar_Durable::WriteParam(Attr& param) {

	if (AbilityLoadInfo::WriteParam(param))
		return true;

	if (CheckParamName(param, AbilitiesLoading_ParamDefNames::ABILITY_NONTAR_DURABLE_CDOWN_SSTART)) {
		CooldownSinceStart = stof(param.second);
	}
	else if (CheckParamName(param, AbilitiesLoading_ParamDefNames::ABILITY_GAMEEFF_CATALOGID)) {
		GameEff_CatalogID = stoll(param.second);
	}
	else if (CheckParamName(param, AbilitiesLoading_ParamDefNames::ABILITY_GAMEEFF_SUB_CATALOGID)) {
		GameEff_SubCatalogID = (std::byte)stoi(param.second);
	}
	else
		return false;

	return true;
}
AbilityLoadInfo& AbilityLoadInfo_NonTar_Durable::Clone() const {
	return *new AbilityLoadInfo_NonTar_Durable(*this);
}