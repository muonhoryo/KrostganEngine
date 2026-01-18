
#include <GameEffectsSystem.h>

using namespace KrostganEngine::GameObjects;

ComposeGameEff_Permanent::ComposeGameEff_Permanent(size_t CatalogID, std::byte SubcatalogID)
	:ComposeGameEffect(CatalogID, SubcatalogID) {

}
ComposeGameEff_Permanent::ComposeGameEff_Permanent(const ComposeGameEff_Permanent& copy) 
	:ComposeGameEffect(copy){

	GameEffects_Durable = vector<IGameEffect_Durable*>(copy.GameEffects_Durable.size());
	for (int i = 0;i < GameEffects_Durable.size();++i) {
		GameEffects_Durable[i] = dynamic_cast<IGameEffect_Durable*>(&copy.GameEffects_Durable[i]->Clone());
	}
}
ComposeGameEff_Permanent::~ComposeGameEff_Permanent() {

}

void ComposeGameEff_Permanent::AddGameEffect_Durable(IGameEffect_Durable& eff) {
	GameEffects_Durable.push_back(&eff);
}
void ComposeGameEff_Permanent::RemoveGameEffect_Durable(IGameEffect_Durable& eff) {
	CollectionsExts::Remove(GameEffects_Durable, &eff);
}

ComposeGameEffect& ComposeGameEff_Permanent::Clone() const {
	return *new ComposeGameEff_Permanent(*this);
}

void ComposeGameEff_Permanent::OnApplyToTarget(IGameEffTarget& target) {

	for (auto eff : GameEffects_Durable) {
		eff->Activate(target);
	}
}
void ComposeGameEff_Permanent::OnRemoveFromTarget(IGameEffTarget& target) {
	
	for (auto eff : GameEffects_Durable) {
		eff->Deactivate(target);
	}
}