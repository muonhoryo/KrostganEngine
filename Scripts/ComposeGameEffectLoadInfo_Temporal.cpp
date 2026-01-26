
#include <ComposeGameEffectLoadInfo.h>
#include <GameEffectsCatalogSerConsts.h>

using namespace KrostganEngine::GameObjects;

ComposeGameEffectLoadInfo_Temporal::ComposeGameEffectLoadInfo_Temporal() {

}
ComposeGameEffectLoadInfo_Temporal::ComposeGameEffectLoadInfo_Temporal(const ComposeGameEffectLoadInfo_Temporal& copy) 
	:ComposeGameEffectLoadInfo_Permanent(copy),
		EffTime(copy.EffTime){

	GeneralGameEffects_TimeDep.resize(copy.GeneralGameEffects_TimeDep.size());
	for (int i = 0;i < GeneralGameEffects_TimeDep.size();++i) {

		GeneralGameEffects_TimeDep[i] = reinterpret_cast<IGameEffect_TimeDepended*>(&copy.GeneralGameEffects_TimeDep[i]->Clone());
	}
}
ComposeGameEffectLoadInfo_Temporal::~ComposeGameEffectLoadInfo_Temporal() {

	for (auto eff : GeneralGameEffects_TimeDep) {
		delete eff;
	}
}

bool ComposeGameEffectLoadInfo_Temporal::WriteParam(Attr& param) {

	if (ComposeGameEffectLoadInfo_Permanent::WriteParam(param))
		return true;

	if (CheckParamName(param, GameEffLoad_ParamDefNames::EFFECT_TEMP_DURATION)) {
		EffTime = stof(param.second);
	}
	else
		return false;

	return true;
}

ComposeGameEffect& ComposeGameEffectLoadInfo_Temporal::InstantiateGameEff() const {

	auto& eff = *new ComposeGameEff_Temporal(EffTime,CatalogID,SubCatalogID);
	for (auto genEff : GeneralGameEffects_Dur) {
		eff.AddGameEffect_Durable(*genEff);
	}
	for (auto genEff : GeneralGameEffects_TimeDep) {
		eff.AddGameEffect_TimeDepended(*genEff);
	}
	return eff;
}
ComposeGameEffectLoadInfo& ComposeGameEffectLoadInfo_Temporal::Clone() const {
	return *new ComposeGameEffectLoadInfo_Temporal(*this);
}
void ComposeGameEffectLoadInfo_Temporal::WriteGeneralGameEff(xml_node<>& node) {
	int type = -1;

	if (!ValidateGeneralGameEff(node, type))
		return;

	auto eff = DeserializeGeneralGameEff(node);
	if (eff != nullptr) {

		if (type == TYPE_DUR) {

			GeneralGameEffects_Dur.push_back(reinterpret_cast<IGameEffect_Durable*>(eff));
		}
		else if (type == TYPE_TIMEDEP) {

			GeneralGameEffects_TimeDep.push_back(reinterpret_cast<IGameEffect_TimeDepended*>(eff));
		}
	}
}

bool ComposeGameEffectLoadInfo_Temporal::ValidateGeneralGameEff(xml_node<>& node, int& type) const {

	string name = string(&GetGenGameEffType(node));
	
	if (GameEffLoad_GeneralGameEffTypes::IsGameEffectType_TimeDepended(name)) {
		type = TYPE_TIMEDEP;
	}
	else if (GameEffLoad_GeneralGameEffTypes::IsGameEffectType_Durable(name)) {
		type = TYPE_DUR;
	}

	return type != TYPE_INVALID;
}