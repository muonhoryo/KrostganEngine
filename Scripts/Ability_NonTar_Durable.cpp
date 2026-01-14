
#include <Ability_NonTar_Durable.h>

using namespace KrostganEngine::GameObjects;

Ability_NonTar_Durable::Ability_NonTar_Durable(const ComposeGameEff_Durable& GameEff, size_t CatalogID, std::byte SubcatalogID) 
	:Ability_NonTargetable(CatalogID, SubcatalogID),
	GameEff(GameEff),
	OnRemoveEffAction(OnRemoveGameEffEvAction(*this)){

	OnRemoveEffAction.Update();
}
Ability_NonTar_Durable::Ability_NonTar_Durable(const ComposeGameEff_Durable& GameEff) 
	:GameEff(GameEff),
	OnRemoveEffAction(OnRemoveGameEffEvAction(*this)) {

	OnRemoveEffAction.Update();
}
Ability_NonTar_Durable::~Ability_NonTar_Durable() {

	if (IsActive) {
		auto parOwner = dynamic_cast<IGameEffTarget*>(Owner);
		parOwner->RemoveGameEffByID(GameEff.GetCatalogID(), GameEff.GetSubcatalogID());
	}
}

void Ability_NonTar_Durable::Activate() {

	if (IsActive) {

		auto parOwner = dynamic_cast<IGameEffTarget*>(Owner);
		parOwner->RemoveGameEffByID(GameEff.GetCatalogID(), GameEff.GetSubcatalogID());
		Cancel();
	}
	else if (!Get_IsOnCooldown()) {

		auto parOwner = dynamic_cast<IGameEffTarget*>(Owner);
		parOwner->AddGameEff(GameEff.Clone());
		parOwner->RemoveGameEffEvent.Add(OnRemoveEffAction);
		if (CooldownSinceStart)
			TurnToCooldown(GetCooldownDuration());
		IsActive = true;
	}
}
void Ability_NonTar_Durable::Cancel() {

	IsActive = false;
	if(!CooldownSinceStart)
		TurnToCooldown(GetCooldownDuration());
}

void Ability_NonTar_Durable::Set_CooldownSinceStart(bool CooldownSinceStart) {
	this->CooldownSinceStart = CooldownSinceStart;
}
bool Ability_NonTar_Durable::Get_IsActive() const {
	return IsActive;
}
bool Ability_NonTar_Durable::Get_CooldownSinceStart() const {
	return CooldownSinceStart;
}

void Ability_NonTar_Durable::OnAddToUser(AbilityUserObject& user) {
	Ability_NonTargetable::OnAddToUser(user);
}
void Ability_NonTar_Durable::OnRemoveFromUser(AbilityUserObject& user) {

}