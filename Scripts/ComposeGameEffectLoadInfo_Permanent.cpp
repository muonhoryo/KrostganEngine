
#include <ComposeGameEffectLoadInfo.h>
#include <GameEffectsCatalogSerConsts.h>

using namespace KrostganEngine::GameObjects;

ComposeGameEffectLoadInfo_Permanent::ComposeGameEffectLoadInfo_Permanent()
	:ComposeGameEffectLoadInfo(){

}
ComposeGameEffectLoadInfo_Permanent::ComposeGameEffectLoadInfo_Permanent(const ComposeGameEffectLoadInfo_Permanent& copy) 
	:ComposeGameEffectLoadInfo(copy){

	GeneralGameEffects_Dur.resize(copy.GeneralGameEffects_Dur.size());
	for (int i = 0;i < GeneralGameEffects_Dur.size();++i) {

		GeneralGameEffects_Dur[i] = reinterpret_cast<IGameEffect_Durable*>(&copy.GeneralGameEffects_Dur[i]->Clone());
	}
}
ComposeGameEffectLoadInfo_Permanent::~ComposeGameEffectLoadInfo_Permanent() {
	for (auto eff : GeneralGameEffects_Dur) {
		delete eff;
	}
}

ComposeGameEffect& ComposeGameEffectLoadInfo_Permanent::InstantiateGameEff() const {
	
	auto& eff = *new ComposeGameEff_Permanent(CatalogID, SubCatalogID);
	for (auto genEff : GeneralGameEffects_Dur) {
		eff.AddGameEffect_Durable(*dynamic_cast<IGameEffect_Durable*>(&genEff->Clone()));
	}
	return eff;
}

ComposeGameEffectLoadInfo& ComposeGameEffectLoadInfo_Permanent::Clone() const {
	return *new ComposeGameEffectLoadInfo_Permanent(*this);
}
void ComposeGameEffectLoadInfo_Permanent::WriteGeneralGameEff(xml_node<>& node) {

	if (!ValidateGeneralGameEff(node))
		return;

	auto eff = DeserializeGeneralGameEff(node);
	if (eff != nullptr)
		GeneralGameEffects_Dur.push_back(reinterpret_cast<IGameEffect_Durable*>(eff));
}
bool ComposeGameEffectLoadInfo_Permanent::ValidateGeneralGameEff(xml_node<>& node) const {

	string name = string(&GetGenGameEffType(node));
	return GameEffLoad_GeneralGameEffTypes::IsGameEffectType_Durable(name);
}