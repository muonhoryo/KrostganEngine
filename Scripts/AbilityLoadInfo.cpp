
#include <AbilityLoadInfo.h>
#include <AbilitiesCatalogSerConsts.h>

using namespace KrostganEngine::GameObjects;

AbilityLoadInfo::AbilityLoadInfo() { 

}
AbilityLoadInfo::AbilityLoadInfo(const AbilityLoadInfo& copy) 
	:ObjectLoadInfo(copy),
		Name(copy.Name),
		CooldownDuration(copy.CooldownDuration){

}

bool AbilityLoadInfo::WriteParam(Attr& param) {

	if (CheckParamName(param, AbilitiesLoading_ParamDefNames::ABILITY_NAME)) {
		Name = param.second;
	}
	else if (CheckParamName(param, AbilitiesLoading_ParamDefNames::ABILITY_COOLDOWN_DUR)) {
		CooldownDuration = stof(param.second);
	}
	else if (CheckParamName(param, AbilitiesLoading_ParamDefNames::ABILITY_CATALOG_ID)) {
		CatalogID = stol(param.second);
	}
	else {
		return false;
	}
	return true;
}
bool AbilityLoadInfo::WriteParamByNode(xml_node<>& node) {
	return false;
}