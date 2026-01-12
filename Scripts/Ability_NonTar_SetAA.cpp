
#include <Ability_NonTar_SetAA.h>
#include <Entity.h>

using namespace KrostganEngine::GameObjects;

Ability_NonTar_SetAA::Ability_NonTar_SetAA(Ability_NonTar_SetAA& NextAbility, size_t AAIndex, size_t CatalogID, std::byte SubcatalogID)
	:Ability_NonTargetable(CatalogID, SubcatalogID),
		NextAbility(&NextAbility),
		AAIndex(AAIndex){

}
Ability_NonTar_SetAA::Ability_NonTar_SetAA(Ability_NonTar_SetAA& NextAbility, size_t AAIndex)
	:NextAbility(&NextAbility),
	AAIndex(AAIndex){

}
Ability_NonTar_SetAA::Ability_NonTar_SetAA(size_t AAIndex, size_t CatalogID, std::byte SubcatalogID) 
	:Ability_NonTargetable(CatalogID, SubcatalogID),
	AAIndex(AAIndex) {

}
Ability_NonTar_SetAA::Ability_NonTar_SetAA(size_t AAIndex) 
	:AAIndex(AAIndex){

}
Ability_NonTar_SetAA::~Ability_NonTar_SetAA() {
	if (OnAddingAbilityGameEff != nullptr)
		delete OnAddingAbilityGameEff;

	delete &NextAbility;
}

void Ability_NonTar_SetAA::Activate() {
	if (NextAbility == nullptr)
		throw exception("NextAbility is not assigned");

	Owner->RemoveAbility(*this, true);
	Owner->AddAbility(*NextAbility);
	NextAbility->TurnToCooldown(NextAbilityCooldown);
}

void Ability_NonTar_SetAA::Set_NextAbility(Ability_NonTar_SetAA& NextAbility) {
	this->NextAbility = &NextAbility;
}

void Ability_NonTar_SetAA::Set_OnAddingAbilityGameEff(ComposeGameEffect* OnAddingAbilityGameEff) {
	if (this->OnAddingAbilityGameEff != nullptr)
		delete this->OnAddingAbilityGameEff;
	this->OnAddingAbilityGameEff = OnAddingAbilityGameEff;
}
void Ability_NonTar_SetAA::Set_NextAbilityCooldown(float NextAbilityCooldown) {
	this->NextAbilityCooldown = NextAbilityCooldown;
}
void Ability_NonTar_SetAA::Set_DeleteGameEffOnRemove(bool DeleteGameEffOnRemove) {
	this->DeleteGameEffOnRemove = DeleteGameEffOnRemove;
}

ComposeGameEffect* Ability_NonTar_SetAA::Get_OnAddingAbilityGameEff() const {
	return OnAddingAbilityGameEff;
}
float Ability_NonTar_SetAA::Get_NextAbilityCooldown() const {
	return NextAbilityCooldown;
}
bool Ability_NonTar_SetAA::Get_DeleteGameEffOnRemove() const {
	return DeleteGameEffOnRemove;
}

void Ability_NonTar_SetAA::OnAddToUser(AbilityUserObject& user) {

	Ability_NonTargetable::OnAddToUser(user);

	if (NextAbility == nullptr)
		throw exception("NextAbility is not assigned");

	auto parOwner = dynamic_cast<Entity*>(Owner);
	if (parOwner == nullptr) {
		Owner->RemoveAbility(*this);
		delete this;
	}
	else {
		parOwner->GetBattleStats().SetAAStats(AAIndex);
		if(OnAddingAbilityGameEff!=nullptr)
			parOwner->AddGameEff(*OnAddingAbilityGameEff);
	}
}
void Ability_NonTar_SetAA::OnRemoveFromUser(AbilityUserObject& user) {
	if (DeleteGameEffOnRemove && OnAddingAbilityGameEff!=nullptr) {

		auto parOwner = dynamic_cast<Entity*>(Owner);
		parOwner->RemoveGameEff(*OnAddingAbilityGameEff);
	}
}