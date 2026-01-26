
#include <ComposeGameEffectLoadInfo.h>
#include <GameEffectsCatalogSerConsts.h>
#include <GameEffectsSystem.h>

using namespace KrostganEngine::GameObjects;

ComposeGameEffectLoadInfo_Instant::ComposeGameEffectLoadInfo_Instant()
	:ComposeGameEffectLoadInfo(){

}
ComposeGameEffectLoadInfo_Instant::ComposeGameEffectLoadInfo_Instant(const ComposeGameEffectLoadInfo_Instant& copy) 
	:ComposeGameEffectLoadInfo(copy){

	GeneralGameEffects_Inst.resize(copy.GeneralGameEffects_Inst.size());
	for (int i = 0;i < GeneralGameEffects_Inst.size();++i) {

		GeneralGameEffects_Inst[i] = reinterpret_cast<IGameEffect_Instant*>(&copy.GeneralGameEffects_Inst[i]->Clone());
	}
}
ComposeGameEffectLoadInfo_Instant::~ComposeGameEffectLoadInfo_Instant() {

	for (auto eff : GeneralGameEffects_Inst) {
		delete eff;
	}
}

void ComposeGameEffectLoadInfo_Instant::WriteGeneralGameEff(xml_node<>& node) {

	if (!ValidateGeneralGameEff(node))
		return;

	auto eff = DeserializeGeneralGameEff(node);
	if (eff != nullptr)
		GeneralGameEffects_Inst.push_back(reinterpret_cast<IGameEffect_Instant*>(eff));
}
bool ComposeGameEffectLoadInfo_Instant::ValidateGeneralGameEff(xml_node<>& node) const {
	string name = string(&GetGenGameEffType(node));
	return GameEffLoad_GeneralGameEffTypes::IsGameEffectType_Instant(name);
}

ComposeGameEffect& ComposeGameEffectLoadInfo_Instant::InstantiateGameEff() const {

	ComposeGameEff_Instant& eff = *new ComposeGameEff_Instant(CatalogID, SubCatalogID);
	for (auto genEff : GeneralGameEffects_Inst) {
		eff.AddGameEffect(*reinterpret_cast<IGameEffect_Instant*>(&genEff->Clone()));
	}
	return eff;
}
ComposeGameEffectLoadInfo& ComposeGameEffectLoadInfo_Instant::Clone() const {
	return *new ComposeGameEffectLoadInfo_Instant(*this);
}