
#include <GameEffectsSystem.h>

using namespace KrostganEngine::GameObjects;

ComposeGameEff_Durable::ComposeGameEff_Durable() {

}
ComposeGameEff_Durable::ComposeGameEff_Durable(const ComposeGameEff_Durable& copy) {

	GameEffects_Durable = vector<IGameEffect_Durable*>(copy.GameEffects_Durable.size());
	for (int i = 0;i < GameEffects_Durable.size();++i) {
		GameEffects_Durable[i] = dynamic_cast<IGameEffect_Durable*>(&copy.GameEffects_Durable[i]->Clone());
	}
}
ComposeGameEff_Durable::~ComposeGameEff_Durable() {

}

void ComposeGameEff_Durable::AddGameEffect_Durable(IGameEffect_Durable& eff) {
	GameEffects_Durable.push_back(&eff);
}
void ComposeGameEff_Durable::RemoveGameEffect_Durable(IGameEffect_Durable& eff) {
	CollectionsExts::Remove(GameEffects_Durable, &eff);
}

void ComposeGameEff_Durable::OnApplyToTarget(IGameEffTarget& target) {

	for (auto eff : GameEffects_Durable) {
		eff->Activate(target);
	}
}
void ComposeGameEff_Durable::OnRemoveFromTarget(IGameEffTarget& target) {
	
	for (auto eff : GameEffects_Durable) {
		eff->Dectivate(target);
	}
}