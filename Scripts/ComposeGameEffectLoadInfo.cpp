
#include <iostream>
#include <ComposeGameEffectLoadInfo.h>
#include <GameEffectsCatalogSerConsts.h>
#include <RelationsSystem.h>
#include <GeneralGameEffects.h>
#include <GameEffectsCatalog.h>

using namespace std;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

ComposeGameEffectLoadInfo::ComposeGameEffectLoadInfo() {

}
ComposeGameEffectLoadInfo::ComposeGameEffectLoadInfo(const ComposeGameEffectLoadInfo& copy) 
	:Name(copy.Name),
	IsStackable(copy.IsStackable){

}
ComposeGameEffectLoadInfo::~ComposeGameEffectLoadInfo() {

}

bool ComposeGameEffectLoadInfo::WriteParam(Attr& param) {

	if (CheckParamName(param, GameEffLoad_ParamDefNames::EFFECT_NAME)) {
		Name = param.second;
	}
	else if (CheckParamName(param, GameEffLoad_ParamDefNames::EFFECT_STACKABLE)) {
		IsStackable = FStreamExts::ParseBool(param.second);
	}
	else if (CheckParamName(param, DEF_CATALOG_ID)) {
		CatalogID = stol(param.second);
	}
	else {
		return false;
	}
	return true;
}
IGameEffect* ComposeGameEffectLoadInfo::DeserializeGeneralGameEff(xml_node<>& node) const {

	IGameEffect* eff = nullptr;
	string name = string(&GetGenGameEffType(node));
	if (name == GameEffLoad_GeneralGameEffTypes::DESERTER) {

		eff = &DeserializeGameEff_Dur_Deserter(node, name);
	}
	else if (name == GameEffLoad_GeneralGameEffTypes::DISARM) {
		
		eff = &DeserializeGameEff_Dur_Disarm(node, name);
	}
	else if (name == GameEffLoad_GeneralGameEffTypes::ENTBATSTAT_CONST_BOOL) {
		eff = &DeserializeGameEff_Dur_EntBatStatConst_Bool(node, name);
	}
	else if (name == GameEffLoad_GeneralGameEffTypes::ENTBATSTAT_MULT) {
		eff = &DeserializeGameEff_Dur_EntBatStatMult(node, name);
	}
	else if (name == GameEffLoad_GeneralGameEffTypes::ADDDUREFF) {
		eff = &DeserializeGameEff_Inst_AddDurEff(node, name);
	}
	else {

		cout << "GameEffectLoad: Unknown type of general game effect" << endl;
		return nullptr;
	}
	
	return eff;
}
const char& ComposeGameEffectLoadInfo::GetGenGameEffType(xml_node<>& genGameEffNode) {

	xml_attribute<>* attr = genGameEffNode.first_attribute();
	char* name = nullptr;
	while (attr != nullptr) {
		name = attr->name();

		if (name == GameEffLoad_GeneralGameEffTypes::TYPE_DEF) {
			return *attr->value();
		}

		attr = attr->next_attribute();
	}
	throw exception("Type-attribute didnt defined");
}
IGameEffect& ComposeGameEffectLoadInfo::DeserializeGameEff_Dur_Deserter(xml_node<>& node, string& nameBuffer) const {

	Fraction deserFraction = FractionsSystem::DEFAULT_FRAC;
	xml_attribute<>* attr = node.first_attribute();
	while (attr != nullptr) {
		nameBuffer = attr->name();
		if (nameBuffer == GameEffLoad_ParamDefNames::EFFECT_DESERTER_FRACTION) {
			deserFraction = FractionsSystem::GetFractionByName(attr->value());
		}

		attr = attr->next_attribute();
	}
	return *new GameEff_Dur_Deserter(deserFraction);
}
IGameEffect& ComposeGameEffectLoadInfo::DeserializeGameEff_Dur_Disarm(xml_node<>& node, string& nameBuffer) const {

	return *new GameEff_Dur_Disarm();
}
IGameEffect& ComposeGameEffectLoadInfo::DeserializeGameEff_Dur_EntBatStatConst_Bool(xml_node<>& node, string& nameBuffer) const {

	EntityBattleStatType statType = EntityBattleStatType::IsTargetableForAA;
	bool value = true;
	xml_attribute<>* attr = node.first_attribute();
	while (attr != nullptr) {
		nameBuffer = attr->name();
		if (nameBuffer == GameEffLoad_ParamDefNames::EFFECT_STATMOD_PARAMNAME) {
			statType = EntityBattleStats::StrToStat(attr->value());
		}
		else if (nameBuffer == GameEffLoad_ParamDefNames::EFFECT_STATMOD_VALUE) {
			value = FStreamExts::ParseBool(attr->value());
		}

		attr = attr->next_attribute();
	}
	return *new GameEff_Dur_EntBatStatConst_bool(statType, value);
}
IGameEffect& ComposeGameEffectLoadInfo::DeserializeGameEff_Dur_EntBatStatMult(xml_node<>& node, string& nameBuffer) const {

	EntityBattleStatType statType = EntityBattleStatType::IsTargetableForAA;
	float value = 1;
	xml_attribute<>* attr = node.first_attribute();
	while (attr != nullptr) {
		nameBuffer = attr->name();
		if (nameBuffer == GameEffLoad_ParamDefNames::EFFECT_STATMOD_PARAMNAME) {

			statType = EntityBattleStats::StrToStat(attr->value());
		}
		else if (nameBuffer == GameEffLoad_ParamDefNames::EFFECT_STATMOD_VALUE) {
			value = stof(attr->value());
		}

		attr = attr->next_attribute();
	}
	return *new GameEff_Dur_EntBatStatMult(statType, value);
}
IGameEffect& ComposeGameEffectLoadInfo::DeserializeGameEff_Inst_AddDurEff(xml_node<>& node, string& nameBuffer) const {
	size_t catalogID = EMPTY_CATALOG_ID;
	std::byte subcatalogId = ABSENT_SUB_CATALOG_ID;
	xml_attribute<>* attr = node.first_attribute();
	while (attr != nullptr) {
		nameBuffer = attr->name();
		if (nameBuffer == GameEffLoad_ParamDefNames::GEN_EFFECT_ADDGAMEEFF_CATALOG_ID) {

			catalogID = stoll(attr->value());
		}
		else if (nameBuffer == GameEffLoad_ParamDefNames::GEN_EFFECT_ADDGAMEEFF_SUB_CATALOG_ID) {
			subcatalogId = (std::byte)stoi(attr->value());
		}

		attr = attr->next_attribute();
	}
	if (catalogID == EMPTY_CATALOG_ID)
		throw new exception("CatalogID cant be empty");
	return *new GameEff_Inst_AddDurEff(catalogID, subcatalogId);
}