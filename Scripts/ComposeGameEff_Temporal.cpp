
#include <GameEffectsSystem.h>

using namespace KrostganEngine::GameObjects;


ComposeGameEff_Temporal::ComposeGameEff_Temporal(float EffTime)
	:EffTime(EffTime){

}
ComposeGameEff_Temporal::ComposeGameEff_Temporal(const ComposeGameEff_Temporal& copy)
	:ComposeGameEff_Durable(copy),
	EffTime(copy.EffTime){

	GameEffects_TimeDepended = vector<IGameEffect_TimeDepended*>(copy.GameEffects_TimeDepended.size());
	for (int i = 0;i < GameEffects_TimeDepended.size();++i) {
		GameEffects_TimeDepended[i] = dynamic_cast<IGameEffect_TimeDepended*>(&copy.GameEffects_TimeDepended[i]->Clone());
	}
}
ComposeGameEff_Temporal::~ComposeGameEff_Temporal() {

	if (IsActive)
		OnRemoveFromTarget(*Target);
}
ComposeGameEffect& ComposeGameEff_Temporal::Clone() const {
	return *new ComposeGameEff_Temporal(*this);
}

void ComposeGameEff_Temporal::AddGameEffect_TimeDepended(IGameEffect_TimeDepended& eff) {
	GameEffects_TimeDepended.push_back(&eff);
}
void ComposeGameEff_Temporal::RemoveGameEffect_TimeDepended(IGameEffect_TimeDepended& eff) {
	CollectionsExts::Remove(GameEffects_TimeDepended, &eff);
}

void ComposeGameEff_Temporal::OnApplyToTarget(IGameEffTarget& target) {

	IsActive = true;
	Target = &target;
	ComposeGameEff_Durable::OnApplyToTarget(target);
	for (auto eff : GameEffects_TimeDepended) {
		eff->Activate(target);
	}
	Timer.restart();
}
void ComposeGameEff_Temporal::OnRemoveFromTarget(IGameEffTarget& target) {
	IsActive = false;
	ComposeGameEff_Durable::OnRemoveFromTarget(target);
	for (auto eff : GameEffects_TimeDepended) {
		eff->Dectivate(target);
	}
}
void ComposeGameEff_Temporal::Update(CallbackRecArgs_Upd args) {

	if (IsActive) {
		if (Timer.getElapsedTime().asSeconds() >= EffTime) {

			Target->RemoveGameEff(*this);
		}
		else {
			Update_Action(args);
		}
	}
}