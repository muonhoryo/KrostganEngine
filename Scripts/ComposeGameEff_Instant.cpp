
#include <GameEffectsSystem.h>

using namespace KrostganEngine::GameObjects;

ComposeGameEff_Instant::ComposeGameEff_Instant(size_t CatalogID, std::byte SubcatalogID) 
	:ComposeGameEffect(CatalogID, SubcatalogID){

}
ComposeGameEff_Instant::ComposeGameEff_Instant(const ComposeGameEff_Instant& copy)
	:ComposeGameEffect(copy){

	GameEffects = vector<IGameEffect_Instant*>(copy.GameEffects.size());
	for (int i = 0;i < GameEffects.size();++i) {
		GameEffects[i] = dynamic_cast<IGameEffect_Instant*>(&copy.GameEffects[i]->Clone());
	}
}
ComposeGameEff_Instant::~ComposeGameEff_Instant() {

}
ComposeGameEffect& ComposeGameEff_Instant::Clone() const {
	return *new ComposeGameEff_Instant(*this);
}

void ComposeGameEff_Instant::AddGameEffect(IGameEffect_Instant& eff) {
	GameEffects.push_back(&eff);
}
void ComposeGameEff_Instant::RemoveGameEffect(const IGameEffect_Instant& eff) {
	CollectionsExts::Remove(GameEffects, &eff);
}

void ComposeGameEff_Instant::OnApplyToTarget(IGameEffTarget& target) {
	for (auto eff : GameEffects) {
		eff->Activate(target);
	}
	target.RemoveGameEff(*this);
}
void ComposeGameEff_Instant::OnRemoveFromTarget(IGameEffTarget& target) {

}