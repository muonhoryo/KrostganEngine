
#include <AbilitiesSystem.h>

using namespace KrostganEngine::GameObjects;

Ability::Ability(size_t CatalogID, std::byte SubcatalogID)
	:CatalogObject(CatalogID, SubcatalogID){

}
Ability::Ability() {

}
Ability::~Ability() {

}

void Ability::TurnToCooldown(float duration) {
	CooldownDuration = duration;
	CooldownTimer.restart();
	IsOnCooldown = true;
}
void Ability::ResetCooldown() {
	IsOnCooldown = false;
}
bool Ability::Get_IsOnCooldown() const {
	return IsOnCooldown;
}
float Ability::GetCooldownDuration() const {
	return CooldownDuration;
}

void Ability::Update(CallbackRecArgs_Upd args) {
	if (IsOnCooldown) {
		if (CooldownTimer.getElapsedTime().asSeconds() >= CooldownDuration)
			IsOnCooldown = false;
	}
}