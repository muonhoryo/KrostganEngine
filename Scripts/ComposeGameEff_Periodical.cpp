
#include <GameEffectsSystem.h>

using namespace KrostganEngine::GameObjects;

ComposeGameEff_Periodical::ComposeGameEff_Periodical(ComposeGameEff_Instant& TickGameEffect, float TickTime, float EffTime, size_t CatalogID, std::byte SubcatalogID)
	:ComposeGameEff_Temporal(EffTime,CatalogID, SubcatalogID),
	TickGameEffect(TickGameEffect),
	TickTime(TickTime){

}
ComposeGameEff_Periodical::ComposeGameEff_Periodical(const ComposeGameEff_Periodical& copy) 
	:ComposeGameEff_Temporal(copy),
	TickGameEffect(copy.TickGameEffect),
	TickTime(copy.TickTime){

}
ComposeGameEff_Periodical::~ComposeGameEff_Periodical() {

}

ComposeGameEffect& ComposeGameEff_Periodical::Clone() const {
	return *new ComposeGameEff_Periodical(*this);
}

float ComposeGameEff_Periodical::GetTickTime() const {
	return TickTime;
}
void ComposeGameEff_Periodical::SetTickTime(float TickTime) {
	this->TickTime = TickTime;
}

void ComposeGameEff_Periodical::OnApplyToTarget(IGameEffTarget& target) {
	ComposeGameEff_Temporal::OnApplyToTarget(target);
	TickTimer.restart();
}
void ComposeGameEff_Periodical::Update_Action(CallbackRecArgs_Upd& args) {
	
	int tickCount = (int)(TickTimer.getElapsedTime().asSeconds() / TickTime);
	if (tickCount > 0) {

		for (int i = 0; i < tickCount;++i) {
			GetTarget().AddGameEff(TickGameEffect.Clone());
		}
		TickTimer.restart();
	}
}