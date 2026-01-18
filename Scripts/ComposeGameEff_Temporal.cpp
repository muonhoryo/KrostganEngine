
#include <GameEffectsSystem.h>

using namespace KrostganEngine::GameObjects;


ComposeGameEff_Temporal::ComposeGameEff_Temporal(float EffTime, size_t CatalogID, std::byte SubcatalogID)
	:ComposeGameEff_Permanent(CatalogID,SubcatalogID),
	EffTime(EffTime){

}
ComposeGameEff_Temporal::ComposeGameEff_Temporal(const ComposeGameEff_Temporal& copy)
	:ComposeGameEff_Permanent(copy),
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
float ComposeGameEff_Temporal::GetEffectTime() const {
	return EffTime;
}
IGameEffTarget& ComposeGameEff_Temporal::GetTarget() const {
	return *Target;
}
void ComposeGameEff_Temporal::SetEffectTime(float EffTime) {
	this->EffTime = EffTime;
}

void ComposeGameEff_Temporal::OnApplyToTarget(IGameEffTarget& target) {

	IsActive = true;
	Target = &target;
	ComposeGameEff_Permanent::OnApplyToTarget(target);
	for (auto eff : GameEffects_TimeDepended) {
		eff->Activate(target);
	}
	Timer.restart();
}
void ComposeGameEff_Temporal::OnRemoveFromTarget(IGameEffTarget& target) {
	IsActive = false;
	ComposeGameEff_Permanent::OnRemoveFromTarget(target);
	for (auto eff : GameEffects_TimeDepended) {
		eff->Deactivate(target);
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