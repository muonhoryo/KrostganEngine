
#include <AbilityLoadInfo.h>
#include <AbilitiesCatalogSerConsts.h>
#include <GameEffectsCatalog.h>
#include <AbilitiesCatalog.h>

using namespace KrostganEngine::GameObjects;

AbilityLoadInfo_NonTar_SetAA::AbilityLoadInfo_NonTar_SetAA() {

}
AbilityLoadInfo_NonTar_SetAA::AbilityLoadInfo_NonTar_SetAA(const AbilityLoadInfo_NonTar_SetAA& copy) 
	:AbilityLoadInfo(copy),
		AAIndex(copy.AAIndex),
		OnAddGameEff_CatalogID(copy.OnAddGameEff_CatalogID),
		OnAddGameEff_SubCatalogID(copy.OnAddGameEff_SubCatalogID),
		NextAbilityCooldown(copy.NextAbilityCooldown),
		DeleteGameEffOnRemove(copy.DeleteGameEffOnRemove){

	NextAbilitiesInfo = vector<AbilityLoadInfo_NonTar_SetAA*>();
	CollectionsExts::CloneByPtrs<vector<AbilityLoadInfo_NonTar_SetAA*>, AbilityLoadInfo_NonTar_SetAA>
		(copy.NextAbilitiesInfo,NextAbilitiesInfo);

		vector<AbilityLoadInfo_NonTar_SetAA*> NextAbilitiesInfo;
		size_t AAIndex = 0;
		size_t OnAddGameEff_CatalogID = EMPTY_CATALOG_ID;
		std::byte OnAddGameEff_SubCatalogID = ABSENT_SUB_CATALOG_ID;
		float NextAbilityCooldown = 0;
		bool DeleteGameEffOnRemove = true;
}
AbilityLoadInfo_NonTar_SetAA::~AbilityLoadInfo_NonTar_SetAA() {
	for (auto ab : NextAbilitiesInfo) {
		delete ab;
	}
}

Ability& AbilityLoadInfo_NonTar_SetAA::InstantiateAbility() const {

	if (NextAbilitiesInfo.size() == 0)
		throw exception("AbilityLoadInfo_SetAA must have at least one next ability's info");

	auto& headAbility = InstantiateSingleSetAAAbility();
	Ability_NonTar_SetAA* prevAb = &headAbility;
	Ability_NonTar_SetAA* nextAb = nullptr;
	for (int i = 0;i < NextAbilitiesInfo.size();++i) {
		nextAb = &NextAbilitiesInfo[i]->InstantiateSingleSetAAAbility();
		prevAb->Set_NextAbility(*nextAb);
		prevAb = nextAb;
	}
	prevAb->Set_NextAbility(headAbility);
	return headAbility;
}
Ability_NonTar_SetAA& AbilityLoadInfo_NonTar_SetAA::InstantiateSingleSetAAAbility() const {

	auto& ability = *new Ability_NonTar_SetAA(AAIndex, CatalogID, SubCatalogID);
	ability.Set_CooldownDuration(CooldownDuration);
	ability.Set_DeleteGameEffOnRemove(DeleteGameEffOnRemove);
	auto& gameEff = GameEffectsCatalog::GetObjectInfo(OnAddGameEff_CatalogID, OnAddGameEff_SubCatalogID).InstantiateGameEff();
	ability.Set_OnAddingAbilityGameEff(&gameEff);
	return ability;
}
bool AbilityLoadInfo_NonTar_SetAA::WriteParam(Attr& param) {
	
	if (AbilityLoadInfo::WriteParam(param))
		return true;

	if (CheckParamName(param, AbilitiesLoading_ParamDefNames::ABILITY_NONTAR_SETAA_AAINDEX)) {
		AAIndex = stoll(param.second);
	}
	else if (CheckParamName(param, AbilitiesLoading_ParamDefNames::ABILITY_GAMEEFF_CATALOGID)) {
		OnAddGameEff_CatalogID = stoll(param.second);
	}
	else if (CheckParamName(param, AbilitiesLoading_ParamDefNames::ABILITY_GAMEEFF_SUB_CATALOGID)) {
		OnAddGameEff_SubCatalogID = (std::byte)stoi(param.second);
	}
	else if (CheckParamName(param, AbilitiesLoading_ParamDefNames::ABILITY_NONTAR_SETAA_NEXTAB_COOLDOWN)) {
		NextAbilityCooldown = stof(param.second);
	}
	else if (CheckParamName(param, AbilitiesLoading_ParamDefNames::ABILITY_NONTAR_SETAA_DELETEGAMEEFFONREM)) {
		DeleteGameEffOnRemove = FStreamExts::ParseBool(param.second);
	}
	else
		return false;

	return true;
}
bool AbilityLoadInfo_NonTar_SetAA::WriteParamByNode(xml_node<>& node) {
	char* name = node.name();
	if (name == AbilitiesLoading_XMLChildrenType::ABILITY_NONTAR_SETAA_NEXTABILITY) {
		auto abInfo = dynamic_cast<AbilityLoadInfo_NonTar_SetAA*>(&AbilitiesCatalogDeserial::DeserializeObjInfo(node));
		NextAbilitiesInfo.push_back(abInfo);
	}
	else
		return false;

	return true;
}
AbilityLoadInfo& AbilityLoadInfo_NonTar_SetAA::Clone() const {
	return *new AbilityLoadInfo_NonTar_SetAA(*this);
}